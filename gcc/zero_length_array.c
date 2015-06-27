/*
# Zero length arrays

    TODO application?
*/

#include "common.h"

int main() {
    int is[0];
    int i;
    printf("&is[0] = %p\n", &is[0]);
    printf("&i     = %p\n", &i);
    return EXIT_SUCCESS;
}
