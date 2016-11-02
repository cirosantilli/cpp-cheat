/*Some basic inertia / friction on a single body.

Gives a strong sense of realism.

Makes you want to play around with two or more bodies and collision detection,
but that can only lead to a time consuming broken re-implementation of a subset
of Box2D... right?
*/

#include "common.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT WINDOW_WIDTH
#define WINDOW_CENTER_X (WINDOW_WIDTH / 2)
#define WINDOW_CENTER_Y (WINDOW_HEIGHT / 2)
#define WINDOW_HEIGHT WINDOW_WIDTH
#define RECT_WIDTH (WINDOW_WIDTH / 50)
#define RECT_HEIGHT RECT_WIDTH
#define MAX_RECT_POS (WINDOW_WIDTH - RECT_WIDTH)
/*
 * Accelerations in meters per second.
 *
 * I like to think like this: how long will it take to cross the screen
 * starting from speed 0 with this constant acceleration?
 *
 * Remember that:
 *
 * x = acc * t^2 / 2
 *
 * so if:
 *
 * - `acc = MAX_RECT_POS * 2.0`  it takes 1       second  to cross the screen
 * - `acc = MAX_RECT_POS`        it takes sqrt(2) seconds to cross the screen
 * - `acc = MAX_RECT_POS / 2.0`  it takes 2       seconds to cross the screen
 **/
#define ACC_USER_METERS_PER_SECOND     (MAX_RECT_POS)
#define ACC_FRICTION_METERS_PER_SECOND (MAX_RECT_POS / 2.5)
#define ACC_GRAVITY_METERS_PER_SECOND  (MAX_RECT_POS / 1.5)

typedef struct {
    double
        x,
        y,
        speed_x,
        speed_y
    ;
} PlayerState;

void init_state(
    PlayerState *player_state,
    double *user_acc_x,
    double *user_acc_y,
    unsigned int *last_time
) {
    player_state->x = WINDOW_WIDTH / 2.0;
    player_state->y = WINDOW_HEIGHT / 2.0;
    player_state->speed_x = 0.0;
    player_state->speed_y = 0.0;

    /* Encode if the movement keys are initially pressed or not. */
    *user_acc_x = 0.0;
    *user_acc_y = 0.0;

    *last_time = SDL_GetTicks();
    common_fps_init();
}

double get_new_coord(double x, double step) {
    x += step;
    x = fmod(x, MAX_RECT_POS);
    if (x < 0)
        x = MAX_RECT_POS;
    return x;
}

/* A constant force in the direction opposite to movement,
 * or stop the movement if it is too slow.
 * */
double apply_constant_friction(double speed, double dt) {
    double dv;
    dv = ACC_FRICTION_METERS_PER_SECOND * dt;
    if (fabs(speed) < dv)
        speed = 0.0;
    else
        speed -= copysign(dv, speed);
    return speed;
}

int main(void) {
    PlayerState player_state;
    SDL_Event event;
    SDL_Rect rect, rect_sun;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int quit = 0;
    unsigned int current_time, last_time;
    double dt, acc_x, acc_y, user_acc_x, user_acc_y;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "arrow keys: accelerate | esc: reset | q: quit");
    rect.w = RECT_WIDTH;
    rect.h = RECT_HEIGHT;
    rect_sun.w = RECT_WIDTH;
    rect_sun.h = RECT_HEIGHT;
    rect_sun.x = WINDOW_CENTER_X;
    rect_sun.y = WINDOW_CENTER_Y;
main_loop:
    init_state(&player_state, &user_acc_x, &user_acc_y, &last_time);
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        user_acc_x = -1;
                        break;
                    case SDLK_RIGHT:
                        user_acc_x = 1;
                        break;
                    case SDLK_UP:
                        user_acc_y = -1;
                        break;
                    case SDLK_DOWN:
                        user_acc_y = 1;
                        break;
                    case SDLK_ESCAPE:
                        goto main_loop;
                    case SDLK_q:
                        goto quit;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        user_acc_x = 0;
                        break;
                    case SDLK_UP:
                    case SDLK_DOWN:
                        user_acc_y = 0;
                        break;
                }
            }
        }
        current_time = SDL_GetTicks();
        if (current_time != last_time) {
            dt = (current_time - last_time) / 1000.0;

            /* Player movement. */
            acc_x = user_acc_x * ACC_USER_METERS_PER_SECOND;
            acc_y = user_acc_y * ACC_USER_METERS_PER_SECOND;

            /* Other forces. */
            {
                /* Constant gravity down. */
                /*acc_y += ACC_GRAVITY_METERS_PER_SECOND;*/

                /* Constant gravity to center of screen, the "sun". */
                {
                    double dx = player_state.x - WINDOW_CENTER_X;
                    double dy = player_state.y - WINDOW_CENTER_Y;
                    double angle = atan2(dy, dx);
                    double hyp = hypot(dx, dy);

                    /* TODO Failed attempt at force proportional to inverse square of distance. */
                    /*double mod = hyp > 0.001 ? hyp : 1.0;*/
                    /*double mod2 = mod * mod;*/

                    acc_x -= cos(angle) * ACC_GRAVITY_METERS_PER_SECOND;
                    acc_y -= sin(angle) * ACC_GRAVITY_METERS_PER_SECOND;
                }
            }

            /* Update speed. */
            player_state.speed_x += dt * acc_x;
            player_state.speed_y += dt * acc_y;

            /*
            Constant friction
            - decelerates very quickly
            - speed is limited to a maximum
            Ideally this force should be added to the acceleration simply,
            but we must consider the case where the object stops completely
            because of it separately.
            */
            /*player_state.speed_x = apply_constant_friction(player_state.speed_x, dt);*/
            /*player_state.speed_y = apply_constant_friction(player_state.speed_y, dt);*/

            /* Friction  proportional to speed:
            - decelerates very quickly
            - speed is limited to a maximum
            Does not feel very natural.
            */
            /* player_state.speed_x *= 0.999; */
            /* player_state.speed_y *= 0.999; */

            /* Update position. */
            player_state.x = get_new_coord(player_state.x, player_state.speed_x * dt);
            player_state.y = get_new_coord(player_state.y, player_state.speed_y * dt);

            /* Render. */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            rect.x = player_state.x;
            rect.y = player_state.y;
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &rect_sun);
            SDL_RenderPresent(renderer);

            /* Update time. */
            last_time = current_time;
        }
        common_fps_update_and_print();
    }
quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
