/*
# Empty struct
*/

#include "common.h"

int main() {
    struct s {};
    struct s s0;
    assert(sizeof(s0) == 0);
    return EXIT_SUCCESS;
}
