/* Newlines do move the cursor down and to the beginning of the next line. */

#include "common.h"

int main(void) {
	initscr();
	printw("a\nb\npress any key to quit");
	refresh();
	getch();
	endwin();
	return 0;
}
