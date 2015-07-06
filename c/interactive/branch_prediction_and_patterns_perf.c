/*
Measure the performance of each call with: TODO

http://igoro.com/archive/fast-and-slow-if-statements-branch-prediction-in-modern-processors/
*/

#include "common.h"

const long N = 1000000000;

void f(long p) {
    long sum = 0;
    for (long i = 0; i < N; i++)
        if (!(i & p))
            sum++;
}

int main() {
    f(INT_MIN);
    f(-1);
    f(1);
    f(2);
    f(3);
    f(4);
    f(8);
    f(16);
    return EXIT_SUCCESS;
}
