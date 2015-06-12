/*
# Type qualifier

    Can be added to types to modify their semantics.
*/

#include "common.h"

int main() {
    /* Repeating qualifiers is OK and has no effect. C99 9.7.3.4 */
    {
        const const const const int i = 0;

        /* In practice, this is more likely to happen when the qualifier is hidden on a typedef. */
        {
            typedef const int ci;
            const ci i;
        }
    }

    return EXIT_SUCCESS;
}
