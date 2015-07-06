/*
# ptrdiff_t
*/

#include "common.h"

int main() {
    /*
    Signed integer type.

    Can always represent the difference between two pointers (which is an integer).

    Remember: there is no sum of pointers, only difference.

    One is  only allowed to take the difference of two pointers in the same array. C99 6.5.5/9.

    > When two pointers are subtracted, both shall point to elements of the same array object,
    or one past the last element of the array object; the result is the difference of the
    subscripts of the two array elements. The size of the result is implementation-defined,
    and its type (a signed integer type) is ptrdiff_t defined in the <stddef.h> header.
    If the result is not representable in an object of that type, the behavior is undefined.

    An array can be so large that `ptrdiff_t` cannot represent the difference of two pointers in it.

    http://en.cppreference.com/w/c/types/ptrdiff_t
    */
    printf("sizeof(ptrdiff_t) = %zu", sizeof(ptrdiff_t));

    ptrdiff_t p;
    int is[16];
    p =  &is[15] - &is[0];
    assert(p == 15);

    assert(p < PTRDIFF_MAX);

    return EXIT_SUCCESS;
}
