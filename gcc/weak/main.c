#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int my_weak_var __attribute__((weak)) = 1;

int main(void) {
    printf("%d\n", my_weak_var);
    assert(my_weak_var == 2);
    return EXIT_SUCCESS;
}
