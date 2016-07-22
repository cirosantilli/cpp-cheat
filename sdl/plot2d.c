/*
Plot 2D function of time.

Allow the following methods to compare speeds:

- SDL_RenderDrawPoint , slowest
- SDL_RenderCopy , faster, very close to the no SDL method
- no SDL: just to calculate the maximum FPS if we weren't doing video IO, just pixel calculation

Bibliography:

- http://stackoverflow.com/questions/25214556/bad-performance-with-sdl2-and-sdl-rendercopy
    Proposes SDL_TEXTUREACCESS_STREAMING + locking and unlocking.
    Looks promissing!
- http://stackoverflow.com/questions/20753726/rendering-pixels-from-array-of-rgb-values-in-sdl-1-2
- http://stackoverflow.com/questions/28279242/how-to-render-a-pixel-array-most-efficiently-to-a-window-in-c
- http://stackoverflow.com/questions/20348616/how-to-create-a-color-gradient-in-sdl
- http://stackoverflow.com/questions/21392755/difference-between-surface-and-texture-sdl-general
- http://stackoverflow.com/questions/503816/what-is-the-fastest-way-to-draw-a-2d-array-of-color-triplets-on-screen

TODO: why do I see some tearing. vsync problem?
*/

/* Input parameters. Play with those to try to increase FPS. */
#define SDL 1
#define STREAMING (SDL && 0)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if SDL
#include <SDL2/SDL.h>
#endif

#define COLOR_MAX 255

double get_secs(void) {
    struct timespec ts;
    /* C11. Use this so we can get completely rid of SDL to benchmark the CPU. */
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + (1e-9 * ts.tv_nsec);
    /*return SDL_GetTicks() / 1000.0;*/
}

int main(void) {
#if SDL
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
# if STREAMING
    SDL_Texture *texture = NULL;
    void *pixels;
    Uint8 *base;
    /* TODO: is it mandatory to use this? Maybe SDL_LockTexture
     * will make the array non continuous to improve alignment? */
    int pitch;
# endif
#else
    double sum;
#endif
    const unsigned int WINDOW_WIDTH = 600;
    const unsigned int WINDOW_HEIGHT = WINDOW_WIDTH;
    const double SPEED = (WINDOW_WIDTH / 10.0);
    const double CENTER_X = WINDOW_WIDTH / 2.0;
    const double CENTER_Y = WINDOW_HEIGHT / 2.0;
    const double PERIOD = (WINDOW_WIDTH / 10.0);
    const double PI2 = 2.0 * acos(-1.0);
    double dt;
    double fps_dt;
    double fps_last_time;
    double initial_time;
    double t;
    int fps_nframes;
    float z;
    unsigned int x;
    unsigned int xc;
    unsigned int y;
    unsigned int yc;

#if SDL
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
# if STREAMING
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
# endif
#endif
    initial_time = get_secs();
    fps_last_time = initial_time;
    fps_nframes = 0;
    while (1) {
        t = get_secs();
        dt = t - initial_time;
#if STREAMING
        SDL_LockTexture(texture, NULL, &pixels, &pitch);
#endif
        for (x = 0; x < WINDOW_WIDTH; x++) {
            for (y = 0; y < WINDOW_HEIGHT; y++) {
                xc = CENTER_X - x;
                yc = CENTER_Y - y;
                z = COLOR_MAX * 0.5 * (1.0 + (sin(PI2 * (sqrt(xc*xc + yc*yc) - SPEED * dt) / PERIOD)));
#if SDL
# if STREAMING
                base = ((Uint8 *)pixels) + (4 * (x * WINDOW_WIDTH + y));
                base[0] = 0;
                base[1] = 0;
                base[2] = z;
                base[3] = COLOR_MAX;
# else
                SDL_SetRenderDrawColor(renderer, z, 0, 0, COLOR_MAX);
                SDL_RenderDrawPoint(renderer, x, y);
# endif
#else
                sum += z;
#endif
            }
        }
#if SDL
# if STREAMING
        SDL_UnlockTexture(texture);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
# endif
        SDL_RenderPresent(renderer);
#endif
        fps_nframes++;
        fps_dt = t - fps_last_time;
        if (fps_dt > 0.25) {
            /* Produce a side-effect for the non-SDL version so that
             * it does not get optimized away. */
            printf("FPS = %f\n", fps_nframes / fps_dt);
            fps_last_time = t;
            fps_nframes = 0;
#if !SDL
            printf("%f\n", sum);
#endif
        }
#if SDL
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
#endif
    }
#if SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
    return EXIT_SUCCESS;
}
