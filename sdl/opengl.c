/*
Docs: https://wiki.libsdl.org/SDL_GL_CreateContext

Expected outcome: monocolor pink screen.
*/

#include <stdlib.h>

#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>

int main(void) {
    SDL_Event event;
    SDL_Window *window;
    SDL_GLContext gl_context;
    const unsigned int
        WINDOW_WIDTH = 500,
        WINDOW_HEIGHT = WINDOW_WIDTH
    ;

    /* Window system. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    window = SDL_CreateWindow(__FILE__, 0, 0,
            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    gl_context = SDL_GL_CreateContext(window);
    glewInit();

    /* Whatever GL draw calls you want. */
    glClearColor(1.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    /* Main loop. */
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    /* Cleanup. */
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
