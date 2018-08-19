#include "common.hpp"

int main(int argc, char **argv) {
    size_t i, n;
    std::priority_queue<int> heap;
    std::set<int> bst;
    std::random_device dev;
    unsigned int seed = dev();
    std::mt19937 prng(seed);
    std::uniform_int_distribution<> dist;
    if (argc > 1) {
        n = std::stoi(argv[1]);
    } else {
        n = 1000000;
    }

    for (i = 0; i < n; ++i) {
        auto random_value = dist(prng);

        // BST.
        auto start = std::chrono::steady_clock::now();
        auto ret = bst.insert(random_value);
        auto end = std::chrono::steady_clock::now();
        auto dt_bst = end - start;
        // Heaps can have dupes, BST cannot, so skip them for both.
        if (!ret.second) continue;

        // Heap.
        start = std::chrono::steady_clock::now();
        heap.push(random_value);
        end = std::chrono::steady_clock::now();
        auto dt_heap = end - start;

        std::cout << random_value << " "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(dt_heap).count() << " "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(dt_bst).count() << std::endl;
    }

    // Sanity check.
    for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
        assert(*it == heap.top());
        heap.pop();
    }
}
