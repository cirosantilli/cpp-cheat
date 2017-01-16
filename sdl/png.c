
/*
Basic texture example.

Much faster than SDL_RenderDrawPoint calls.

Uses GL textures under the hood.

SDL_TEXTUREACCESS_STREAMING is key to allow us to write to the texture from CPU.
*/

#include "common.h"

SDL_Texture* load_image(SDL_Renderer *renderer, char *path) {
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    surface = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Window *window = NULL;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        COMMON_WINDOW_WIDTH, COMMON_WINDOW_WIDTH,
        0, &window, &renderer
    );
    IMG_Init(IMG_INIT_PNG);
    texture = load_image(renderer, "flower.png");
    common_fps_init();
    while (1) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        common_fps_update_and_print();
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
