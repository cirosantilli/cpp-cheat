#include "a.h"

__asm__(".symver a1,a@LIBA_1");
int a1(void) {
    return 1;
}

/* @@ means "default version". */
__asm__(".symver a2,a@@LIBA_2");
int a2(void) {
    return 2;
}
