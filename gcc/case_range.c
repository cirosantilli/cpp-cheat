/*
# case range
*/

#include "common.h"

int main() {
    int i = 1;
    switch (i) {
        case 0 ... 2:
            assert(1);
        break;
        case 3 ... 5:
            assert(0);
        break;
        default:
            assert(0);
        break;
    }
    return EXIT_SUCCESS;
}
