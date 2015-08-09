/*
# fork

    Makes a copy of this process.

    This includes open file descriptors.

    Global memory space (`.DATA` and `.BSD`) is copied to current value but separated
    (unlike threads, which share memory space).

    # fork and stream buffering

        http://stackoverflow.com/questions/3513242/working-of-fork-in-linux-gcc

        There are three buffering methods:

        - unbuffered
        - fully buffered
        - line buffered

        When you fork, the streams get forked too,
        with unflushed data still inside

        stdout and stderr flush at newlines

        If you don't put newlines, it does not flush,
        and fork copies the buffers, and prints things twice.

# vfork

    Fork but keep same address space. POSIX 7 discourages it's use,
    and says that it may be deprecated in the future

    Somewhat similar to threads.

# posix_spawn

    TODO

# wait

    Wait for any child to terminate and then wake up.

    Same as:

        waitpid(-1, &status, 0);

# waitpid

    Wait for child with given PID to terminate.

    # WIFEXITED

        True is the process exited normally.

        This is false in the following cases:

        - singals
        - ptrace

    # WEXITSTATUS

        `status` is not set to the exact exit status, but contains multiple fields.

        We need to use those macros to extract individual fields.

# Copy on write

# COW

    Often the fork is followed by an operation which does not use the old memory
    such as `exec`, making copying the data useless.

    Some operating systems may at first not copy memory from old process,
    but wait until memory is written to do that.

    This process normally has page granularity (~4k).
*/

#include "common.h"

int main() {
    int status;
    /* This variable will be duplicated on the parent and on the child. */
    int i;
    pid_t pid;
    /* Parent PID */
    pid_t ppid;

    i = 0;
    ppid = getpid();
    if (ppid == -1) {
        perror("getpid");
        exit(EXIT_FAILURE);
    }

    puts("parent only before child");

    /* Flush before fork so that existing output won't be duplicated. */
    fflush(stdout);
    fflush(stderr);

    /* In case of success, PID is set differently on parent and child */
    /* so you can distinguish between them. For the child, `pid = 0`. */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        assert(false);
    } else {
        puts("child and parent");

        /* Happens on child only. */
        if (pid == 0) {
            /*
            This puts is asynchronous with the process stdout.

            So it might not be in the line program order.

            But they both go to the same terminal.
            */
            puts("child only");

            /* Child has a different PID than its parent */
            pid = getpid();
            if (pid == -1) {
                perror("getpid");
                exit(EXIT_FAILURE);
            }
            assert(pid != ppid);
            printf("child PID getpid() = %jd\n", (intmax_t)pid);

            /* This only change the child's `i` because memory was cloned (unlike threads). */
            i++;

            /* The child exits here. */
            exit(EXIT_SUCCESS);
        }

        /*
        Only the parent reaches this point because of the exit call
        done on the child.
        */
        puts("parent only");

        /*
        fork returns the child pid to the parent.

        This could be asserted with the getpid in the child,
        but would require the child to communicate that back to the parent,
        which would need a `mmap` + `semaphore`,
        and we don't want to complicate the example too much.
        */
        printf("child PID fork() = %jd\n", (intmax_t)pid);

        wait(&status);
        if (WIFEXITED(status)) {
            assert(status == WEXITSTATUS(EXIT_SUCCESS));
        } else {
            perror("execl abnormal exit");
            assert(false);
        }

        puts("parent only after child");

        /* Memory was cloned, parent `i` was only modified in child memory. */
        assert(i == 0);
    }

    return EXIT_SUCCESS;
}
