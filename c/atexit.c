/*
# atexit

    Function gets called when process ends via `exit` or a `return` on the `main` function.

    Does not get called on abnormal termination, e.g. from signals.
*/

#include "common.h"

void atexit_func() {
    printf("atexit\n");
}

int main() {
    atexit(atexit_func);
    return EXIT_SUCCESS;
}
