/*
# Zero length arrays

http://stackoverflow.com/questions/9722632/what-happens-if-i-define-a-0-size-array-in-c-c

Major application looks like pre-99 flexible array member:

    struct S {
        int is[0];
    };

to save a byte compared to:

    struct S {
        int is[1];
    };
*/

#include "common.h"

int main(void) {
    int is[0];
    int i;
    printf("&is[0] = %p\n", &is[0]);
    printf("&i     = %p\n", &i);
    return EXIT_SUCCESS;
}
