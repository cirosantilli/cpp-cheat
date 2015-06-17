/*
# mutex

    Only allows one thread to enter the critical zone.

    This is an artificial example: the more restricted and efficient atomic would be a better fit.

    http://stackoverflow.com/questions/6837699/are-mutex-lock-functions-sufficient-without-volatile
*/

#include "common.hpp"

#if __cplusplus >= 201103L

long int global = 0;
std::mutex mutex;

void threadMain() {
    for (int i = 0; i < NUM_ITERS; ++i) {
#ifndef FAIL
        mutex.lock();
#endif
        global++;
#ifndef FAIL
        mutex.unlock();
#endif
    }
}
#endif

int main() {
#if __cplusplus >= 201103L
    std::thread threads[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; ++i)
        threads[i] = std::thread(threadMain);
    for (i = 0; i < NUM_THREADS; ++i)
        threads[i].join();
    if (global != NUM_OPS) {
        printf("fraction of errors = %f\n", (1.0 - (double)global/NUM_OPS));
        assert(false);
    }
#endif
}
