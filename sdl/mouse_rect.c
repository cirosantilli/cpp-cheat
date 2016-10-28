#include "common.h"

#define WINDOW_WIDTH 600

int main(void) {
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int x, y, half_w, half_h;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    rect.x = WINDOW_WIDTH / 2;
    rect.y = WINDOW_WIDTH / 2;
    rect.w = WINDOW_WIDTH / 6;
    rect.h = WINDOW_WIDTH / 6;
    half_w = rect.w / 2;
    half_h = rect.h / 2;
    common_fps_init();
    while (1) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        SDL_GetMouseState(&x, &y);
        if (x != rect.x || y != rect.y) {
            rect.x = x - half_w;
            rect.y = y - half_h;
        }
        common_fps_update_and_print();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
