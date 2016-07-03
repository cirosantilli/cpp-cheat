/*
Check if a key was pressed in the last loop cycle:
http://stackoverflow.com/questions/2984307/c-key-pressed-in-linux-console
*/

#include "common.h"

/*
Return a character, on -1 if none was entered.
*/
int getkey(void) {
    int character;
    int stdin_fileno;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    stdin_fileno = fileno(stdin);

    /* Save old attributes. */
    tcgetattr(stdin_fileno, &orig_term_attr);

    /* Set the terminal to raw mode. */
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    /* TODO what are those parameters? */
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(stdin_fileno, TCSANOW, &new_term_attr);

    /* Read character. */
    character = getchar();
    while (getchar() != EOF);

    /* Restore the original terminal attributes. */
    tcsetattr(stdin_fileno, TCSANOW, &orig_term_attr);

    return character;
}

int main(void) {
    int key;
    struct timespec sleep_cycle;
    sleep_cycle.tv_sec = 0;
    /*
    If we reduce this a lot and hold da key, `-1` shows all the time.
    When we hold a key, it it refreshed at a given low frequency it seems?
    */
    sleep_cycle.tv_nsec = 500000000L;
	initscr();
    for (;;) {
        clear();
        key = getkey();
        printw("%d\n", key);
        refresh();
        nanosleep(&sleep_cycle, NULL);
    }
	endwin();
    return 0;
}
