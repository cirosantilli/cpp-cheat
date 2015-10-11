/*
# limits.h

    Gives the maximum and minimum values that fit into base integer types
    in the current architecture.
*/

#include "common.h"

int main() {
    {
        /*
        # CHAR_BIT

            Numbers of bits in a char == number of bits in a C byte (not necessarily 8!)

            POSIX fixes it to 8 TODO reference.

            `sizeof` returns results in multiples of it.
        */
        printf("CHAR_BIT = %d\n", CHAR_BIT);
        /* Guaranteed. */
        assert(CHAR_BIT >= 8);

        /*
        # CHAR_MAX

            Remember that signed char is different from char:
            it can be either signed or unsigned.
        */
        printf("CHAR_MAX = %d\n", CHAR_MAX);

        /*
        # SCHAR_MAX

            TODO Not redundant with by CHAR_BIT? Maybe not: CHAR_BIT is about memory size,
            but it could have some dead bits around for some reason, ans CHAR_MAX could be smaller.
        */
        printf("SCHAR_MIN = %d\n", SCHAR_MIN);
        printf("SCHAR_MAX = %d\n", SCHAR_MAX);
    }

    /* # INT_MAX */
    printf("INT_MAX = %d\n", INT_MAX);
    printf("INT_MIN = %d\n", INT_MIN);

    printf("LONG_MAX = %ld\n", LONG_MAX);
    printf("LLONG_MIN = %lld\n", LLONG_MIN);

    /*
    Unsigned versions are prefixed by `U`.

    There is no MIN macro for unsigned versions since it is necessarily `0`.
    */
    printf("UINT_MAX = %u\n", UINT_MAX);

    return EXIT_SUCCESS;
}
