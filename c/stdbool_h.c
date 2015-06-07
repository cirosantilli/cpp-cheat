/*
# stdbool.h

    # bool

        Macro to `_Bool`.

        Same rationale as `_Complex` vs `complex`.

    # true

        Macro to `1`.

    # false

        Macro to `0`.
*/

#include "common.h"

int main() {
#if __STDC_VERSION__ >= 199901L
    bool b = true;
    bool b2 = false;
    assert(false == 0);
    assert(true  == 1);
#endif
    return EXIT_SUCCESS;
}
