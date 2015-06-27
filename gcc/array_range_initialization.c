/*
# Array range initialization
*/

#include "common.h"

int main() {
    int is[] = {
        [0 ... 2] = 0,
        [3 ... 5 ] = 1
    };
    assert(memcmp(is,
                &(int[6]){ 0, 0, 0, 1, 1, 1 },
                sizeof(typeof(is))) == 0);
    return EXIT_SUCCESS;
}
