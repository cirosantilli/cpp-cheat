/*
Bad things happen: at the bottom of the screen,
the cursor is imply not lowered anymore.
*/

#include "common.h"
#include "common_curses.h"

int main(void) {
    int i;
	initscr();
	for (i = 0; i < 1000; ++i) {
        printw("%d\n", i);
    }
	press_any_key_to_quit();
	endwin();
	return 0;
}
