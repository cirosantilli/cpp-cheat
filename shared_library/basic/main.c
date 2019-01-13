#include <assert.h>
#include <stdlib.h>

#include "a.h"
#include "b.h"

int main(void) {
    assert(a() == 1);
    assert(b() == 2);
    return EXIT_SUCCESS;
}
