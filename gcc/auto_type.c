/*
## __auto_type

    Like C++11 `auto`.
*/

#include "common.h"

int main() {
#if defined(__GNUC__) && (__GNUC__ >= 5 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
    __auto_type i = 1;
    assert(_Generic((i), int: 1, default: 0));
#endif
    return EXIT_SUCCESS;
}
