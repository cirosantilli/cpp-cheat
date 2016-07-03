/* The current cursor position is unchanged. */

#include "common.h"
#include "common_curses.h"

int main(void) {
	initscr();
	printw("first\n");
	printw("second\n");
	printw(ANY_KEY_TO_QUIT_MSG);
	refresh();
	getch();
	endwin();
	return 0;
}
