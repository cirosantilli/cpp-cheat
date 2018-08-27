/* https://stackoverflow.com/questions/7696925/how-to-send-a-signal-to-a-process-in-c/50075790#50075790
 *
 * Some fun with signal sending.
 *
 * Fork a process, then a signal to it every second.
 *
 * The fork prints a message to stdtout when the signal is received:
 *
 * SIGUSR1
 * SIGUSR2
 * SIGUSR1
 * SIGUSR2
 * ...
 */

#include "common.h"

void signal_handler(int sig) {
    char s1[] = "SIGUSR1\n";
    char s2[] = "SIGUSR2\n";
    if (sig == SIGUSR1) {
        write(STDOUT_FILENO, s1, sizeof(s1));
    } else if (sig == SIGUSR2) {
        write(STDOUT_FILENO, s2, sizeof(s2));
    }
    signal(sig, signal_handler);
}

int main(void) {
    pid_t pid;

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    pid = fork();
    if (pid == -1) {
        perror("fork");
        assert(false);
    }
    if (pid == 0) {
        while (1);
        exit(EXIT_SUCCESS);
    }
    while (1) {
        kill(pid, SIGUSR1);
        sleep(1);
        kill(pid, SIGUSR2);
        sleep(1);
    }
    return EXIT_SUCCESS;
}
