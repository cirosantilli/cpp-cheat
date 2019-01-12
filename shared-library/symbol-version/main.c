#include <assert.h>
#include <stdlib.h>

#include "a.h"

/* TODO: any clearer way of doing this maybe
 * with some compilation option only?
 */
#if defined(V1)
__asm__(".symver a,a@LIBA_1");
#elif defined(V2)
__asm__(".symver a,a@LIBA_2");
#endif

int main(void) {
#if defined(V1)
    assert(a() == 1);
#else
    assert(a() == 2);
#endif
    return EXIT_SUCCESS;
}
