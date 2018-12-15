/* # setpgid
 *
 * - https://unix.stackexchange.com/questions/149741/why-is-sigint-not-propagated-to-child-process-when-sent-to-its-parent-process/465112#465112
 * - https://stackoverflow.com/questions/31907212/will-ctrlc-send-sigint-signals-to-both-parent-and-child-processes-in-linux/52042820#52042820
 * - https://stackoverflow.com/questions/1046933/posix-process-groups/53759402#53759402
 * - https://stackoverflow.com/questions/6108953/how-does-ctrl-c-terminate-a-child-process/52042970#52042970
 *
 * **Run without `setpgid`**
 *
 * Without any CLI arguments, `setpgid` is not done:
 *
 *     ./setpgid
 *
 * Possible outcome:
 *
 *     child pid, pgid = 28250, 28249
 *     parent pid, pgid = 28249, 28249
 *     sigint parent
 *     sigint child
 *
 * and the program hangs.
 *
 * As we can see, the pgid of both processes is the same, as it gets inherited across `fork`.
 *
 * Then whenever you hit:
 *
 *     Ctrl + C
 *
 * It outputs again:
 *
 *     sigint parent
 *     sigint child
 *
 * This shows how:
 *
 * - to send a signal to an entire process group with `kill(-pgid, SIGINT)`
 * - Ctrl + C on the terminal sends a kill to the entire process group by default
 *
 * Quit the program by sending a different signal to both processes, e.g. SIGQUIT with `Ctrl + \`.
 *
 * **Run with `setpgid`**
 *
 * If you run with an argument, e.g.:
 *
 *     ./setpgid 1
 *
 * then the child changes its pgid, and now only a single sigint gets printed every time from the parent only:
 *
 *     child pid, pgid = 16470, 16470
 *     parent pid, pgid = 16469, 16469
 *     sigint parent
 *
 * You can still kill the parent as before with a SIGQUIT:
 *
 *     Ctrl + \
 *
 * however the child now has a different PGID, and does not receive that signal! This can seen from:
 *
 *     ps aux | grep setpgid
 *
 * You will have to kill it explicitly with:
 *
 *     kill -9 16470
 *
 * This makes it clear why signal groups exist: otherwise we would get a bunch of processes left over to be cleaned manually all the time.
 *
 * Tested on Ubuntu 18.04.
 */

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
        /* Change the pgid.
         * The new one is guaranteed to be different than the previous, which was equal to the parent's,
         * because `man setpgid` says:
         * > the child has its own unique process ID, and this PID does not match
         * > the ID of any existing process group (setpgid(2)) or session.
         */
        is_child = 1;
        if (argc > 1) {
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
