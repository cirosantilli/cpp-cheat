/*
TODO this example is too complex, split it up into smaller examples.

# Thread

# Multithreading

# Parallel

# Concurrency

    Requires `-pthread` flag on g++ Linux.
*/

#include "common.hpp"

int nNsecs = 10;
int threadGlobal = 0;
int threadGlobalMutexed = 0;
std::mutex threadGlobalMutex;
std::thread::id lastThreadId;
std::set<std::thread::id> threadIds;

int threadGlobalEq0 = 0;
int threadGlobalMutexedEq0 = 0;
int threadChange = 0;

void threadMain(int threadCountToSqrt) {
    std::thread::id id = std::this_thread::get_id();
    for (int i = 0; i < threadCountToSqrt; i++) {
        for (int j = 0; j<threadCountToSqrt; j++) {
            if (lastThreadId != id) {
                ++threadChange;
                //threadIds.insert(id);
                lastThreadId = id;
            }

            // cout is not thread safe order gets mixed up.
            //std::cout << id << " " << i << endl;

            // If happens.

            threadGlobal = 1;
            if (threadGlobal == 0)
                ++threadGlobalEq0;
            threadGlobal = 0;

            // If never happens!

            threadGlobalMutex.lock();
            // if not available, wait
            //threadGlobalMutex.try_lock();
            // If not available, return!
            threadGlobalMutexed = 1;
            if (threadGlobalMutexed == 0)
                ++threadGlobalMutexedEq0;
            threadGlobalMutexed = 0;
            threadGlobalMutex.unlock();

        }
    }
    std::this_thread::sleep_for (std::chrono::nanoseconds(nNsecs));
    // Done, pass to another thread.
    std::this_thread::yield();
}


int main() {
    // Start threads.
    std::thread t1(threadMain, 1000);
    std::thread t2(threadMain, 1000);

    // Ensure that both threads ended.
    t1.join();
    t2.join();

    assert(threadChange > 0);
    //assert(threadIds.size() == 2);
    //assert(threadGlobalEq0 > 0);
    assert(threadGlobalMutexedEq0 == 0);

    std::thread::id mainId = std::this_thread::get_id();
    std::this_thread::sleep_for(std::chrono::nanoseconds(nNsecs));
    std::this_thread::yield();
}
