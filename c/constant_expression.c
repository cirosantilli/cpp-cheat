/*
# Constant expressions

    C99 6.6.

    The fact that an expression is a compile time constant
    or not has effects such as:

    -   when declaring an array, if the size is a constant expression
        then the array is a regular aray, if not it is a VLA statring on C99,
        or a compilation error before. TODO this cannot be observed?

    -   only constant expressions can be used to initialize enum members

    -   only constant expressions can be used in `_Static_assert`

    -   only constant expressions can be used in `case` expressions

    C++ does not allow const pointer typecasts, so `const` variables generate constant expressions.
    There is an even more explicit language feature in C++11 via the `constexpr` keyword.

    GCC has `__builtin_constant_p` to explicitly check if a variable is a compile time constant or not.
*/
#include "common.h"

int main() {
    const int i = 0;

    /* ERROR: not a constant expression. */
    /*enum E { E0 = i };*/

#if __STDC_VERSION__ >= 201112L
    /* ERROR: not a constant expression. */
    /*_Static_assert(i, "e");*/
#endif

    return EXIT_SUCCESS;
}
