#include <stdio.h>
#include <stdlib.h>

#include "a.h"

__asm__(".symver a1,a@LIBA_1");

int main(void) {
    a();
    return EXIT_SUCCESS;
}
