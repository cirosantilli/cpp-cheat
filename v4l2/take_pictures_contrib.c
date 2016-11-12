/* V4L2 video picture grabber
   Copyright (C) 2009 Mauro Carvalho Chehab <mchehab@infradead.org>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 */

/*
Convert camera to a few ppms.
Adapted from official git tree: https://git.linuxtv.org/v4l-utils.git v4l-utils-1.10.0 contrib/test/v4l2grab.c
*/

#define _XOPEN_SOURCE 700
#include <argp.h>
#include <errno.h>
#include <fcntl.h>
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

#define CLEAR_P(x,s) memset((x), 0, s)
#define CLEAR(x) CLEAR_P(&(x), sizeof(x))

struct buffer {
	void   *start;
	size_t length;
};

static void xioctl(int fh, unsigned long int request, void *arg)
{
	int r;
	do {
		r = v4l2_ioctl(fh, request, arg);
	} while (r == -1 && ((errno == EINTR) || (errno == EAGAIN)));
	if (r == -1) {
		fprintf(stderr, "%s(%lu): error %d, %s\n", __func__,
			_IOC_NR(request), errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

/* Used by the multi thread capture version */
struct buffer_queue {
	struct v4l2_buffer *buffers;
	int buffers_size;

	int read_pos;
	int write_pos;
	int n_frames;

	int fd;

	pthread_mutex_t mutex;
	pthread_cond_t buffer_cond;
};

/* Gets a buffer and puts it in the buffers list at write position, then
 * notifies the consumer that a new buffer is ready to be used */
static void *produce_buffer (void * p)
{
	struct buffer_queue 		*bq;
	fd_set				fds;
	struct timeval			tv;
	int				i;
	struct v4l2_buffer		*buf;
	int				r;

	bq = p;

	for (i = 0; i < bq->n_frames; i++) {
		printf ("Prod: %d\n", i);
		buf = &bq->buffers[bq->write_pos % bq->buffers_size];
		do {
			FD_ZERO(&fds);
			FD_SET(bq->fd, &fds);

			/* Timeout. */
			tv.tv_sec = 2;
			tv.tv_usec = 0;

			r = select(bq->fd + 1, &fds, NULL, NULL, &tv);
		} while ((r == -1 && (errno == EINTR)));
		if (r == -1) {
			perror("select");
			pthread_exit (NULL);
			return NULL;
		}

		CLEAR_P(buf, sizeof(struct v4l2_buffer));
		buf->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf->memory = V4L2_MEMORY_MMAP;
		xioctl(bq->fd, VIDIOC_DQBUF, buf);

		pthread_mutex_lock (&bq->mutex);
		bq->write_pos++;
		printf ("Prod: %d (done)\n", i);
		pthread_cond_signal (&bq->buffer_cond);
		pthread_mutex_unlock (&bq->mutex);

	}

	pthread_exit (NULL);
}

/* will create a separate thread that will produce the buffers and put
 * into a circular array while this same thread will get the buffers from
 * this array and 'render' them */
static int capture_threads (int fd, struct buffer *buffers, int bufpool_size,
			struct v4l2_format fmt, int n_frames,
			char *out_dir, int sleep_ms)
{
	struct v4l2_buffer		buf;
	unsigned int			i;
	struct buffer_queue		buf_queue;
	pthread_t			producer;
	char				out_name[25 + strlen(out_dir)];
	FILE				*fout;
	struct timespec			sleeptime;

	if (sleep_ms) {
		sleeptime.tv_sec = sleep_ms / 1000;
		sleeptime.tv_nsec = (sleep_ms % 1000) * 1000000;
	}

	buf_queue.buffers_size = bufpool_size * 2;
	buf_queue.buffers = calloc(buf_queue.buffers_size,
				   sizeof(struct v4l2_buffer));
	buf_queue.fd = fd;
	buf_queue.read_pos = 0;
	buf_queue.write_pos = 0;
	buf_queue.n_frames = n_frames;
	pthread_mutex_init (&buf_queue.mutex, NULL);
	pthread_cond_init (&buf_queue.buffer_cond, NULL);

	pthread_create (&producer, NULL, produce_buffer, &buf_queue);

	for (i = 0; i < n_frames; i++) {
		printf ("Read: %d\n", i);

		/* wait for a buffer to be available in the queue */
		pthread_mutex_lock (&buf_queue.mutex);
		while (buf_queue.read_pos == buf_queue.write_pos) {
			pthread_cond_wait (&buf_queue.buffer_cond,
					   &buf_queue.mutex);
		}
		pthread_mutex_unlock (&buf_queue.mutex);

		if (sleep_ms)
			nanosleep (&sleeptime, NULL);

		sprintf(out_name, "%s/out%03d.ppm", out_dir, i);
		fout = fopen(out_name, "w");
		if (!fout) {
			perror("Cannot open image");
			exit(EXIT_FAILURE);
		}
		fprintf(fout, "P6\n%d %d 255\n",
			fmt.fmt.pix.width, fmt.fmt.pix.height);
		buf = buf_queue.buffers[buf_queue.read_pos %
					buf_queue.buffers_size];
		fwrite(buffers[buf.index].start, buf.bytesused, 1, fout);
		fclose(fout);

		xioctl(fd, VIDIOC_QBUF, &buf);

		pthread_mutex_lock (&buf_queue.mutex);
		buf_queue.read_pos++;
		printf ("Read: %d (done)\n", i);
		pthread_cond_signal (&buf_queue.buffer_cond);
		pthread_mutex_unlock (&buf_queue.mutex);
	}

	pthread_mutex_destroy (&buf_queue.mutex);
	pthread_cond_destroy (&buf_queue.buffer_cond);
	free (buf_queue.buffers);
	return 0;
}

static int capture_loop (int fd, struct buffer *buffers, struct v4l2_format fmt,
			int n_frames, char *out_dir)
{
	struct v4l2_buffer		buf;
	unsigned int			i;
	struct timeval			tv;
	int				r;
	fd_set				fds;
	FILE				*fout;
	char				out_name[25 + strlen(out_dir)];

	for (i = 0; i < n_frames; i++) {
		do {
			FD_ZERO(&fds);
			FD_SET(fd, &fds);

			/* Timeout. */
			tv.tv_sec = 2;
			tv.tv_usec = 0;

			r = select(fd + 1, &fds, NULL, NULL, &tv);
		} while ((r == -1 && (errno == EINTR)));
		if (r == -1) {
			perror("select");
			return errno;
		}

		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		xioctl(fd, VIDIOC_DQBUF, &buf);

		sprintf(out_name, "%s/out%03d.ppm", out_dir, i);
		fout = fopen(out_name, "w");
		if (!fout) {
			perror("Cannot open image");
			exit(EXIT_FAILURE);
		}
		fprintf(fout, "P6\n%d %d 255\n",
			fmt.fmt.pix.width, fmt.fmt.pix.height);
		fwrite(buffers[buf.index].start, buf.bytesused, 1, fout);
		fclose(fout);

		xioctl(fd, VIDIOC_QBUF, &buf);
	}
	return 0;
}

static int capture(char *dev_name, int x_res, int y_res, int n_frames,
		   char *out_dir, int block, int threads, int sleep_ms)
{
	struct v4l2_format		fmt;
	struct v4l2_buffer		buf;
	struct v4l2_requestbuffers	req;
	enum v4l2_buf_type		type;
	int				fd = -1;
	unsigned int			i, n_buffers;
	struct buffer			*buffers;

	if (block)
		fd = v4l2_open(dev_name, O_RDWR, 0);
	else
		fd = v4l2_open(dev_name, O_RDWR | O_NONBLOCK, 0);
	if (fd < 0) {
		perror("Cannot open device");
		exit(EXIT_FAILURE);
	}

	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width       = x_res;
	fmt.fmt.pix.height      = y_res;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
	fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
	xioctl(fd, VIDIOC_S_FMT, &fmt);
	if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_RGB24) {
		printf("Libv4l didn't accept RGB24 format. Can't proceed.\n");
		exit(EXIT_FAILURE);
	}
	if ((fmt.fmt.pix.width != x_res) || (fmt.fmt.pix.height != y_res))
		printf("Warning: driver is sending image at %dx%d\n",
			fmt.fmt.pix.width, fmt.fmt.pix.height);

	CLEAR(req);
	req.count = 2;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	xioctl(fd, VIDIOC_REQBUFS, &req);

	buffers = calloc(req.count, sizeof(*buffers));
	for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
		CLEAR(buf);

		buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory      = V4L2_MEMORY_MMAP;
		buf.index       = n_buffers;

		xioctl(fd, VIDIOC_QUERYBUF, &buf);

		buffers[n_buffers].length = buf.length;
		buffers[n_buffers].start = v4l2_mmap(NULL, buf.length,
			      PROT_READ | PROT_WRITE, MAP_SHARED,
			      fd, buf.m.offset);

		if (MAP_FAILED == buffers[n_buffers].start) {
			perror("mmap");
			exit(EXIT_FAILURE);
		}
	}

	for (i = 0; i < n_buffers; ++i) {
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		xioctl(fd, VIDIOC_QBUF, &buf);
	}
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	xioctl(fd, VIDIOC_STREAMON, &type);
	if (threads)
		capture_threads(fd, buffers, 2, fmt, n_frames, out_dir,
				sleep_ms);
	else
		capture_loop(fd, buffers, fmt, n_frames, out_dir);

	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	xioctl(fd, VIDIOC_STREAMOFF, &type);
	for (i = 0; i < n_buffers; ++i)
		v4l2_munmap(buffers[i].start, buffers[i].length);
	v4l2_close(fd);

	return 0;
}

static const char doc[] = "\nCapture images using libv4l, storing them as ppm files\n";

static const struct argp_option options[] = {
	{"device",	'd',	"DEV",		0,	"video device (default: /dev/video0)", 0},
	{"out-dir",	'o',	"OUTDIR",	0,	"output directory (default: current dir)", 0},
	{"xres",	'x',	"XRES",		0,	"horizontal resolution", 0},
	{"yres",	'y',	"YRES",		0,	"vertical resolution", 0},
	{"n-frames",	'n',	"NFRAMES",	0,	"number of frames to capture", 0},
	{"thread-enable", 't',	"THREADS",	0,	"if different threads should capture and save", 0},
	{"blockmode-enable", 'b', "BLOCKMODE",	0,	"if blocking mode should be used", 0},
	{"sleep-time",	's',	"SLEEP",	0,	"how long should the consumer thread sleep to simulate the processing of a buffer (in ms)"},
	{ 0, 0, 0, 0, 0, 0 }
};

/* Static vars to store the parameters */
static char 	*dev_name = "/dev/video0";
static char	*out_dir = ".";
static int	x_res = 640;
static int	y_res = 480;
static int	n_frames = 20;
static int	threads = 0;
static int	block = 0;
static int	sleep_ms = 0;

static error_t parse_opt(int k, char *arg, struct argp_state *state)
{
	int val;

	switch (k) {
	case 'd':
		dev_name = arg;
		break;
	case 'o':
		out_dir = arg;
		break;
	case 'x':
		val = atoi(arg);
		if (val)
			x_res = val;
		break;
	case 'y':
		val = atoi(arg);
		if (val)
			y_res = val;
		break;
	case 'n':
		val = atoi(arg);
		if (val)
			n_frames = val;
		break;
	case 't':
		threads = 1;
		break;
	case 'b':
		block = 1;
		break;
	case 's':
		val = atoi(arg);
		if (val)
			sleep_ms = val;
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = {
	.options = options,
	.parser = parse_opt,
	.doc = doc,
};


int main(int argc, char **argv)
{
	argp_parse(&argp, argc, argv, 0, 0, 0);

	return capture(dev_name, x_res, y_res, n_frames, out_dir, block,
		       threads, sleep_ms);
}
