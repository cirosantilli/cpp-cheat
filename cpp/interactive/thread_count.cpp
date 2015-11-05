/*
Dummy operation that uses a lot of CPU, but very little memory.

Used as a control for the parallel version, which should me scalably faster.
*/

#include "common.hpp"

void sleeper() {
    std::this_thread::sleep_for(std::chrono::seconds(1000000));
}

int main() {
    unsigned int nThreads = std::thread::hardware_concurrency();
    std::thread *threads = new std::thread[nThreads];
    unsigned int i;
    for (i = 0; i < nThreads; ++i)
        threads[i] = std::thread(sleeper);
    for (i = 0; i < nThreads; ++i)
        threads[i].join();
}
