/* # if */

#include "common.h"

int main() {
    /* Only 0 counts as false. */
    if (0) {
        assert(0);
    }

    if (1){
        assert(1);
    }

    if (-1) {
    } else {
        assert(0);
    }

    if (-1) {
    } else if (0) {
        assert(0);
    } else {
        assert(0);
    }

    if (1.1) {
    }

    /* Can ommit braces for single statements. */
    {
        {
            if (0) assert(0);
            if (0)
                assert(0);
            if (0) { assert(0); }
        }

        {
            if (0)
                assert(0);
            else
                assert(1);
        }

        /* Possible but very ugly to use only one pair of braces. */
        {
            if (0) {
                assert(0);
            } else
                assert(1);

            if (0)
                assert(0);
            else {
                assert(1);
            }
        }
    }

    /* Scope */
    {
        int i = 0;
        if (1) {
            int i = 1;
            assert(i == 1);
        }
    }

    return EXIT_SUCCESS;
}
