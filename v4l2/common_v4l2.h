#ifndef COMMON_V4L2_H
#define COMMON_V4L2_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>

#include <libv4l2.h>
#include <linux/videodev2.h>

#define COMMON_V4L2_CLEAR(x) memset(&(x), 0, sizeof(x))
#define COMMON_V4L2_DEVICE "/dev/video0"

typedef struct {
    void *start;
    size_t length;
} CommonV4l2_Buffer;

typedef struct {
    int fd;
    CommonV4l2_Buffer *buffers;
    struct v4l2_buffer buf;
    unsigned int n_buffers;
} CommonV4l2;

void CommonV4l2_xioctl(int fh, unsigned long int request, void *arg)
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

void CommonV4l2_init(CommonV4l2 *this, char *dev_name, unsigned int x_res, unsigned int y_res) {
    enum v4l2_buf_type type;
    struct v4l2_format fmt;
    struct v4l2_requestbuffers req;
    unsigned int i;

    this->fd = v4l2_open(dev_name, O_RDWR | O_NONBLOCK, 0);
    if (this->fd < 0) {
        perror("Cannot open device");
        exit(EXIT_FAILURE);
    }
    COMMON_V4L2_CLEAR(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = x_res;
    fmt.fmt.pix.height      = y_res;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
    CommonV4l2_xioctl(this->fd, VIDIOC_S_FMT, &fmt);
    if ((fmt.fmt.pix.width != x_res) || (fmt.fmt.pix.height != y_res))
        printf("Warning: driver is sending image at %dx%d\n",
            fmt.fmt.pix.width, fmt.fmt.pix.height);
    COMMON_V4L2_CLEAR(req);
    req.count = 2;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    CommonV4l2_xioctl(this->fd, VIDIOC_REQBUFS, &req);
    this->buffers = calloc(req.count, sizeof(*this->buffers));
    for (this->n_buffers = 0; this->n_buffers < req.count; ++this->n_buffers) {
        COMMON_V4L2_CLEAR(this->buf);
        this->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        this->buf.memory = V4L2_MEMORY_MMAP;
        this->buf.index = this->n_buffers;
        CommonV4l2_xioctl(this->fd, VIDIOC_QUERYBUF, &this->buf);
        this->buffers[this->n_buffers].length = this->buf.length;
        this->buffers[this->n_buffers].start = v4l2_mmap(NULL, this->buf.length,
            PROT_READ | PROT_WRITE, MAP_SHARED, this->fd, this->buf.m.offset);
        if (MAP_FAILED == this->buffers[this->n_buffers].start) {
            perror("mmap");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < this->n_buffers; ++i) {
        COMMON_V4L2_CLEAR(this->buf);
        this->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        this->buf.memory = V4L2_MEMORY_MMAP;
        this->buf.index = i;
        CommonV4l2_xioctl(this->fd, VIDIOC_QBUF, &this->buf);
    }
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    CommonV4l2_xioctl(this->fd, VIDIOC_STREAMON, &type);
}

void CommonV4l2_updateImage(CommonV4l2 *this) {
    fd_set fds;
    int r;
    struct timeval tv;

    do {
        FD_ZERO(&fds);
        FD_SET(this->fd, &fds);

        /* Timeout. */
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        r = select(this->fd + 1, &fds, NULL, NULL, &tv);
    } while ((r == -1 && (errno == EINTR)));
    if (r == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    }
    COMMON_V4L2_CLEAR(this->buf);
    this->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    this->buf.memory = V4L2_MEMORY_MMAP;
    CommonV4l2_xioctl(this->fd, VIDIOC_DQBUF, &this->buf);
    CommonV4l2_xioctl(this->fd, VIDIOC_QBUF, &this->buf);
}

/* TODO must be called after updateImage? Or is init enough? */
void * CommonV4l2_getImage(CommonV4l2 *this) {
    return this->buffers[this->buf.index].start;
}

/* TODO must be called after updateImage? Or is init enough? */
size_t CommonV4l2_getImageSize(CommonV4l2 *this) {
    return this->buffers[this->buf.index].length;
}

void CommonV4l2_deinit(CommonV4l2 *this) {
    unsigned int i;
    enum v4l2_buf_type type;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    CommonV4l2_xioctl(this->fd, VIDIOC_STREAMOFF, &type);
    for (i = 0; i < this->n_buffers; ++i)
        v4l2_munmap(this->buffers[i].start, this->buffers[i].length);
    v4l2_close(this->fd);
    free(this->buffers);
}

#endif
