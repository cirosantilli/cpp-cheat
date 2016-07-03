#define ANY_KEY_TO_QUIT_MSG "press any key to quit\n"

void press_any_key_to_quit() {
	printw(ANY_KEY_TO_QUIT_MSG);
	refresh();
	getch();
}
