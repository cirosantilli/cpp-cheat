/*
# Local label

# __label__

    https://gcc.gnu.org/onlinedocs/gcc/Local-Labels.html

    Labels have function scope and are not constrained by inner blocks.

    With `__label__` they are.
*/

#include "common.h"

int main() {
    /* Without. */
    goto label;
    {
        label:
        ;
    }

    /* With. */
    {
        /* Must be working, or else we'd have a conflict. */
        __label__ label;
        label:
        ;

        {
            __label__ label;
            label:
            ;
        }
    }

    return EXIT_SUCCESS;
}
