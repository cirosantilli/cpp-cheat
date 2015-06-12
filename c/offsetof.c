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
    struct foo {
        char a;
        char b[2];
        int c;
        char d;
    };

    printf("offsetof(struct foo, a) = %zu\n", offsetof(struct foo, a));
    printf("offsetof(struct foo, b) = %zu\n", offsetof(struct foo, b));
    printf("offsetof(struct foo, c) = %zu\n", offsetof(struct foo, c));
    printf("offsetof(struct foo, d) = %zu\n", offsetof(struct foo, d));

    return EXIT_SUCCESS;
}
