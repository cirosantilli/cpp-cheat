/*
Player movements are not synchronized.

To do so, we could:

- discretize time into time windows
- check if a keypress was done in a time slot
- update all players at once

but that would lead to a delay between keypress and movement.

If the time windows are very small, the delay cannot be seen,
but then the players would move too fast in this discrete world.

Without sync like in here, we have to keep one timer per event type,
which is cumbersome.
*/

#include "common.h"

#define WINDOW_WIDTH 600
#define RECTS_PER_WINDOW (10)
#define RECT_WIDTH (WINDOW_WIDTH / RECTS_PER_WINDOW)
#define MOVE_DELAY_NORMAL 0.25
#define MOVE_DELAY_FAST (MOVE_DELAY_NORMAL / 4.0)

typedef struct {
    unsigned int x;
    unsigned int y;
    int speed_x;
    int speed_y;
    double last_move_time_s;
} PlayerState;

unsigned int get_pos(int x, int speed) {
    x = (x + speed) % RECTS_PER_WINDOW;
    if (x < 0)
        x += RECTS_PER_WINDOW;
    return x;
}

void update_and_draw_player(
        SDL_Renderer *renderer,
        PlayerState *player_state,
        double current_time_s,
        double move_delay,
        unsigned int r,
        unsigned int g,
        unsigned int b) {
    SDL_Rect rect;
    rect.w = RECT_WIDTH;
    rect.h = RECT_WIDTH;
    if (
        (player_state->speed_x || player_state->speed_y)
        && current_time_s - player_state->last_move_time_s > move_delay
    ) {
        player_state->x = get_pos(player_state->x, player_state->speed_x);
        player_state->y = get_pos(player_state->y, player_state->speed_y);
        player_state->last_move_time_s = current_time_s;
    }
    rect.x = player_state->x * RECT_WIDTH;
    rect.y = player_state->y * RECT_WIDTH;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void init_state(
        PlayerState *player_state_0,
        PlayerState *player_state_1,
        double *move_delay) {
    *move_delay = MOVE_DELAY_NORMAL;
    player_state_0->x = RECTS_PER_WINDOW / 5;
    player_state_0->y = RECTS_PER_WINDOW / 2;
    player_state_0->speed_x = 0;
    player_state_0->speed_y = 0;
    player_state_0->last_move_time_s = SDL_GetTicks() / 1000.0;
    player_state_1->x = 4 * RECTS_PER_WINDOW / 5;
    player_state_1->y = RECTS_PER_WINDOW / 2;
    player_state_1->speed_x = 0;
    player_state_1->speed_y = 0;
    player_state_1->last_move_time_s = player_state_0->last_move_time_s;
    common_fps_init();
}

int main(void) {
    PlayerState player_state_0, player_state_1;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    double current_time_s;
    double move_delay = MOVE_DELAY_NORMAL;
    unsigned int current_time, last_time;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "asdw: move red | jkli: move blue | space: move faster | esc: restart | q: quit");
main_loop:
    init_state(&player_state_0, &player_state_1, &move_delay);
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
                        move_delay = MOVE_DELAY_FAST;
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
                        move_delay = MOVE_DELAY_NORMAL;
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
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            update_and_draw_player(
                renderer,
                &player_state_0,
                current_time_s,
                move_delay,
                255,
                0,
                0
            );
            update_and_draw_player(
                renderer,
                &player_state_1,
                current_time_s,
                move_delay,
                0,
                0,
                255
            );
            SDL_RenderPresent(renderer);
        }
        last_time = current_time;
        common_fps_update_and_print();
    }
quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
