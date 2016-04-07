/*
Plot 2D function of time.

TODO possible to do it faster? Just the loop without anything inside
and only FPS calculation and no optimization max out at 70 FPS already.
Look into surfaces, textures.

- http://stackoverflow.com/questions/20753726/rendering-pixels-from-array-of-rgb-values-in-sdl-1-2
- http://stackoverflow.com/questions/28279242/how-to-render-a-pixel-array-most-efficiently-to-a-window-in-c
- http://stackoverflow.com/questions/20348616/how-to-create-a-color-gradient-in-sdl
- http://stackoverflow.com/questions/21392755/difference-between-surface-and-texture-sdl-general

TODO: get vsync right.
*/

#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define COLOR_MAX 255

int main(void) {
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
    unsigned int x;
    unsigned int y;
    unsigned int xc;
    unsigned int yc;
    const unsigned int WINDOW_WIDTH = 600;
    const unsigned int WINDOW_HEIGHT = WINDOW_WIDTH;
    const double CENTER_X = WINDOW_WIDTH / 2.0;
    const double CENTER_Y = WINDOW_HEIGHT / 2.0;
    const double PERIOD = (WINDOW_WIDTH / 10.0);
    const double SPEED = (WINDOW_WIDTH / 10.0);
    const double PI2 = 2.0 * acos(-1.0);
    double dt;
    double fps_last_time;
    double fps_dt;
    double initial_time;
    double t;
    int nframes;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    initial_time = SDL_GetTicks() / 1000.0;
    fps_last_time = initial_time;
    nframes = 0;
    while (1) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        for (x = 0; x < WINDOW_WIDTH; x++) {
            for (y = 0; y < WINDOW_HEIGHT; y++) {
                t = SDL_GetTicks() / 1000.0;
                dt = t - initial_time;
                xc = CENTER_X - x;
                yc = CENTER_Y - y;
                SDL_SetRenderDrawColor(
                        renderer,
                        COLOR_MAX * 0.5 * (1.0 + (sin(PI2 * (sqrt(xc*xc + yc*yc) - SPEED * dt) / PERIOD))),
                        0,
                        0,
                        COLOR_MAX);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
        SDL_RenderPresent(renderer);
        nframes++;
        fps_dt = t - fps_last_time;
        if (fps_dt > 0.25) {
            printf("FPS = %f\n", nframes / fps_dt);
            fps_last_time = t;
            nframes = 0;
        }
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
