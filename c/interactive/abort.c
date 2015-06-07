/*
# abort

    Raise a SIGABRT, an ANSI C signal which by default kills the program.

        man abort

    Sources:

    - http://stackoverflow.com/questions/397075/what-is-the-difference-between-exit-and-abort
    - http://stackoverflow.com/questions/3676221/when-abort-is-preferred-over-exit

    Differences from exit: does not run regular program teardown:

    - does not call `atexit` function.
    - does not call C++ destructors
*/

#include "common.h"

void atexit_func() {
    printf("atexit\n");
}

int main() {
    /* Will not get called. */
    atexit(atexit_func);
    abort();
    return EXIT_SUCCESS;
}
