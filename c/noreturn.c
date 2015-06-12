/*
# _Noreturn

# noreturn

    Vs: same rationale as `_Complex` vs `complex`.

    Indicates that a function never returns.

    E.g.: a function that always runs:

    - `exit()`
    - `longjmp`

    Main application: avoid compiler warnings.
*/

#include "common.h"

#if __STDC_VERSION__ >= 201112L
_Noreturn
#endif
void f() { exit(0); }

#if __STDC_VERSION__ >= 201112L
noreturn
#endif
void g() { exit(0); }

int main() {
#if __STDC_VERSION__ >= 201112L
    f();
    g();
#endif
    return EXIT_SUCCESS;
}
