/*
# No return non void

    In C99, a non-void return function can have no return.

    This is because it is hard to check if all code paths have a return.

    Gives undefined behaviour.
*/

#include "common.h"

#if __STDC_VERSION__ >= 199901L
#ifdef UNDEFINED_BEHAVIOUR
int f() {}
#endif
#endif

int main() {
#if __STDC_VERSION__ >= 199901L
#ifdef UNDEFINED_BEHAVIOUR
    f();
#endif
#endif
    return EXIT_SUCCESS;
}
