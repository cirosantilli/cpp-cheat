/*
# offsetof

    Get distance of member variable from the start of the struct.

    Appliction: get the struct that corresponds to a given pointer to a field.
    this is used in the kernel via `container_of`, and can be used to implement
    linked lists in ANSI C:
    http://stackoverflow.com/questions/10269685/kernels-container-of-any-way-to-make-it-iso-conforming
*/

#include "common.h"

int main() {
    /* Basic example. */
    {
        struct S {
            char a;
            char b[2];
            int c;
            char d;
        };

        printf("a = %zu\n", offsetof(struct S, a));
        printf("b = %zu\n", offsetof(struct S, b));
        printf("c = %zu\n", offsetof(struct S, c));
        printf("d = %zu\n", offsetof(struct S, d));
    }

    /* Does not work with bitfields. */
    {
        struct S {
            int a:1;
        };

        /* ERROR: attempt to take the address of a bitfield struct member. */
        /*printf("a = %zu\n", offsetof(struct S, a));*/
    }

    return EXIT_SUCCESS;
}
