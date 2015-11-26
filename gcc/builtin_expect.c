/*
# builtin_expect


    - http://stackoverflow.com/questions/109710/likely-unlikely-macros-in-the-linux-kernel-how-do-they-work-whats-their
    - http://stackoverflow.com/questions/7346929/why-do-we-use-builtin-expect-when-a-straightforward-way-is-to-use-if-else
    - http://unix.stackexchange.com/questions/11597/what-is-the-difference-between-likely-and-unlikely-calls-in-kernel
*/

#include "common.h"

int main() {
    /*
    `(x, y)` *always* returns `x`.

    The second argument says that we expect:

        x == y

    to happen much more often.

    It does *not* return `x == y`.
    */
    {
        if (__builtin_expect(0, 0))
            assert(0);

        if (__builtin_expect(1, 0)) {
        } else {
            assert(0);
        }
    }

    /* Usage example */
    {
        int i;
        if ((time(NULL) % 2)) {
        /*if (__builtin_expect(time(NULL) % 2, 0)) {*/
            i = 0;
        } else {
            i = 1;
        }
        printf("%d\n", i);
    }

    return EXIT_SUCCESS;
}
