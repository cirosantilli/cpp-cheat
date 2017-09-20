/*
#alarm

	sends a SIGALRM to ourselves in n seconds
*/

#include "common.h"

void signal_handler(int sig) {
	char s[] = "signal_handler\n";
	write(STDOUT_FILENO, s, sizeof(s));
	signal(sig, signal_handler);
}

int main(void) {
    signal(SIGALRM, signal_handler);

    int i = 0;
	assert(alarm(2) == 0);
    while (i < 4) {
        printf("%d\n", i);
        i++;
        sleep(1);
    }

    /*
    # pause

        Stop program until it receives a signal.

        TODO
    */

    return EXIT_SUCCESS;
}
