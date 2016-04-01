/*
# Identifier list function declarator

    Old style thing that should never be done today.
*/

#include "common.h"

/* TODO without definition. Should never be done. Conforming or not? */
/*int f(x, y);*/

int f(x, y)
    int x;
    int y;
{ return x + y; }

/* Also identifier list: it is the only optional one. */
void g() {}

/* Identifier type list. This one is not optional. */
void h(void) {}

int main() {
    assert(f(1, 2) == 3);
    return EXIT_SUCCESS;
}
