/*
# 128 bit int

# int128

# __int128

    https://gcc.gnu.org/onlinedocs/gcc-5.1.0/gcc/_005f_005fint128.html

    - http://stackoverflow.com/questions/3329541/does-gcc-support-128-bit-int-on-amd64
    - http://stackoverflow.com/questions/21886985/what-gcc-versions-support-the-int128-intrinsic-type

    No hardware support it seems.
*/

#include "common.h"

int main() {
    /* Basic example. */
    {
        unsigned __int128 i = (unsigned __int128)1 << 127;
        /* TODO: why does this fail? */
        /*assert(i + 1 == 0);*/
        printf("__int128 max + 1 = %ju\n", (uintmax_t)i + 1U);
        printf("sizeof(long long) = %zu\n", sizeof(long long));
        printf("sizeof(__int128) = %zu\n", sizeof(__int128));
    }

    /*
    # __int128_t

        TODO vs __int128?
    */
    {
        __int128_t i;
    }

    /*
    How to printf __int128:
    http://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc

    `%ju` not possible because `intmax_t` does not currently consider `__int128`:

    - http://stackoverflow.com/a/11658831/895245
    - http://stackoverflow.com/questions/21265462/why-in-g-stdintmax-t-is-not-a-int128-t

    Seems that the answer is that it is not well implemented
    enough to replace the standard's `intmax_t`.
    */
    {
        printf("sizeof(intmax_t) = %zu\n", sizeof(intmax_t));
    }

    return EXIT_SUCCESS;
}
