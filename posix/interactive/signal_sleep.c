/*
Shows clearly that program execution waits until signal handler is done.
*/

#include "common.h"

volatile sig_atomic_t i = 0;

void signal_handler(__attribute__((unused)) int sig) {
	char s[] = "signal_handler\n";
	write(STDOUT_FILENO, s, sizeof(s));
	i++;
	sleep(2);
	signal(sig, signal_handler);
}

int main(void) {
    signal(SIGALRM, signal_handler);
	puts("before");
    assert(i == 0);
    assert(kill(getpid(), SIGALRM) == 0);
    assert(i == 1);
	puts("after");
    assert(kill(getpid(), SIGALRM) == 0);
    assert(i == 2);
	puts("after2");
    return EXIT_SUCCESS;
}
