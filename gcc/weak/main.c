#include <assert.h>
#include <stdlib.h>

int weak __attribute__((weak)) = 1;

/* Link error: multiple definitions of strong. */
#if 0
int strong = 1;
#endif

int main(void) {
    assert(weak == 2);
    return EXIT_SUCCESS;
}
