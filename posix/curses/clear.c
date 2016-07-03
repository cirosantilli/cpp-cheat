/* Second times overwrites the first. */

#include "common.h"
#include "common_curses.h"

int main(void) {
    int c;
	initscr();
	printw("before clear\n");
	clear();
	printw("after clear\n");
	refresh();
	press_any_key_to_quit();
	endwin();
	return 0;
}
