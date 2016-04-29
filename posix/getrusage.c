/*
# getrusage

    `rusage` stands for Resource usage

    The kernel allows processes to use a certain ammount of ressources such as
    memory or processor time.

    Exceeding those Limits may lead the kernel to kill a processes

    Returns the total time usage of current process (non sleeping/waiting)

        int getrusage(int who, struct rusage *r_usage);

    -   `who`:

        -   `RUSAGE_SELF`: only get information about current process

        -   `RUSAGE_CHILDREN`: information includes both current process and chidren who are dead
            and are just waiting for the parent to call `wait()` on them.

            This makes sense here because the only thing that keeps their memory
            used up is the existance of the parent process.

    -   `r_usage`: is the main return valu, and is set to contain a struct:

            struct rusage {
                struct timeval ru_utime; // user time used
                struct timeval ru_stime; // system time used
            };

        and `timeval` is of type:

            struct timeval {
                time_t         tv_sec      Seconds.
                suseconds_t    tv_usec     Microseconds.
            };

        http://pubs.opengroup.org/onlinepubs/009604499/basedefs/sys/types.h.html says:
        The type `suseconds_t` shall be a signed integer type capable of storing values
        at least in the range [-1, 1000000].

    - return: 0 on success, -1 on error + errno set to exact error
*/

#include "common.h"

int main(void) {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == -1) {
        perror("getrusage failed");
        exit(EXIT_FAILURE);
    } else {
        printf(
            "user time      = %ju s %ju micro secs\n",
            (uintmax_t)usage.ru_utime.tv_sec,
            (uintmax_t)usage.ru_utime.tv_usec
        );
        printf(
            "system time    = %ju s %ju micro secs\n",
            (uintmax_t)usage.ru_stime.tv_sec,
            (uintmax_t)usage.ru_stime.tv_usec
        );
    }
    return EXIT_SUCCESS;
}
