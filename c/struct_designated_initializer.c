/*
# struct designated initializer

    Allows to struc values by their name instead of order.
*/

#include "common.h"

int main() {
#if __STDC_VERSION__ >= 199901L
    /* Basic example. */
    {
        struct S {
            int i;
            float f;
        };
        struct S s = {
            .f = 1.5,
            .i = 1
        };
        assert(s.i == 1);
        assert(s.f == 1.5);
    }

    /* Can be mixed with array designated initializers. */
    {
        struct S { int a[2]; int i; };

        /* TODO GCC 4.8 warns missing i for [0]. Bug? */
        struct S ss[] = {
            [0].a = {0, 1},
            [0].i = 2,
            [1].a[0] = 3,
            [1].a[1] = 4,
            [1].i = 5
        };

        assert(ss[0].a[0] == 0);
        assert(ss[0].a[1] == 1);
        assert(ss[0].i == 2);

        assert(ss[1].a[0] == 3);
        assert(ss[1].a[1] == 4);
        assert(ss[1].i == 5);
    }
#endif
    return EXIT_SUCCESS;
}
