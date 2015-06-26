/*
# abs

    Absolute values, integer version.

    For floating point values, use `fabs` in `math.h`.
*/

#include "common.h"

int main() {
    assert(abs(-1) == 1);

    /*
    There is one UB case in 2's complement: INT_MIN

    TODO can there be more or less UB cases?
    */
    {
#ifdef UNDEFINED_BEHAVIOUR
        printf("abs(INT_MIN) = 0x%x\n", abs(INT_MIN));
        /* For comparison only. */
        printf("INT_MIN      = 0x%x\n", INT_MIN);
#endif
    }

    return EXIT_SUCCESS;
}
