/*
# typeof

    Like C++11 decltype.

    Partially reproductible with C11 `_Generic`.
*/

#include "common.h"

int main() {
    /* Same as: double j = 0.5; */
    typeof(1 + 0.5) j = 0.5;
    assert(j == 0.5);
    return EXIT_SUCCESS;
}
