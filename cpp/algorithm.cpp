#include "common.hpp"

int main() {
    // # min
    //
    // # max
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

    // # swap
    //
    // Does things equivalent to:
    //
    //     template <class T> void swap (T& a, T& b)
    //     {
    //         T c(a); a=b; b=c;
    //     }
    //
    // However stdlib can specialize it to do operations more efficiently.
    //
    // Some stdlib classes implement swap as a method.
    //
    // Particularly important because of the copy and swap idiom.

    // # random_shuffle
    {
        std::vector<int> v{2, 0, 1};
        std::random_shuffle(v.begin(), v.end());
    }

#if __cplusplus >= 201703L
    // # sample
    //
    // https://stackoverflow.com/questions/6942273/how-to-get-a-random-element-from-a-c-container/42484107#42484107
    {
        const std::vector<int> in{1, 2, 3, 5, 7};
        std::vector<int> out;
        size_t nelems = 3;
        std::sample(in.begin(), in.end(), std::back_inserter(out),
                    nelems, std::mt19937{std::random_device{}()});
        std::set<int> in_set{std::begin(in), std::end(in)};
        std::set<int> out_set{std::begin(out), std::end(out)};

        // The sample elements are distinct.
        assert(out_set.size() == nelems);

        // The sample elements came from the input.
        std::set<int> intersect;
        std::set_intersection(
            in.begin(), in.end(), out.begin(), out.end(),
            std::inserter(intersect, intersect.begin())
        );
        assert(intersect.size() == nelems);

        //for (auto i : out)
        //    std::cout << i << std::endl;
    }
#endif

    // # equal
    //
    // Compares ranges of two containers.
    //
    // Vs memcmp:
    // https://stackoverflow.com/questions/39262496/why-is-stdequal-much-slower-than-a-hand-rolled-loop-for-two-small-stdarray
    {
        std::vector<int> v1{0, 1, 2   };
        std::vector<int> v2{   1, 2, 3};
        assert(std::equal(v1.begin() + 1, v1.end(), v2.begin()));
    }

    // # copy
    //
    // Vs memcpy: can compile down to an assembly optimized memcpy for arrays apparently, so just always use this:
    // https://stackoverflow.com/questions/4707012/is-it-better-to-use-stdmemcpy-or-stdcopy-in-terms-to-performance
    //
    // Handles overlap in the correct direction: https://stackoverflow.com/questions/1952972/does-stdcopy-handle-overlapping-ranges/53487672#53487672
    {
        // Newbie basic class usage.
        {
            std::vector<int> v{0, 1, 2, 3, 4};
            std::vector<int> v2(v.size(), v.size());
            std::copy(v.begin() + 1, v.end() - 1, v2.begin() + 2);
            assert(v2 == std::vector<int>({5, 5, 1, 2, 3}));
        }

        // # std::begin
        //
        // # std::end
        //
        // Array usage.
        //
        // https://stackoverflow.com/questions/7593086/why-use-non-member-begin-and-end-functions-in-c11
        {
            int v1[]{0, 1, 2, 3, 4};
            int v2[]{5, 5, 5, 5, 5};
            int v3[]{5, 5, 1, 2, 3};
            std::copy(std::begin(v1) + 1, std::end(v1) - 1, std::begin(v2) + 2);
            assert(std::equal(std::begin(v2), std::end(v2), std::begin(v3)));

            // Pointer usage.
            auto p1 = &v1[0];
            auto p2 = &v2[0];
            auto p3 = &v3[0];
            std::copy(p1 + 1, p1 + 4, p2 + 2);
            // Nah. Why.
            // https://stackoverflow.com/questions/26909429/stdbegin-and-stdend-not-working-with-pointers-and-reference-why
            //std::copy(std::begin(p1) + 1, std::begin(p1) + 4, std::begin(p2) + 2);
        }

        // Therefore, a more elegant class approach that uses exact same syntax as arrays.
        {
            std::vector<int> v1{0, 1, 2, 3, 4};
            std::vector<int> v2{5, 5, 5, 5, 5};
            std::vector<int> v3{5, 5, 1, 2, 3};
            std::copy(std::begin(v1) + 1, std::end(v1) - 1, std::begin(v2) + 2);
            assert(std::equal(std::begin(v2), std::end(v2), std::begin(v3)));
        }
    }

    // # accumulate
    //
    // Sum over range with operator+
    //
    // Also has functional versions http://www.cplusplus.com/reference/numeric/accumulate/
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

    // # find
    //
    // Return iterator to first found element.
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

    // # find_if
    //
    // Like find, but using an arbitrary condition on each element instead of equality.
    //
    // Consider usage with C++11 lambdas and functional.
    {
        std::vector<int> v{2, 0, 1};
        assert(std::find_if (v.begin(), v.end(), odd) == --v.end());
    }

    // # binary_search
    //
    // Container must be already sorted.
    //
    // Log complexity.
    //
    // Only states if the element is present or not, but does not get its position.
    //
    // If you want to get the position of those items, use `equal_range`, `lower_bound` or `upper_bound`.
    {
        std::vector<int> v{0, 1, 2};
        assert(std::binary_search(v.begin(), v.end(),     1) == true);
        assert(std::binary_search(v.begin(), v.end(),     3) == false);
        assert(std::binary_search(v.begin(), v.end() - 1, 2) == false);
    }

    // # lower_bound
    //
    // Finds first element in container which is not less than val.
    {
        std::vector<int> v{0, 2, 3};
        auto it = std::lower_bound(v.begin(), v.end(), 1);
        assert(it - v.begin() == 1);
    }

    // # upper_bound
    //
    // Finds first element in container is greater than val.
    {
        std::vector<int> v{0, 1, 2};
        auto it = std::upper_bound(v.begin(), v.end(), 1);
        assert(it - v.begin() == 2);
    }

    // # equal_range
    //
    // Finds first and last location of a value iniside a ranged container.
    //
    // Return values are the same as lower_bound and upper_bound.
    //
    // log complexity.
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


    // # max_element
    //
    // # min_element
    {
        std::vector<int> v{2,0,1};
        assert(*std::max_element(v.begin(), v.end()) == 2);
        assert(*std::min_element(v.begin(), v.end()) == 0);
    }

    // # advance
    //
    // Advance iterator by given number.
    //
    // If random access, simply adds + N.
    //
    // Else, calls `++` N times.
    //
    // Advantage over `+`: only random access containers support `+`,
    // but this works for any container, allowing one to write more general code.
    //
    // Beware however that this operation will be slow for non random access containers.
    {
        std::vector<int> v{0, 1, 2};
        auto it = v.begin();
        std::advance(it, 2);
        assert(*it == 2);
    }

#if __cplusplus >= 201103L
    // # next
    //
    // Same as advance, but returns a new iterator instead of modifying the old one.
    {
        std::vector<int> v{0, 1, 2};
        auto it(v.begin());
        auto itNext = std::next(it, 2);
        assert(*it == 0);
        assert(*itNext == 2);
    }
#endif

    // # remove_if
    //
    // Remove if a given function evaluates to true on an element.
    {
        {
            std::vector<int> v{0, 1, 2, 3, 4};
            auto end = v.end();
            v.erase(std::remove_if(v.begin(), end, odd), end);
            assert((v == std::vector<int>{0, 2, 4}));
        }

        // Common combo with lambdas
        {
            std::vector<int> v{0, 1, 2, 3, 4};
            auto end = v.end();
            v.erase(
                std::remove_if(
                    v.begin(),
                    end,
                    [](int i) {return i % 2 == 1;}
                ),
                end
            );
            assert((v == std::vector<int>{0, 2, 4}));
        }
    }

    // # transform
    //
    // Replace elements by output of a function.
    {
        std::vector<int> v{0, 1, 2};
        std::transform(
            v.begin(),
            v.end(),
            v.begin(),
            [](int i) {return i * i;}
        );
        assert((v == std::vector<int>{0, 1, 4}));
    }
}
