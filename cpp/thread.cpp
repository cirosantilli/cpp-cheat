/*
# thread

# Multithreading

# Parallel

# Concurrency

    Requires `-pthread` flag on g++ Linux.
*/

#include "common.hpp"

int main() {
    /* # get_id */
    {
        std::thread::id id = std::this_thread::get_id();
        std::cout << "get_id = " << id << std::endl;
    }

    /*
    # hardware_concurrency

        Get the number of threads.

        http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
    */
    {
        unsigned int n = std::thread::hardware_concurrency();
        std::cout << "hardware_concurrency = " << n << std::endl;
    }
}
