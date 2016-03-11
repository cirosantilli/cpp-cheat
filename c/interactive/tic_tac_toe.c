#include "common.h"

static const char * const names[] = {"circle", "cross"};
static const char * const marker[] = {"o", "x"};
enum constexpr { WIDTH = 3, NSTATES = WIDTH * WIDTH };
typedef enum { PLAYER_CROSS = 0, PLAYER_CIRCLE = 1, PLAYER_EMPTY = 2 } Player;

static void render(Player *state) {
    int i;
    int j;
    int pos;
    int state_pos;

    for (i = 0; i < WIDTH; ++i) {
        for (j = 0; j < WIDTH; ++j) {
            pos = i * WIDTH + j;
            state_pos = state[pos];
            if (state_pos != PLAYER_EMPTY)
                printf("%s", marker[state_pos]);
            else
                printf("%d", pos + 1);
        }
        puts("");
    }
}

static int won(Player *state, Player current_player) {
    int i;
    int j;

    /* Horizontal. */
    for (i = 0; i < WIDTH; ++i) {
        for (j = 0; j < WIDTH; ++j) {
            if (state[i * WIDTH + j] != current_player)
                break;
        }
        if (j == WIDTH)
            return 1;
    }

    /* Vertical. */
    for (j = 0; j < WIDTH; ++j) {
        for (i = 0; i < WIDTH; ++i) {
            if (state[i * WIDTH + j] != current_player)
                break;
        }
        if (i == WIDTH)
            return 1;
    }

    /* Diagonal. */
    for (i = 0; i < WIDTH; ++i) {
        if (state[i * WIDTH + i] != current_player)
            break;
    }
    if (i == WIDTH)
        return 1;

    /* Anti-diagonal. */
    j = WIDTH - 1;
    for (i = 0; i < WIDTH; ++i, --j) {
        if (state[i * WIDTH + j] != current_player)
            break;
    }
    if (i == WIDTH)
        return 1;

    return 0;
}

static void update_state(Player *state, Player current_player) {
    char s[2] = {'\0', '\0'};
    char *end;
    int c;
    int i;
    int dump;
    int pos;
    while (1) {
        printf("%s moves. Enter a digit digit between 1-9 and press enter:\n", names[current_player]);
        c = getchar();
        /* Clear stdin. */
        while ((dump = getchar()) != EOF && dump != '\n') {}
        if (c < '1' || c > '9') {
            puts("Not between 1-9.");
            continue;
        }
        s[0] = c;
        pos = strtol(s, &end, 10) - 1;
        if (state[pos] != PLAYER_EMPTY) {
            puts("Case already taken.");
            continue;
        }
        break;
    }
    state[pos] = current_player;
    return;
}

int main() {
    Player current_player = PLAYER_CIRCLE;
    Player state[NSTATES];
    const char *s;
    int i;
    int move;
    int turn = 0;

    for (i = 0; i < NSTATES; ++i)
        state[i] = PLAYER_EMPTY;
    render(state);
    while (1) {
        if (turn == NSTATES) {
            puts("draw");
            break;
        }
        update_state(state, current_player);
        render(state);
        if (won(state, current_player)) {
            printf("%s won\n", names[current_player]);
            break;
        }
        current_player = (current_player + 1) % 2;
        i++;
    }
    return EXIT_SUCCESS;
}
