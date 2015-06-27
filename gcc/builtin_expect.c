/*
# builtin_expect

    Basis for the `likely` and `unlikely` macros used extensively on the Linux kernel to help with branch prediction:

        #define likely(x)	__builtin_expect(!!(x), 1)
        #define unlikely(x)	__builtin_expect(!!(x), 0)

    Says that we expect the left side expression and the right side long value to be the same almost always.
*/

#include "common.h"

int main() {
    int x = 0;
    int y;
    if (__builtin_expect(x, 0))
        y = 1;
    if (x == 0)
        y = 1;
    assert(y == 1);
    return EXIT_SUCCESS;
}
