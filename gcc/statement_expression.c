/*
## Statement expression

    https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html

    Only the last expression is returned.
*/

#include "common.h"

int main() {
    assert(({int i = 0; int j = i; i++; j = i; j;}));
    return EXIT_SUCCESS;
}
