/*
# atomic

    More restricted than mutex as it can only protect a few operations on integers.

    But if that is the use case, may be more efficient.

    On GCC 4.8 x86-64, using atomic is a huge peformance improvement
    over the same program with mutexes (5x).
*/

#include "common.hpp"

#if __cplusplus >= 201103L

std::atomic_long global(0);

void threadMain() {
    for (int i = 0; i < NUM_ITERS; ++i) {
        global++;
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
    assert(global.load() == NUM_THREADS * NUM_ITERS);
    // Same as above through `operator T`.
    assert(global == NUM_THREADS * NUM_ITERS);
#endif
}
