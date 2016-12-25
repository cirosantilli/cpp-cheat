/*
Basic texture example.

Much faster than SDL_RenderDrawPoint calls.

Uses GL textures under the hood.

SDL_TEXTUREACCESS_STREAMING is key to allow us to write to the texture from CPU.
*/

#include "common.h"

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Window *window = NULL;
    Uint8 *base;
    int pitch;
    void *pixels = NULL;
    const unsigned int
        WINDOW_WIDTH = 500,
        WINDOW_HEIGHT = WINDOW_WIDTH;
    const double
        SPEED = WINDOW_WIDTH / 10.0,
        CENTER_X = WINDOW_WIDTH / 2.0,
        CENTER_Y = WINDOW_HEIGHT / 2.0,
        PERIOD = WINDOW_WIDTH / 10.0,
        PI2 = 2.0 * acos(-1.0);
    double dt, initial_time;
    float z;
    unsigned int x, xc, y, yc;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    initial_time = common_get_secs();
    common_fps_init();
    while (1) {
        dt = common_get_secs() - initial_time;
        SDL_LockTexture(texture, NULL, &pixels, &pitch);
        for (x = 0; x < WINDOW_WIDTH; x++) {
            for (y = 0; y < WINDOW_HEIGHT; y++) {
                xc = CENTER_X - x;
                yc = CENTER_Y - y;
                /*z = COMMON_COLOR_MAX * 0.5 * (1.0 + (sin(PI2 * (sqrt(xc*xc + yc*yc) - SPEED * dt) / PERIOD)));*/
                z = (int)(x + y + SPEED * dt) % COMMON_COLOR_MAX;
                base = ((Uint8 *)pixels) + (4 * (x * WINDOW_WIDTH + y));
                base[0] = 0;
                base[1] = 0;
                base[2] = z;
                base[3] = COMMON_COLOR_MAX;
            }
        }
        SDL_UnlockTexture(texture);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        common_fps_update_and_print();
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
