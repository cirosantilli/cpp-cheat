/*
# Array designated initializer

# Designated initializer for arrays

    Allows to initialize array elements in any order.

    Called like that because you explicitly *designate*
    which field you are initializing by its position.

    There is also a struct version.
*/

#include "common.h"

int main() {
#if __STDC_VERSION__ >= 199901L
    {
        int is[] = {
            [1] = 1,
            [0] = 0,
        };
        assert(is[0] == 0);
        assert(is[1] == 1);
    }

    /* Missing elements are zeroed. */
    {
        int is[2] = {
            [1] = 1,
        };
        assert(is[0] == 0);
        assert(is[1] == 1);
    }

    /*
    Multiple assignments for a single int.

    Only last takes effect.

    WARN -Woverride-init
    */
    {
        int is[1] = {
            [0] = 0,
            [0] = 1,
        };
        assert(is[0] == 1);
    }

    /* arrays of structs can refer multiple times to the same struct */
    {
        struct S { int i; int j; };

        struct S ss[] = {
            [0].i = 0,
            [0].j = 1,
            [1].i = 2,
            [1].j = 3,
        };

        assert(ss[0].i == 0);
        assert(ss[0].j == 1);
        assert(ss[1].i == 2);
        assert(ss[1].j == 3);
    }

    /*
    Mix designated and non designated initialization.

    Non designated pick off where the last designated left.

    Non specified ones are zero.
    */
    {
        {
            int is[4] = {
                -1,             /* [0] */
                                /* [1] was not specified, so it is 0. */
                [2] = 1,
                2,              /* [3], because it comes after [2] */
            };
            assert(is[0] == -1);
            assert(is[1] == 0);
            assert(is[2] == 1);
            assert(is[3] == 2);
        }

        /* possible to overwrite values */
        {
            int is[2] = {
                0,          /* [0] first assign */
                1,          /* [1] first assign */
                [0] = 2,    /* [0] second assign, overwrites first */
                3,          /* [1] because comes after [0], second assign, overwrites first */
            };
            assert(is[0] == 2);
            assert(is[1] == 3);
        }
    }
#endif
    return EXIT_SUCCESS;
}
