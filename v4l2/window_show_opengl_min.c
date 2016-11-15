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
Same as window_show_opengl, but minimized.
*/

#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include "common_v4l2.h"

static void setup_display(
    Display **dpy,
    Window *win,
    GLuint *texture_id,
    unsigned int x_res,
    unsigned int y_res,
    char *dev_name
) {

    GLXContext glc;
    GLint att[] = {
        GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None
    };
    Window root;
    XSetWindowAttributes swa;
    XVisualInfo *vi;
    unsigned int i, j;

    *dpy = XOpenDisplay(NULL);
    if (!*dpy) {
        printf("error: XOpenDisplay\n");
        exit(EXIT_FAILURE);
    }
    root = DefaultRootWindow(*dpy);
    vi = glXChooseVisual(*dpy, 0, att);
    if (!vi) {
        printf("error: glXChooseVisual\n");
        exit(EXIT_FAILURE);
    }
    swa.event_mask = ExposureMask | KeyPressMask;
    swa.colormap = XCreateColormap(*dpy, root, vi->visual, AllocNone);
    *win = XCreateWindow(*dpy, root, 0, 0,
                x_res, y_res, 0, vi->depth, InputOutput,
                vi->visual, CWEventMask  | CWColormap, &swa);
    XMapWindow(*dpy, *win);
    XStoreName(*dpy, *win, dev_name);
    glc = glXCreateContext(*dpy, vi, NULL, GL_TRUE);
    if (glc == NULL) {
        printf("error: glXCreateContext");
        exit(EXIT_FAILURE);
    }
    glXMakeCurrent(*dpy, *win, glc);
    glEnable(GL_DEPTH_TEST);
    XCreatePixmap(*dpy, root, x_res, y_res, vi->depth);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
}

static void redraw(
    void *image,
    unsigned int x_res,
    unsigned int y_res,
    Display **dpy,
    Window *win,
    GLuint *texture_id
) {
    XWindowAttributes gwa;
    unsigned int i;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x_res, y_res, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image);
    XGetWindowAttributes(*dpy, *win, &gwa);
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
    glXSwapBuffers(*dpy, *win);
}

int main(void) {
    char
        *dev_name = "/dev/video0",
        *out_dir = "."
    ;
    unsigned int
        x_res = 640,
        y_res = 480,
        i
    ;
    CommonV4l2 common_v4l2;
    Display *dpy = NULL;
    GLuint texture_id;
    Window win;

    setup_display(&dpy, &win, &texture_id, x_res, y_res, dev_name);
    CommonV4l2_init(&common_v4l2, dev_name, x_res, y_res);
    /* Main loop. */
    while (1) {
        CommonV4l2_updateImage(&common_v4l2);
        redraw(CommonV4l2_getImage(&common_v4l2), x_res, y_res, &dpy, &win, &texture_id);
    }
    CommonV4l2_deinit(&common_v4l2);
    return EXIT_SUCCESS;
}
