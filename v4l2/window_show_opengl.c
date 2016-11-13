/* V4L2 video picture grabber and GL displayer
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
Show camera on a window. Uses immediate mode OpenGL, raw X11 windowing and GLUT.
Adapted from official git tree: https://git.linuxtv.org/v4l-utils.git v4l-utils-1.10.0 contrib/test/v4l2gl.c
*/

#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <linux/videodev2.h>
#include <libv4l2.h>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

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
		fprintf(stderr, "error %d, %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void Redraw(Display *dpy, Window win)
{
	XWindowAttributes	gwa;

	XGetWindowAttributes(dpy, win, &gwa);
	glViewport(0, 0, gwa.width, gwa.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1., 1., -1., 1., 1., 20.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0,  1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( 1.0,  1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f( 1.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 0.0);
	glEnd();

	glXSwapBuffers(dpy, win);
}

static int capture(char *dev_name, int x_res, int y_res, int n_frames,
		   char *out_dir)
{
	struct v4l2_format		fmt;
	struct v4l2_buffer		buf;
	struct v4l2_requestbuffers	req;
	enum v4l2_buf_type		type;
	fd_set				fds;
	struct timeval			tv;
	int				r, fd = -1;
	unsigned int			i, j, n_buffers;
	struct buffer			*buffers;
	Display				*dpy;
	Window				win;
	int				num_textures = 1;
	GLuint				texture_id[num_textures];
	Window				root;
	XVisualInfo			*vi;
	XSetWindowAttributes		swa;
	GLXContext			glc;
	GLint				att[] = {
		GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None
	};

	dpy = XOpenDisplay(NULL);
	if (!dpy) {
		printf("\tcannot open display.\n");
		exit(EXIT_FAILURE);
	}

	root = DefaultRootWindow(dpy);

	vi = glXChooseVisual(dpy, 0, att);
	if (!vi) {
		printf("no appropriate visual found.\n");
		exit(EXIT_FAILURE);
	}
	swa.event_mask = ExposureMask | KeyPressMask;
	swa.colormap   = XCreateColormap(dpy, root, vi->visual, AllocNone);

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
	if ((fmt.fmt.pix.width != x_res) || (fmt.fmt.pix.height != y_res))
		printf("Warning: driver is sending image at %dx%d\n",
			fmt.fmt.pix.width, fmt.fmt.pix.height);

	printf("Fourcc format: %c%c%c%c\n",
		fmt.fmt.pix.pixelformat & 0xff,
		(fmt.fmt.pix.pixelformat >> 8) &0xff,
		(fmt.fmt.pix.pixelformat >> 16) &0xff,
		(fmt.fmt.pix.pixelformat >> 24) &0xff);

	win = XCreateWindow(dpy, root, 0, 0,
			    fmt.fmt.pix.width, fmt.fmt.pix.height, 0, vi->depth,
			    InputOutput, vi->visual, CWEventMask  | CWColormap,
			    &swa);
	XMapWindow(dpy, win);
	XStoreName(dpy, win, dev_name);

	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	if (glc == NULL) {
		printf("\n\tcannot create gl context\n\n");
		exit(0);
	}

	glXMakeCurrent(dpy, win, glc);
	glEnable(GL_DEPTH_TEST);

	XCreatePixmap(dpy, root,
		      fmt.fmt.pix.width, fmt.fmt.pix.height,
		      vi->depth);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, texture_id);
	for (j = 0; j < num_textures; j++) {
		glActiveTexture(GL_TEXTURE0 + j);
		glBindTexture(GL_TEXTURE_2D, texture_id[j]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glEnable(GL_TEXTURE_2D);
	}

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
	i = 0;

	while (i < n_frames || n_frames <= 0) {
		/* Request new buffer */
		if (i)
			xioctl(fd, VIDIOC_QBUF, &buf);

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

		/*
		 * Display the image via GL - for RGB, only one texture is enough
		 */
		for (j = 0; j < num_textures; j++) {
			glActiveTexture(GL_TEXTURE0 + j);
			glBindTexture(GL_TEXTURE_2D, texture_id[j]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				fmt.fmt.pix.width, fmt.fmt.pix.height, 0,
				GL_RGB, GL_UNSIGNED_BYTE,
				((char *)buffers[buf.index].start) + j);
		}
		Redraw(dpy, win);

		i++;
	}

	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	xioctl(fd, VIDIOC_STREAMOFF, &type);
	for (i = 0; i < n_buffers; ++i)
		v4l2_munmap(buffers[i].start, buffers[i].length);
	v4l2_close(fd);

	return 0;
}

/*
 * Main routine. Basically, reads parameters via argp.h and passes it to the
 * capture routine
 */

const char *argp_program_bug_address = "Mauro Carvalho Chehab <m.chehab@samsung.com>";

static const char doc[] = "\nCapture images using libv4l, storing them as ppm files\n";

static const struct argp_option options[] = {
	{"device",	'd',	"DEV",		0,	"video device (default: /dev/video0)", 0},
	{"out-dir",	'o',	"OUTDIR",	0,	"output directory (default: current dir)", 0},
	{"xres",	'x',	"XRES",		0,	"horizontal resolution", 0},
	{"yres",	'y',	"YRES",		0,	"vertical resolution", 0},
	{"n-frames",	'n',	"NFRAMES",	0,	"number of frames to capture", 0},
	{ 0, 0, 0, 0, 0, 0 }
};

/* Static vars to store the parameters */
static char 	*dev_name = "/dev/video0";
static char	*out_dir = ".";
static int	x_res = 640;
static int	y_res = 480;
static int	n_frames = -1;

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

	return capture(dev_name, x_res, y_res, n_frames, out_dir);
}
