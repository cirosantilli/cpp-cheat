/*
Random walk.
*/

#include "common.h"

#define WINDOW_WIDTH 600
#define RECT_WIDTH (WINDOW_WIDTH / 30)
#define MAX_RECT_POS (WINDOW_WIDTH - RECT_WIDTH)
#define SCREENS_PER_SECOND 10.0

double rand_one() {
    return -1.0 + 2.0 * (rand() / (double)RAND_MAX);
}

double get_coord(double *x, double magnitude) {
    *x += magnitude * rand_one();
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
    double x, y, magnitude;
    unsigned int current_time, last_time;

    srand(time(NULL));
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    rect.x = WINDOW_WIDTH / 2;
    rect.y = WINDOW_WIDTH / 2;
    rect.w = RECT_WIDTH;
    rect.h = RECT_WIDTH;
    last_time = SDL_GetTicks();
    common_fps_init();
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        current_time = SDL_GetTicks();
        if (current_time != last_time) {
            magnitude = SCREENS_PER_SECOND * MAX_RECT_POS * (current_time - last_time) / 1000.0;
            rect.x = get_coord(&x, magnitude);
            rect.y = get_coord(&y, magnitude);
            last_time = current_time;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
        }
        common_fps_update_and_print();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
