/*
# builtin_constant_p()

    Returns true iff GCC could determine that the given expression is constant,
    to decide if compile time optimizations may be done or not.

    GCC is not smart enough to decide all cases correctly.

    TODO what is a compile time constant? How to use this?
*/

#include "common.h"

int main() {
    assert(__builtin_constant_p(1));
    assert(__builtin_constant_p(1 + 1));
    const int i = 0;
    assert(!__builtin_constant_p(i));
    return EXIT_SUCCESS;
}
