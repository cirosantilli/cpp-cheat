/*
# Complex integer.

    C99 has floating point complex numbers, but no integer complex numbers.
*/

#include "common.h"

int main() {
    int complex z = 1 + 1*I;
    int complex z2 = 1 - 1*I;
    assert(z + z2 == 2  );
    return EXIT_SUCCESS;
}
