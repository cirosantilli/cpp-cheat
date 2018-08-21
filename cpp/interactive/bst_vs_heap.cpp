#include "common.hpp"

int main(int argc, char **argv) {
    typedef uint64_t I;
    I *randoms;
    size_t i, j, n, granule;
    std::priority_queue<I> heap;
    std::set<I> bst;
    std::uniform_int_distribution<I> dist;
    std::random_device dev;
    unsigned int seed = dev();
    std::mt19937 prng(seed);

    if (argc > 1) {
        n = std::stoi(argv[1]);
    } else {
        n = 1000000;
    }
    if (argc > 2) {
        granule = std::stoi(argv[2]);
    } else {
        granule = 10;
    }
    randoms = new I[granule];
    for (i = 0; i < n / granule; ++i) {
        for (j = 0; j < granule; ++j) {
            randoms[j] = dist(prng);
        }

        // BST.
        auto start = std::chrono::high_resolution_clock::now();
        for (j = 0; j < granule; ++j) {
            bst.insert(randoms[j]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto dt_bst = end - start;

        // Heap.
        start = std::chrono::high_resolution_clock::now();
        for (j = 0; j < granule; ++j) {
            heap.emplace(randoms[j]);
        }
        end = std::chrono::high_resolution_clock::now();
        auto dt_heap = end - start;

        // Output.
        std::cout
            << std::chrono::duration_cast<std::chrono::nanoseconds>(dt_heap).count() << " "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(dt_bst).count() << std::endl;
    }
    delete[] randoms;

    // Sanity check.
    for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
        assert(*it == heap.top());
        heap.pop();
    }
}
