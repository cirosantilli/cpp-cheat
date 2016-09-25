#ifndef COMMON_GLUT_H
#define COMMON_GLUT_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "common_texture.h"

int common_glut_fps_last_time;
void common_glut_fps_init(void) {
    common_glut_fps_last_time = glutGet(GLUT_ELAPSED_TIME);
}
void common_glut_fps_print(void) {
    int t;
    int dt;
    static int nframes = 0;
    nframes++;
    t = glutGet(GLUT_ELAPSED_TIME);
    dt = t - common_glut_fps_last_time;
    if (dt > 250) {
        printf("FPS = %f\n", (nframes / (dt / 1000.0)));
        common_glut_fps_last_time = t;
        nframes = 0;
    }
}

#endif
