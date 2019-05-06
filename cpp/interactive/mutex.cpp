// Only allows one thread to enter the critical zone.
//
// Usage:
//
//     ./mutex.out [num_iters [num_threads [use_mutex=0|1]]
//
// Should work because uses mutex:
//
//     ./mutex.out 1000 10 1
//
// Fails for large num_iters large enough with more than one thread
// due to synchroniation problems:
//
//     ./mutex.out 1000 10 0
//
// This is an artificial example: the more restricted and efficient atomic would be a better fit.
//
// http://stackoverflow.com/questions/6837699/are-mutex-lock-functions-sufficient-without-volatile

#if __cplusplus >= 201103L
#include <cassert>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mutex;
unsigned int num_threads;
unsigned int use_mutex = 1;
unsigned long global = 0;
unsigned long long num_iters = 0;

void thread_main() {
    for (decltype(num_iters) i = 0; i < num_iters; ++i) {
        if (use_mutex)
            mutex.lock();
        global++;
        if (use_mutex)
            mutex.unlock();
    }
}
#endif

int main(int argc, char **argv) {
#if __cplusplus >= 201103L
    if (argc > 1) {
        num_iters = std::strtoull(argv[1], NULL, 10);
    } else {
        num_iters = 10;
    }
    if (argc > 2) {
        num_threads = std::strtoull(argv[2], NULL, 10);
    } else {
        num_threads = std::thread::hardware_concurrency();
    }
    if (argc > 3) {
        use_mutex = (argv[3][0] == '1');
    } else {
        use_mutex = 1;
    }

    std::vector<std::thread> threads(num_threads);
    for (auto& thread : threads)
        thread = std::thread(thread_main);
    for (auto& thread : threads)
        thread.join();
    auto num_ops = num_threads * num_iters;
    if (global != num_ops) {
        std::cout << "fraction of errors " << ((double)global / num_ops) << std::endl;
        assert(false);
    }
#endif
}
