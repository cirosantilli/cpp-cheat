/*
Many functions of SDL can fail.

When that can happen, they return a negative number, and the error gets stored in SDL_GetError().

We can then use SDL_LogError to log the problem, and exit.

Since too many functions can fail, this is the only example in which we will do full error checking.

But in production code, you should always do it.
*/

#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600

#define SDL_ERROR(x) if (x < 0) { \
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init failed: %s\n", SDL_GetError()); \
    exit(EXIT_FAILURE); }

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;

    SDL_ERROR(SDL_Init(SDL_INIT_VIDEO));
    SDL_ERROR(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer));
    SDL_ERROR(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0));
    SDL_ERROR(SDL_RenderClear(renderer));
    SDL_ERROR(SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255));
    for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_ERROR(SDL_RenderDrawPoint(renderer, i, i));
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
