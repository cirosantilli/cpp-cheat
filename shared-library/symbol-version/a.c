#include <stdio.h>

#include "a.h"

__asm__(".symver a1,a@LIBA_1");
void a1(void) {
    puts("a1");
}

/* @@ means "default version". */
__asm__(".symver a2,a@@LIBA_2");
void a2(void) {
    puts("a2");
}
