/* # setpgid
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/setpgid.html
 *
 * Without argument, we change the process group of the child with setpgid:
 *
 *     ./setpgid.out
 *
 * and the program first outputs immediately:
 *
 *     child pid, pgid = 16396, 16396
 *     parent pid, pgid = 16395, 16395
 *     sigint
 *
 * and then whenever you hit Ctrl + C, it prints:
 *
 *     sigint
 *
 * once.
 *
 * With an argument:
 *
 *     ./setpgid.out 0
 *
 * The initial output shows that both child and parent have the same pgid as in:
 *
 *     child pid, pgid = 18747, 18746
 *     parent pid, pgid = 18746, 18746
 *
 * and then each Ctrl + C outputs sigint twice:
 *
 *     sigint
 *     sigint
 *
 * See also:
 *
 * - https://unix.stackexchange.com/questions/149741/why-is-sigint-not-propagated-to-child-process-when-sent-to-its-parent-process/465112#465112
 * - https://stackoverflow.com/questions/31907212/will-ctrlc-send-sigint-signals-to-both-parent-and-child-processes-in-linux/52042820#52042820
 * - https://stackoverflow.com/questions/6108953/how-does-ctrl-c-terminate-a-child-process/52042970#52042970
 *
 * # Process group
 *
 * http://en.wikipedia.org/wiki/Process_group
 *
 * # getpgrp
 *
 * Same at `getpgid(0)`.
 *
 * # setpgrp
 *
 * Same at `setpgid(0, 0)`, deprecated in POSIX 7.
 */

#include "common.h"

void signal_handler(int sig) {
    char sigint_str[] = "sigint\n";
    signal(sig, signal_handler);
    if (sig == SIGINT) {
        write(STDOUT_FILENO, sigint_str, sizeof(sigint_str) - 1);
    }
}

int main(int argc, char **argv) {
    COMMON_UNUSED(argv);
    pid_t pid, pgid;

    signal(SIGINT, signal_handler);
    signal(SIGUSR1, signal_handler);
    pid = fork();
    assert(pid != -1);
    if (pid == 0) {
        /* Change the pgid.
         * The new one is guaranteed to be different than the previous, which was equal to the parent's,
         * because `man setpgid` says:
         * > the child has its own unique process ID, and this PID does not match
         * > the ID of any existing process group (setpgid(2)) or session.
         */
        if (argc == 1) {
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
