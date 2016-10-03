/*
Plot 2D function of time.

Allow the following methods to compare speeds:

-   SDL_RenderDrawPoint, slowest.

-   SDL_RenderCopy , faster, very close to the no SDL method

-   no SDL: just to calculate the maximum FPS if we weren't doing video IO, just pixel calculation.

    This is as fast as we can possibly go without pushing CPU calculations to a GPU shader.

    To have an idea, a 500 x 500 window does 2.5e4 has pixels, x60 FPS gives 1.5e6

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

#include "common.h"

/*
Turn SDL on or off.
If off, no window is created, but computations are still run.
Play with those to try to increase FPS and find out if the limiting factor is computation or display.
*/
#define SDL 1

#define COLOR_MAX 255

int main(void) {
#if SDL
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *texture = NULL;
    void *pixels;
    Uint8 *base;
    /* TODO: is it mandatory to use this? Maybe SDL_LockTexture
     * will make the array non continuous to improve alignment? */
    int pitch;
#else
    double sum;
#endif
    const unsigned int
        WINDOW_WIDTH = 500,
        WINDOW_HEIGHT = WINDOW_WIDTH;
    const double
        SPEED = WINDOW_WIDTH / 10.0,
        CENTER_X = WINDOW_WIDTH / 2.0,
        CENTER_Y = WINDOW_HEIGHT / 2.0,
        PERIOD = WINDOW_WIDTH / 10.0,
        PI2 = 2.0 * acos(-1.0);
    double dt, initial_time;
    float z;
    unsigned int x, xc, y, yc;

#if SDL
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
#endif
    initial_time = common_get_secs();
    common_fps_init();
    while (1) {
        dt = common_get_secs() - initial_time;
        for (x = 0; x < WINDOW_WIDTH; x++) {
            for (y = 0; y < WINDOW_HEIGHT; y++) {
                xc = CENTER_X - x;
                yc = CENTER_Y - y;
                z = COLOR_MAX * 0.5 * (1.0 + (sin(PI2 * (sqrt(xc*xc + yc*yc) - SPEED * dt) / PERIOD)));
                /*z = (int)(x + y + SPEED * dt) % COLOR_MAX;*/
#if SDL
                SDL_SetRenderDrawColor(renderer, z, 0, 0, COLOR_MAX);
                SDL_RenderDrawPoint(renderer, x, y);
#else
                sum += z;
#endif
            }
        }
#if SDL
        SDL_RenderPresent(renderer);
        common_fps_update_and_print();
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
