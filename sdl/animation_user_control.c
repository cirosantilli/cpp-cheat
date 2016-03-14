/*
Use controls a square.

https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html
*/

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600
#define RECT_WIDTH (WINDOW_WIDTH / 30)
#define MAX_RECT_POS (WINDOW_WIDTH - RECT_WIDTH)
#define SCREENS_PER_SECOND 1.0

double get_coord(double *x, double step) {
    *x += step;
    *x = fmod(*x, MAX_RECT_POS);
    if (*x < 0)
        *x = MAX_RECT_POS;
    return *x;
}

int main(void) {
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int quit = 0;
    unsigned int current_time;
    double step;
    double speed_x;
    double speed_y;
    unsigned int last_time;
    double x;
    double y;

    srand(time(NULL));
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    rect.x = WINDOW_WIDTH / 2;
    rect.y = WINDOW_WIDTH / 2;
    rect.w = RECT_WIDTH;
    rect.h = RECT_WIDTH;
    last_time = SDL_GetTicks();
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                        speed_x = -1;
                        break;
                    case SDLK_RIGHT:
                        speed_x = 1;
                        break;
                    case SDLK_UP:
                        speed_y = -1;
                        break;
                    case SDLK_DOWN:
                        speed_y = 1;
                        break;
                    default:
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                        speed_x = 0;
                        break;
                    case SDLK_RIGHT:
                        speed_x = 0;
                        break;
                    case SDLK_UP:
                        speed_y = 0;
                        break;
                    case SDLK_DOWN:
                        speed_y = 0;
                        break;
                    default:
                        break;
                }
            }
        }
        current_time = SDL_GetTicks();
        if (current_time != last_time) {
            step = SCREENS_PER_SECOND * MAX_RECT_POS * (current_time - last_time) / 1000.0;
            rect.x = get_coord(&x, step * speed_x);
            rect.y = get_coord(&y, step * speed_y);
            last_time = current_time;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
