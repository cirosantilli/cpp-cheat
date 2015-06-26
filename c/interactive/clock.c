/*
# clock
*/

#include "common.h"

int main() {
    clock_t t;
    uintmax_t i, j;

    t = clock();
    /*
    Busy waiting.

    Do something whacky, and then a printf side-effect,
    so that GCC won't be able to optimize it away.
    */
    j = (uintmax_t)time(NULL);
    for (i = 0; i < (uintmax_t)(CLOCKS_PER_SEC * 1000); i++) {
        j += i*i*i - i-j + 1;
    }
    printf("side-effect: %ju\n", j);
    t = clock() - t;

    printf("t1 - t0 = %Lf\n", (long double)t);
    printf("(t1 - t0) / CLOCKS_PER_SEC = %Lf\n", (long double)(t / CLOCKS_PER_SEC));

    return EXIT_SUCCESS;
}
