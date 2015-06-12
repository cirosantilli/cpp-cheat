/*
# Static_assert

# _Static_assert

    Makes compile time assertions.

    Can only take constant expressions (C99 6.6).

    Issues warnings or prevents compilation if failed.

    C++ has the analogous `static_assert`.
*/

#include "common.h"

int main() {
#if __STDC_VERSION__ >= 201112L
    /* ERROR: static assertion failed: "Error message". */
    /*_Static_assert(0, "Error message.");*/

    _Static_assert(1, "e");
    _Static_assert(1 + 1, "e");

    const int i = 1;
    /* ERROR: expression in static assertion is not constant. */
    /*_Static_assert(i, "e");*/
#endif

    return EXIT_SUCCESS;
}
