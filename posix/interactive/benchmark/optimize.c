/*
On a separate file to allow compiling the main test suite with -O0 and
ensure that optimizations won't optimize function calls away.
*/

#include <inttypes.h>
#include <stdlib.h>

/* http://stackoverflow.com/questions/1965487/does-the-restrict-keyword-provide-significant-benefits-in-gcc-g */

void f1(uint8_t *p1, uint8_t *p2, size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        p1[i] = 4;
        p2[i] = 9;
    }
}

void f2(uint8_t *restrict p1, uint8_t *restrict p2, size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        p1[i] = 4;
        p2[i] = 9;
    }
}
