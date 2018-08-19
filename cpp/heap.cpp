/* First learn how binary heaps work, and how they can efficiently implement
 * Dijkstra more efficiently than BST:
 * https://stackoverflow.com/questions/6147242/heap-vs-binary-search-tree-bst/29548834#29548834
 *
 * There are two ways to make priority queues in C++:
 *
 * -   `make_heap` and other functions in the family, which implement a heap
 *     on top of a random access container, typically std::vector.
 *
 * -   `priority_queue` class, which seems to just use `std::vector` + `make_heap` by default
 *     internally: https://stackoverflow.com/questions/11266360/when-should-i-use-make-heap-vs-priority-queue
 */

#include "common.hpp"

int main() {
    int myints[]{10, 20, 30, 5, 15};
    std::vector<int> v(myints, myints + 5);

    // Heap functions.
    {
        /* # make_heap
         *
         * Make random access data structure into a heap.
         */
        {
            std::make_heap(v.begin(), v.end());
            assert(v.front() == 30);
        }

        /* # pop_heap
         *
         * Remove the largest element from the heap.
         *
         * That element is moved to the end of the data structure, but since the
         * heap should have its length reduced by one, the element is effectively removed.
         *
         * Assumes that the input range is already a heap, made with `make_heap` for example.
         */
        {
            std::pop_heap(v.begin(), v.end());

            // The element still exists on the data structure.
            assert(v.back() == 30);

            // The second largest element hat become the largest.
            assert(v.front() == 20);

            // Remove the element from the data structure definitively
            v.pop_back();
        }

        /* # push_heap
         *
         * Insert element into a heap.
         *
         * Assumes that:
         *
         * - the range 0 - (end - 1) was already a heap
         * - the new element to be inserted into that heap is at end.
         */
        {
            // Add the new element to the data structure.
            v.push_back(99);

            // Reorganize the data so that the last element will be placed in the heap.
            std::push_heap(v.begin(), v.end());

            assert(v.front() == 99);
        }

        /* # sort_heap
         *
         * Assumes that the input range is a heap, and sorts it in increasing order.
         *
         * The assumption that we have a heap allows for $O(ln)$ sorting,
         * much faster than the optimal bound $O(n log n)$.
         *
         * This is exactly what the heapsort algorithm does: make_heap and then sort_heap.
         */
        {
            std::sort_heap(v.begin(), v.end());
            //assert(v)
            //v == 5 10 15 20 99
        }
    }

    /* # priority_queue
     *
     * It could however use some other implementation in theory, and it does seem that GCC libstdc++ does provide
     * a few alternatives with the policy base
     *
     * No Fibonacci as of 7.3.0 however:
     *
     * - https://gcc.gnu.org/onlinedocs/gcc-7.3.0/libstdc++/manual/manual/policy_based_data_structures_test.html#performance.priority_queue
     * - http://stackoverflow.com/questions/14118367/stl-for-fibonacci-heap
     *
     * TODO As of C++11, does not support the increase key operation.
     *
     * Boost offers explicit heap types: Fibonacci, binary and others.
     */
    {
        // max
        {
            std::priority_queue<int> q;
            for(int n : {1,8,5,6,3,4,0,9,7,2})
                q.push(n);
            assert(q.top() == 9);
            q.pop();
            assert(q.top() == 8);
            q.pop();
            assert(q.top() == 7);
            q.pop();
        }

        // min
        {
            std::priority_queue<int, std::vector<int>, std::greater<int>> q;
            for(int n : {1,8,5,6,3,4,0,9,7,2})
                q.push(n);
            assert(q.top() == 0);
            q.pop();
            assert(q.top() == 1);
            q.pop();
            assert(q.top() == 2);
            q.pop();
        }

        // Dupes are accepted unlike in sets.
        {
            std::priority_queue<int, std::vector<int>, std::greater<int>> q;
            q.push(1);
            q.push(1);
            assert(q.size() == 2);
        }
    }
}
