/*
# static array argument

    Specifies the minimum size of the array to be passed.

    Can be used by the compiler for optimization

    http://stackoverflow.com/questions/3693429/c-parameter-array-declarators

    Not enforced by the compiler and does not alter any behaviour
    except for the exact generated assembly code.

    If the contract is not followed by the programmer, undefined behaviour.
*/

#include "common.h"

#if __STDC_VERSION__ >= 199901L
    int static_array_argument(int is[static 3]) {
        return is[3];
    }
#endif

int main() {
#if __STDC_VERSION__ >= 199901L
    /* Undefined behaviour: */
    int is2[2];
    /*static_array_argument(is2);*/

    int is4[4];
    static_array_argument(is4);
#endif
    return EXIT_SUCCESS;
}
