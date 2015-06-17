/*
# algorithm
*/

#include "common.hpp"

int main() {
    {
        assert(std::min(0.1, 0.2) == 0.1);
        assert(std::max(0.1, 0.2) == 0.2);
    }

    // # sort
    {
        std::vector<int> v{2, 0, 1};
        std::sort(v.begin(), v.end());
        std::vector<int> v1 = {0, 1, 2};
        assert((v == std::vector<int>{0, 1, 2}));
    }

    // # reverse
    {
        std::vector<int> v{2, 0, 1};
        std::reverse(v.begin(), v.end());
        assert((v == std::vector<int>{1, 0, 2}));
    }

    /*
    # swap

        Does things equivalent to:

            template <class T> void swap (T& a, T& b)
            {
                T c(a); a=b; b=c;
            }

        However stdlib can specialize it to do operations more efficiently.

        Some stdlib classes implement swap as a method.

        Particularly important because of the copy and swap idiom.
    */

    // # randomize
    {
        std::vector<int> v{2, 0, 1};
        std::random_shuffle(v.begin(), v.end());
    }

    // # copy
    {
        std::vector<int> v{2, 0, 1};
        std::vector<int> v2(5, 3);
        std::copy(v.begin(), v.end(), v2.begin() + 1);
        assert(v2 == std::vector<int>({3, 2, 0, 1, 3}));
    }

    /*
    # equal

        Compares ranges of two containers.
    */
    {
        std::vector<int> v {0, 1, 2   };
        std::vector<int> v2{   1, 2, 3};
        assert(std::equal(v.begin() + 1, v.end(), v2.begin()));
    }

    /*
    # accumulate

        Sum over range with operator+

        Also has functional versions http://www.cplusplus.com/reference/numeric/accumulate/
    */
    {
        {
            std::vector<int> v{2, 0, 1};
            assert(std::accumulate(v.begin(), v.end(), 0) == 3);
            assert(std::accumulate(v.begin(), v.end(), 10) == 13);
        }

        // The functional version can be used to add up arrays.
        // http://stackoverflow.com/questions/26941943/how-to-add-all-numbers-in-an-array-c
        {
            int a[] = {1, 3, 5, 7, 9};
            assert(std::accumulate(std::begin(a), std::end(a), 0, std::plus<int>()) == 25);
        }
    }

    /*
    # find

        Return iterator to first found element.
    */
    {
        std::vector<int> v{2,0,1};
        unsigned int pos;

        pos = std::find(v.begin(), v.end(), 0) - v.begin();
        assert(pos == 1);

        pos = std::find(v.begin(), v.end(), 1) - v.begin();
        assert(pos == 2);

        pos = std::find(v.begin(), v.end(), 2) - v.begin();
        assert(pos == 0);

        pos = std::find(v.begin(), v.end(), 3) - v.begin(); //end() returned
        assert(pos == v.size());
    }

    /*
    # find_if

        Like find, but using an arbitrary condition on each element instead of equality.

        Consider usage with C++11 lambdas and functional.
    */
    {
        std::vector<int> v{2, 0, 1};
        assert(std::find_if (v.begin(), v.end(), odd) == --v.end());
    }

    /*
    # binary_search

        Container must be already sorted.

        Log complexity.

        Only states if the element is present or not, but does not get its position.

        If you want to get the position of those items, use `equal_range`, `lower_bound` or `upper_bound`.
    */
    {

        std::vector<int> v{0, 1, 2};
        assert(std::binary_search(v.begin(), v.end(),     1) == true);
        assert(std::binary_search(v.begin(), v.end(),     3) == false);
        assert(std::binary_search(v.begin(), v.end() - 1, 2) == false);
    }

    /*
    # lower_bound

        Finds first element in container which is not less than val.
    */
    {
        std::vector<int> v{0, 2, 3};
        auto it = std::lower_bound(v.begin(), v.end(), 1);
        assert(it - v.begin() == 1);
    }

    /*
    # upper_bound

        Finds first element in container is greater than val.
    */
    {
        std::vector<int> v{0, 1, 2};
        auto it = std::upper_bound(v.begin(), v.end(), 1);
        assert(it - v.begin() == 2);
    }

    /*
    # equal_range

        Finds first and last location of a value iniside a ranged container.

        Return values are the same as lower_bound and upper_bound.

        log complexity.
    */
    {
        std::vector<int> v{0, 1, 1, 2};
        std::vector<int>::iterator begin, end;
        std::tie(begin, end) = std::equal_range(v.begin(), v.end(), 1);
        assert(begin - v.begin() == 1);
        assert(end   - v.begin() == 3);
    }

    // # count
    {
        std::vector<int> v{2,1,2};
        assert(std::count(v.begin(), v.end(), 0) == 0);
        assert(std::count(v.begin(), v.end(), 1) == 1);
        assert(std::count(v.begin(), v.end(), 2) == 2);
    }


    // # max_element #min_element
    {
        std::vector<int> v{2,0,1};
        assert(*std::max_element(v.begin(), v.end()) == 2);
        assert(*std::min_element(v.begin(), v.end()) == 0);
    }

    /*
    # advance

        Advance iterator by given number.

        If random access, simply adds + N.

        Else, calls `++` N times.

        Advantage over `+`: only random access containers support `+`,
        but this works for any container, allowing one to write more general code.

        Beware however that this operation will be slow for non random access containers.
    */
    {
        std::vector<int> v{0, 1, 2};
        auto it = v.begin();
        std::advance(it, 2);
        assert(*it == 2);
    }

#if __cplusplus >= 201103L
    /*
    # next

        Same as advance, but returns a new iterator instead of modifying the old one.
    */
    {
        std::vector<int> v{0, 1, 2};
        auto it(v.begin());
        auto itNext = std::next(it, 2);
        assert(*it == 0);
        assert(*itNext == 2);
    }
#endif

    /*
    # priority queue

        Offers `O(1)` access to the smalles element.

        Other operatoins vary between `O(n)` and `O(1).

        Most common implementaions are via:

        - binary heap
        - fibonacci heap

        Boost offers explicit heap types: fibonacci, binary and others.

        But no guarantees are made.

        As of C++11, does not support the increase key operation.

        A binary heap without increase key can be implemented via the heap function family under algorithm.
    */

    /*
    # heap

        Binary heap implementation.

        <http://en.wikipedia.org/wiki/Heap_%28data_structure%29>

        In short:

        - getting largest element is O(1)
        - removing the largest element is O(lg) for all implementation
        - other operations (insertion) may be O(1) or O(lg) depending on the implementation.

        this makes for a good priority queue.
        Exact heap type is not guaranteed. As of 2013, it seems that most implementations use binary heaps.

        For specific heaps such as Fibonacci, consider [Boost](http://www.boost.org/doc/libs/1_49_0/doc/html/heap.html).

        <http://stackoverflow.com/questions/14118367/stl-for-fibonacci-heap>

        There is no concrete heap data structure in C++:
        only heap operations over random access data structures.
        This is why this is under algoritms and is not a data structure of its own.

        There is however a `priority_queue` stdlib container.

        Why random access structure is needed: <https://github.com/cirosantilli/comp-sci/blob/1.0/src/heap.md#array-implementation>
    */
    {
        int myints[]{10, 20, 30, 5, 15};
        std::vector<int> v(myints, myints + 5);

        /*
        # make_heap

            Make random access data structure into a heap.

            This changes the element order so that the range has heap properties

            Worst case time: $O(n)$.
        */
            std::make_heap(v.begin(), v.end());
            assert(v.front() == 30);

        /*
        # pop_heap

            Remove the largest element from the heap.

            That element is moved to the end of the data structure, but since the
            heap should have its length reduced by one, that element will then be out of the heap.

            Assumes that the input range is already a heap (made with `make_heap` for example).
        */
            std::pop_heap(v.begin(), v.end());

            //the element still exists on the data structure
            assert(v.back() == 30);

            //the second largest element hat become the largets
            assert(v.front() == 20);

            //remove the element from the data structure definitively
            v.pop_back();

        /*
        # push_heap

            Insert element into a heap.

            Assumes that:

            - the range 0 - (end - 1) was already a heap
            - the new element to be inserted into that heap is at end.
        */

            //add the new element to the data structure
            v.push_back(99);

            //reorganize the data so that the last element will be placed in the heap
            std::push_heap(v.begin(), v.end());

            assert(v.front() == 99);

        /*
        # sort_heap

            Assumes that the input range is a heap, and sorts it in increasing order.

            The assumption that we have a heap allows for $O(ln)$ sorting,
            much faster than the optimal bound $O(n log n)$.

            This is exactly what the heapsort alrotithm does: make_heap and then sort_heap.
        */

            std::sort_heap(v.begin(), v.end());
            //assert(v)
            //v == 5 10 15 20 99
    }
}
