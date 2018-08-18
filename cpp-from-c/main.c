#include <assert.h>

#include "cpp.h"

int main(void) {
    assert(f_int(1) == 2);
    assert(f_float(1.0) == 3);
    return 0;
}
