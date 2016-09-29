/*
Plot a 1D picture that is a function of x and time.

Up to 3 plots at once: one per color.
*/

#include <math.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#define COLOR_MAX 255

int main(void) {
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
    unsigned int x;
    const unsigned int WINDOW_WIDTH = 600;
    const unsigned int WINDOW_HEIGHT = WINDOW_WIDTH;
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
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    rect.y = 0;
    rect.w = 1;
    rect.h = WINDOW_HEIGHT;
    initial_time = SDL_GetTicks() / 1000.0;
    fps_last_time = initial_time;
    nframes = 0;
    while (1) {
        t = SDL_GetTicks() / 1000.0;
        dt = t - initial_time;
        for (x = 0; x < WINDOW_WIDTH; x++) {
            rect.x = x;
            SDL_SetRenderDrawColor(
                    renderer,
                    COLOR_MAX * 0.5 * (1.0 + (sin(PI2 * (x + SPEED * dt) / PERIOD))),
                    0,
                    0,
                    COLOR_MAX);
            SDL_RenderFillRect(renderer, &rect);
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
