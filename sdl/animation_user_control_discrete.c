/*
Use controls a square in a very discrete world, e.g. Tetris.

Using float coordinates would lead to an internal invisible state,
which is weird (you can be either at the left or right corner of the active square).
*/

#include "common.h"

#define WINDOW_WIDTH 600
#define RECTS_PER_WINDOW (10)
#define RECT_WIDTH (WINDOW_WIDTH / RECTS_PER_WINDOW)
#define SCREENS_PER_SECOND 1.0
#define KEYPRESS_DELAY 0.25

unsigned int get_pos(int x, int speed) {
    x = (x + speed) % RECTS_PER_WINDOW;
    if (x < 0)
        x += RECTS_PER_WINDOW;
    return x;
}

int main(void) {
    SDL_Event event;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    SDL_Window *window;
    double current_time_s, last_key_pressed_time_s;
    unsigned int x = RECTS_PER_WINDOW / 2,
                 y = RECTS_PER_WINDOW / 2;
    int key_pressed,
        quit = 0,
        speed_x = 0,
        speed_y = 0;
    unsigned int current_time, last_time;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "arrow keys: move");
    rect.w = RECT_WIDTH;
    rect.h = RECT_WIDTH;
    last_key_pressed_time_s = SDL_GetTicks() / 1000.0;
    common_fps_init();
    while (!quit) {
        current_time = SDL_GetTicks();
        current_time_s = current_time / 1000.0;
        while (SDL_PollEvent(&event) == 1) {
            key_pressed = 0;
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
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
                key_pressed = 1;
            } else if (event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
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
        if (current_time != last_time) {
            if (key_pressed && current_time_s - last_key_pressed_time_s > KEYPRESS_DELAY) {
                x = get_pos(x, speed_x);
                y = get_pos(y, speed_y);
                last_key_pressed_time_s = current_time_s;
            }
            rect.x = x * RECT_WIDTH;
            rect.y = y * RECT_WIDTH;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
        }
        last_time = current_time;
        common_fps_update_and_print();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
