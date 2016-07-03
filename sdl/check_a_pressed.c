/*
Check if the a key is pressed.
Expected outcome: screen becomes red when it is.
*/

#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT (WINDOW_WIDTH)

int main(void) {
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int pressed;
    int quit;

    quit = 0;
    pressed = 0;
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    rect.x = 0;
    rect.y = 0;
    rect.w = WINDOW_WIDTH;
    rect.h = WINDOW_HEIGHT;
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_a:
                        pressed = 1;
                        break;
                    default:
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    case SDLK_a:
                        pressed = 0;
                    default:
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        if (pressed)
            SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
