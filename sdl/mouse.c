/* Print mouse position to stdout. */

#include "common.h"

int main(void) {
    SDL_Event event;
    SDL_Window *window;
    int x, y, last_x, last_y;
    window = SDL_CreateWindow(__FILE__, 0, 0, 500, 500, SDL_WINDOW_OPENGL);
    x = 0;
    y = 0;
    last_x = 0;
    last_y = 0;
    common_fps_init();
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        SDL_GetMouseState(&x, &y);
        if (x != last_x || y != last_y) {
            printf("%d %d\n", x, y);
            last_x = x;
            last_y = y;
        }
        common_fps_update_and_print();
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
