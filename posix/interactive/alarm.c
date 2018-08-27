/* #alarm
 *
 * Sends a SIGALRM to ourselves in n seconds
 *
 * Outcome:
 *
 *     0
 *     1
 *     signal_handler
 *     2
 *     3
 */

#include "common.h"

void signal_handler(int sig) {
    char s[] = "signal_handler\n";
    write(STDOUT_FILENO, s, sizeof(s));
    signal(sig, signal_handler);
}

int main(void) {
    int i;

    signal(SIGALRM, signal_handler);
    i = 0;
    assert(alarm(2) == 0);
    while (i < 4) {
        printf("%d\n", i);
        i++;
        sleep(1);
    }
    return EXIT_SUCCESS;
}
