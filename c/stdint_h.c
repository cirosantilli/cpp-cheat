/*
# stdint.h

    Contains several types of ints, including fixed size
    and optimal for speed types

    C99

    All macros with numbers are defined for N = 8, 16, 32, 64.
*/

#include "common.h"

int main() {
#if __STDC_VERSION__ >= 199901L
    /* Fixed size integers. */
    {
        /* Exactly 32 bits. */
        assert(sizeof(int32_t) == 4);

        /* All have unsigned versions prefixed by 'u'. */
        assert(sizeof(uint32_t) == 4);

        /* At least 32 bits. */
        assert(sizeof(int_least32_t) >= 4);

        /* Fastest operations with at least 32 bits. */
        assert(sizeof(int_least32_t) >= 4);

        /*
        # Fast types

        # int_fast32_t

            TODO What is the motivation for those types?
            Is there an architecture where this fits well?
            http://stackoverflow.com/questions/9239558/what-is-the-difference-between-intxx-t-and-int-fastxx-t
        */
        {
            int_fast32_t i = 0;
        }
    }

    /*
    # intmax_t

    # uintmax_t

        int with max possible width

        There is no floating point analogue:
        http://stackoverflow.com/questions/17189423/how-to-get-the-largest-precision-floating-point-data-type-of-implemenation-and-i

        This does not have to be `long long`, since the standard explicitly allows extended types:
        http://stackoverflow.com/a/30322474/895245

        GCC 4.8 has __int128, but it currently does not count:
        http://stackoverflow.com/questions/21265462/why-in-g-stdintmax-t-is-not-a-int128-t
    */
    {
        printf("sizeof(intmax_t) = %zu\n", sizeof(intmax_t));
        assert(sizeof(intmax_t) >= sizeof(long long));
        assert(sizeof(uintmax_t) >= sizeof(unsigned long long));
    }

    /*
    # intptr_t

        An integer type large enough to hold a pointer.

        Could be larger than the minimum however.

    # uintptr_t

        Unsigned version.

    TODO example of real life application?
    */
    {
        assert(sizeof(void*) == sizeof(intptr_t));
        assert(sizeof(void*) == sizeof(uintptr_t));
    }

    /*
    # Bound for types

    # INT32_MAX

    # INT32_MIN

        Bounds for the fixed size integers.
    */
    {
        {
            int32_t i;
            assert(INT32_MIN <= i);
            assert(INT32_MAX >= i);
            assert(INT32_MIN == 0x80000000);
            assert(INT32_MAX == 0x7FFFFFFF);
        }

        /*
        # fast types

            TODO
        */
        {
            int_fast32_t i;
            assert(INT_FAST32_MIN <= i);
            assert(INT_FAST32_MAX >= i);
        }
    }
#endif
    return EXIT_SUCCESS;
}
