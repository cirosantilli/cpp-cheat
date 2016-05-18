/*
# Flexible array member

Allows to embed a dynamically allocated array contiguously inside a dynamically allocated struct:

- http://stackoverflow.com/questions/2060974/dynamic-array-in-struct-c
- http://stackoverflow.com/questions/246977/flexible-array-members-in-c-bad
- https://en.wikipedia.org/wiki/Flexible_array_member

# Struct hack

Before C99, people would use either: http://stackoverflow.com/questions/6390331/why-use-array-size-1-instead-of-pointer

    struct S {
        int is[1];
    }

or possibly a the GCC `is[0]` extension to save a byte: http://stackoverflow.com/questions/14643406/whats-the-need-of-array-with-zero-elements

    struct S {
        int is[0];
    }
*/

#include "common.h"

int main(void) {
#if __STDC_VERSION__ >= 199901L
    typedef struct {
        int i;
        int is[];
    } S;
    S *s = malloc(sizeof(S) + 2 * sizeof(int));
    s->i = 0;
    s->is[0] = 1;
    s->is[1] = 2;
#endif
    return EXIT_SUCCESS;
}
