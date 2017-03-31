#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define GLEW_STATIC
#include <GL/glew.h>

#define COMMON_COLOR_MAX 255
#define COMMON_WINDOW_WIDTH 500
#define COMMON_WINDOW_HEIGHT (COMMON_WINDOW_WIDTH)

double common_get_secs(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + (1e-9 * ts.tv_nsec);
}

const double COMMON_FPS_GRANULARITY_S = 0.5;
double common_fps_last_time_s;
unsigned int common_fps_nframes;

void common_fps_init() {
    common_fps_nframes = 0;
    common_fps_last_time_s = common_get_secs();
}

void common_fps_update_and_print() {
    double dt, current_time_s;
    current_time_s = common_get_secs();
    common_fps_nframes++;
    dt = current_time_s - common_fps_last_time_s;
    if (dt > COMMON_FPS_GRANULARITY_S) {
        printf("FPS = %f\n", common_fps_nframes / dt);
        common_fps_last_time_s = current_time_s;
        common_fps_nframes = 0;
    }
}

#endif
