#include <assert.h>
#include <stdlib.h>

int weak __attribute__((weak)) = 1;

/* Link error: multiple definitions of strong. */
/*int strong = 1;*/

int main() {
    assert(weak == 2);
    return EXIT_SUCCESS;
}
