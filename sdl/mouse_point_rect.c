#include "common.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT WINDOW_WIDTH

int main(void) {
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i, j, x, y, half_w, half_h;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    rect.x = WINDOW_WIDTH / 2;
    rect.y = WINDOW_WIDTH / 2;
    rect.w = 3 * WINDOW_WIDTH / 4;
    rect.h = 3 * WINDOW_WIDTH / 4;
    half_w = rect.w / 2;
    half_h = rect.h / 2;
    common_fps_init();
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        SDL_GetMouseState(&x, &y);
        if (x != rect.x || y != rect.y) {
            rect.x = x - half_w;
            rect.y = y - half_h;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            for (i = 0; i < rect.w; ++i) {
                for (j = 0; j < rect.h; ++j) {
                    if ((i + j) & 1) {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_RenderDrawPoint(renderer, x + i - half_w, y + j - half_h);
                    }
                }
            }
            SDL_RenderPresent(renderer);
        }
        common_fps_update_and_print();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
