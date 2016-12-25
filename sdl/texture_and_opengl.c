/*
Mixing raw GL calls with wrapped textures (SDL_RenderCopy).
*/

#include "common.h"

int main(void) {
    SDL_GLContext gl_context;
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Window *window = NULL;
    Uint8 *base;
    const unsigned int
        WINDOW_WIDTH = 500,
        WINDOW_HEIGHT = WINDOW_WIDTH
    ;
    int pitch;
    unsigned int x, y;
    void *pixels = NULL;

    /* Window setup. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        __FILE__, 0, 0,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL
    );
    renderer = SDL_CreateRenderer(window, 0, 0);
    gl_context = SDL_GL_CreateContext(window);

    /* GL drawing. */
    glClearColor(1.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Wrapped texture drawing. */
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_LockTexture(texture, NULL, &pixels, &pitch);
    for (x = 0; x < WINDOW_WIDTH; x++) {
        for (y = 0; y < WINDOW_HEIGHT; y++) {
            base = ((Uint8 *)pixels) + (4 * (x * WINDOW_WIDTH + y));
            base[0] = 0;
            base[1] = 0;
            base[2] = COMMON_COLOR_MAX;
            base[3] = COMMON_COLOR_MAX;
        }
    }
    SDL_UnlockTexture(texture);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = WINDOW_WIDTH / 2;
    rect.h = WINDOW_HEIGHT / 2;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_GL_SwapWindow(window);

    /* Main loop. */
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    /* Cleanup. */
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
