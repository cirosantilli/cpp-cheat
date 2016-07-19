/*
All state is updated at a single time.

Speed differences are controlled by frequency dividers.
*/

#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600
#define RECTS_PER_WINDOW (10)
#define RECT_WIDTH (WINDOW_WIDTH / RECTS_PER_WINDOW)
#define FASTEST_TICK_PERIOD (1.0 / 16.0)
#define NORMAL_FREQUENCY_DIVIDER 2
#define FAST_FREQUENCY_DIVIDER 1
#define GRAVITY_FREQUENCY_DIVIDER 4
#define MCD_FREQUENCY_DIVIDER 4

typedef struct {
    unsigned int x;
    unsigned int y;
    int speed_x;
    int speed_y;
} PlayerState;

unsigned int get_pos(int x, int speed) {
    x = (x + speed) % RECTS_PER_WINDOW;
    if (x < 0)
        x += RECTS_PER_WINDOW;
    return x;
}

void draw_player(
    PlayerState *player_state,
    SDL_Renderer *renderer,
    unsigned int r,
    unsigned int g,
    unsigned int b
) {
    SDL_Rect rect;
    rect.w = RECT_WIDTH;
    rect.h = RECT_WIDTH;
    rect.x = player_state->x * RECT_WIDTH;
    rect.y = player_state->y * RECT_WIDTH;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void update_player(
    PlayerState *player_state
) {
    if (player_state->speed_x || player_state->speed_y) {
        player_state->x = get_pos(player_state->x, player_state->speed_x);
        player_state->y = get_pos(player_state->y, player_state->speed_y);
    }
}

void init_state(
    PlayerState *player_state_0,
    PlayerState *player_state_1,
    double *last_tick_time_s,
    unsigned int *frequency_divider_counter,
    unsigned int *player_move_frequency_divider
) {
    *frequency_divider_counter = 0;
    *last_tick_time_s = SDL_GetTicks() / 1000.0;
    *player_move_frequency_divider = NORMAL_FREQUENCY_DIVIDER;
    player_state_0->x = RECTS_PER_WINDOW / 5;
    player_state_0->y = RECTS_PER_WINDOW / 2;
    player_state_0->speed_x = 0;
    player_state_0->speed_y = 0;
    player_state_1->x = 4 * RECTS_PER_WINDOW / 5;
    player_state_1->y = RECTS_PER_WINDOW / 2;
    player_state_1->speed_x = 0;
    player_state_1->speed_y = 0;
}

int main(void) {
    PlayerState player_state_0, player_state_1;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    double current_time_s, last_tick_time_s;
    unsigned int frequency_divider_counter, player_move_frequency_divider;
    unsigned int current_time, last_time;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "asdw: move red | jkli: move blue | space: move faster | esc: restart | q: quit");

main_loop:
    init_state(
        &player_state_0,
        &player_state_1,
        &last_tick_time_s,
        &frequency_divider_counter,
        &player_move_frequency_divider
    );
    while (1) {
        current_time = SDL_GetTicks();
        current_time_s = current_time / 1000.0;
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                goto quit;
            } else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        goto main_loop;

                    case SDLK_SPACE:
                        player_move_frequency_divider = FAST_FREQUENCY_DIVIDER;
                        break;

                    case SDLK_q:
                        goto quit;

                    case SDLK_a:
                        player_state_0.speed_x = -1;
                        break;
                    case SDLK_d:
                        player_state_0.speed_x = 1;
                        break;
                    case SDLK_w:
                        player_state_0.speed_y = -1;
                        break;
                    case SDLK_s:
                        player_state_0.speed_y = 1;
                        break;

                    case SDLK_j:
                        player_state_1.speed_x = -1;
                        break;
                    case SDLK_l:
                        player_state_1.speed_x = 1;
                        break;
                    case SDLK_i:
                        player_state_1.speed_y = -1;
                        break;
                    case SDLK_k:
                        player_state_1.speed_y = 1;
                        break;

                    default:
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    case SDLK_SPACE:
                        player_move_frequency_divider = NORMAL_FREQUENCY_DIVIDER;
                        break;

                    case SDLK_a:
                    case SDLK_d:
                        player_state_0.speed_x = 0;
                        break;
                    case SDLK_w:
                    case SDLK_s:
                        player_state_0.speed_y = 0;
                        break;

                    case SDLK_j:
                    case SDLK_l:
                        player_state_1.speed_x = 0;
                        break;
                    case SDLK_i:
                    case SDLK_k:
                        player_state_1.speed_y = 0;
                        break;

                    default:
                        break;
                }
            }
        }
        if (current_time != last_time) {
            if (current_time_s - last_tick_time_s > FASTEST_TICK_PERIOD) {
                /* TODO this is broken. It should be possible to overcome gravity with a fast up movement. */
                if (frequency_divider_counter % GRAVITY_FREQUENCY_DIVIDER == 0) {
                    player_state_0.speed_y = 1;
                    player_state_1.speed_y = 1;
                }
                if (frequency_divider_counter % player_move_frequency_divider == 0) {
                    update_player(&player_state_0);
                    update_player(&player_state_1);
                }
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);
                draw_player(
                    &player_state_0,
                    renderer,
                    255,
                    0,
                    0
                );
                draw_player(
                    &player_state_1,
                    renderer,
                    0,
                    0,
                    255
                );
                SDL_RenderPresent(renderer);
                last_tick_time_s = current_time_s;
                frequency_divider_counter++;
                if (frequency_divider_counter == MCD_FREQUENCY_DIVIDER)
                    frequency_divider_counter = 0;
            }
        }
        last_time = current_time;
    }
quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
