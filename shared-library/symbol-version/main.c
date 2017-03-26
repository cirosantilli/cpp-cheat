#include <stdio.h>
#include <stdlib.h>

#include "a.h"

/* TODO: any clearer way of doing this maybe
 * with some compilation option only? */
#if defined(V1)
__asm__(".symver a,a@LIBA_1");
#elif defined(V2)
__asm__(".symver a,a@LIBA_2");
#endif

int main(void) {
    a();
    return EXIT_SUCCESS;
}
