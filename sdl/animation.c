/*
TODO find source saying the good way to control speed.

Simple movement that has an absolute equation.
*/

#include "common.h"

#define WINDOW_WIDTH 600
#define RECT_WIDTH WINDOW_WIDTH / 30
#define MAX_RECT_POS (WINDOW_WIDTH - RECT_WIDTH)
#define SCREENS_PER_SECOND 1.0

int main(void) {
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
    unsigned int initial_time;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    rect.y = WINDOW_WIDTH / 2;
    rect.w = RECT_WIDTH;
    rect.h = RECT_WIDTH;
    initial_time = SDL_GetTicks();
    common_fps_init();
    while (1) {
        rect.x = ((int)(
                SCREENS_PER_SECOND
                * (MAX_RECT_POS)
                * (SDL_GetTicks() - initial_time) / 1000.0))
                % (MAX_RECT_POS);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        common_fps_update_and_print();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
