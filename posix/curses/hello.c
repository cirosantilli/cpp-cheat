#include <curses.h>

int main(void) {
    /* Startup. */
	initscr();
	printw("hello world. Press any key to quit.");
	refresh();
	/* Wait for use input. */
	getch();
	/* Teardown. */
	endwin();
	return 0;
}
