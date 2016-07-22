#include <time.h>

static const double FPS_GRANULARITY_S = 0.5;
static double fps_last_time_s;
static unsigned int fps_nframes;

static double fps_get_secs(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + (1e-9 * ts.tv_nsec);
}

static void fps_init() {
    fps_nframes = 0;
    fps_last_time_s = fps_get_secs();
}

static void fps_update_and_print() {
    double fps_dt, current_time_s;
    current_time_s = fps_get_secs();
    fps_nframes++;
    fps_dt = current_time_s - fps_last_time_s;
    if (fps_dt > FPS_GRANULARITY_S) {
        printf("FPS = %f\n", fps_nframes / fps_dt);
        fps_last_time_s = current_time_s;
        fps_nframes = 0;
    }
}

