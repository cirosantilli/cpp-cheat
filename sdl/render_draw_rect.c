#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Rect rect;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    rect.x = WINDOW_WIDTH / 2;
    rect.y = WINDOW_WIDTH / 3;
    rect.w = WINDOW_WIDTH / 6;
    rect.h = WINDOW_WIDTH / 12;
    /* Make it filled. */
    /*SDL_RenderFillRect(renderer, &rect);*/
    /*SDL_RenderDrawRect(renderer, &rect);*/
    /* Same as the above. */
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
