/*
# Statement expression

Only the last expression is "returned".

Especially useful for macros:
https://stackoverflow.com/questions/10393844/about-typecheck-in-linux-kernel
where it serves as a "return value"

https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html
*/

#define FACTORIAL(X) \
    ({ \
        unsigned int x = X; \
        unsigned int result = 1; \
        while (x > 1) { \
            result *= x; \
            x--; \
        } \
        result; \
    })

#include "common.h"

int main(void) {
    /* Minimal example */
    int x = ({int i = 0; i++; i + 1;});
    assert(x == 2);

    /* More meaningful macro example*/
    assert(FACTORIAL(5) == 120);

    return EXIT_SUCCESS;
}
