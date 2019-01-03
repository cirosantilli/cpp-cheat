/* See: setpgid.md */

#define _XOPEN_SOURCE 700
#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t is_child = 0;

void signal_handler(int sig) {
    char parent_str[] = "sigint parent\n";
    char child_str[] = "sigint child\n";
    signal(sig, signal_handler);
    if (sig == SIGINT) {
        if (is_child) {
            write(STDOUT_FILENO, child_str, sizeof(child_str) - 1);
        } else {
            write(STDOUT_FILENO, parent_str, sizeof(parent_str) - 1);
        }
    }
}

int main(int argc, char **argv) {
    pid_t pid, pgid;

    (void)argv;
    signal(SIGINT, signal_handler);
    signal(SIGUSR1, signal_handler);
    pid = fork();
    assert(pid != -1);
    if (pid == 0) {
        is_child = 1;
        if (argc > 1) {
            /* Change the pgid.
             * The new one is guaranteed to be different than the previous, which was equal to the parent's,
             * because `man setpgid` says:
             * > the child has its own unique process ID, and this PID does not match
             * > the ID of any existing process group (setpgid(2)) or session.
             */
            setpgid(0, 0);
        }
        printf("child pid, pgid = %ju, %ju\n", (uintmax_t)getpid(), (uintmax_t)getpgid(0));
        assert(kill(getppid(), SIGUSR1) == 0);
        while (1);
        exit(EXIT_SUCCESS);
    }
    /* Wait until the child sends a SIGUSR1. */
    pause();
    pgid = getpgid(0);
    printf("parent pid, pgid = %ju, %ju\n", (uintmax_t)getpid(), (uintmax_t)pgid);
    /* man kill explains that negative first argument means to send a signal to a process group. */
    kill(-pgid, SIGINT);
    while (1);
}
