/*
Draw a rectangle with points.

Bad idea, because the GPU can make that operation faster for quads,
and SDL_rect uses that power by default.

So just to see how bad the naive method is.
*/

#include "common.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT WINDOW_WIDTH

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int x, y;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_RenderPresent(renderer);
    common_fps_init();
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        for (x = 0; x < WINDOW_WIDTH; ++x) {
            for (y = 0; y < WINDOW_HEIGHT; ++y) {
                if ((x + y) & 1) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
        SDL_RenderPresent(renderer);
        common_fps_update_and_print();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
