/*
# vector

    Array backed conatiner that grows / shrinks as necessary.

    $O(1)$ random access.

    $O(n)$ element removal from interior

    $O(1)$ element append to end (amortized, $O(n)$ worst case)

    All methods that work for several SLT containers shall only be cheated here once.
*/

#include "common.hpp"

int main() {
    // Create
    {
        // Empty
        {
            std::vector<int> v;
            // C++11 initializer lists:
            std::vector<int> v1{};
            assert(v == v1);
        }

        // Given size
        {
            std::vector<int> v(3);
            assert(v.size() == 3);
        }

        /*
        Fill constructor.

        Make a `std::vector` with n copies of a single value.
        */
        {
            // Copies of given object.
            {
                assert(std::vector<int>(3, 2) == std::vector<int>({2, 2, 2}));
            }

            // Default constructed objects. int = 0.
            {
                assert(std::vector<int>(3) == std::vector<int>({0, 0, 0}));
            }
        }

        // Range copy.
        {
            std::vector<int> v{0, 1, 2};
            std::vector<int> v1(v.begin(), v.end());
            assert(v == v1);
        }

        // From existing array.
        {
            int myints[]{0, 1, 2};
            std::vector<int> v(myints, myints + sizeof(myints) / sizeof(int));
            std::vector<int> v1 = {0, 1, 2};
            assert(v == v1);
        }
    }

    // Vectors have order.
    {
        std::vector<int> v{0, 1, 2};
        std::vector<int> v1{2, 1, 0};
        assert(v != v1);
    }

    /*
    # Contigous storage

    # Data

        Storage is required to be contiguous by TR1:
        http://stackoverflow.com/questions/849168/are-stdvector-elements-guaranteed-to-be-contiguous

        C++11 introduces the `data()` method which returns a pointer to the first element.
        It works even if the vector is empty.
        http://stackoverflow.com/questions/6485496/how-to-get-stdvector-pointer-to-the-raw-data

        Before C++11, `&v[0]` works for non-empty vectors.

        `vector<bool>` as usual is an exception.
    */
    {
        std::vector<int> v{0, 1, 2};
        assert(&v[0] == v.data());
        // True because contiguous:
        assert(v.data()[1] == v[1]);
    }

    // size methods
    {
        /*
        # size

        # length of vector

        # size_type

            Number of elements in std::vector.

            This has type std::vector<X>::size_type
        */
        {
            std::vector<int> v;
            assert(v.size() == 0);
            v.push_back(0);
            assert(v.size() == 1);
        }

        /*
        # resize

            If larger than current size, append given element at end.

            If smaller than current size, remove elements from end.
        */
        {
            // Reduce size
            {
                std::vector<int> v{0, 1};
                v.resize(1);
                assert((v == std::vector<int>{0}));
            }

            // Increase size
            {
                // Using default constructor objects.
                {
                    std::vector<int> v{1};
                    v.resize(3);
                    assert((v == std::vector<int>{1, 0, 0}));
                }

                // Using copies of given object.
                {
                    std::vector<int> v{1};
                    v.resize(3, 2);
                    assert((v == std::vector<int>{1, 2, 2}));
                }
            }
        }
    }

    // Capacity methods.
    {
        /*
        # capacity

            Get currently allocated size.

            Different from size, which is the number of elements in the std::vector!

            At least as large as size.

            Likely to be a power of 2 on most implementations.
        */
        {
            std::vector<int> v;
            v.push_back(0);
            v.push_back(1);
            v.push_back(2);
            assert(v.capacity() >= 3);
            std::cout << "capacity = " << v.capacity() << std::endl;
        }

        // # max_size: estimative of what your OS allows you to allocate
        {
            std::cout << "max_size (MiB) = " << std::vector<int>().max_size() / (1 << 20) << std::endl;
        }

        // # reserve: increase allocated size if larger than current size.
        {
            std::vector<int> v;
            v.reserve(3);
            assert(v.capacity() >= 3);
            // size() is untouched
            assert(v.empty());
        }

#if __cplusplus >= 201103L
        // # shrink_to_fit
        {
            std::vector<int> v{0, 1};
            v.reserve(4);
            v.shrink_to_fit();
            assert(v.capacity() == 2);
        }
#endif
    }

    // `std::vector` stores copies of elements, not references.
    {
        std::string s = "abc";
        std::vector<std::string> v{s};
        v[0][0] = '0';
        assert(v[0] == "0bc");
        assert(s    == "abc");
    }

    // Modify.
    {
        {
            std::vector<int> v;
            v = {0};
            v = {0, 1};
            assert((v == std::vector<int>{0, 1}));
        }

        /*
        # push_back

        # append

            Push to the end of the std::vector.

            Amortized time O(1), but may ocassionaly make the std::vector grow,
            which may required a full data copy to a new location if the
            current backing array cannot grow.

        # push_front

            Does not exist for std::vector, as it would always be too costly (requires to move
            each element forward.) Use deque if you need that.
        */
        {
            std::vector<int> v;
            std::vector<int> v1;

            v.push_back(0);
            v1 = {0};
            assert(v == v1);

            v.push_back(1);
            v1 = {0, 1};
            assert(v == v1);

            /*
            push_back makes copies with assign `=`

            If you want references, use pointers, or even better, auto_ptr.
            */
            {
                std::vector<std::string> v;
                std::string s = "abc";

                v.push_back(s);
                v[0][0] = '0';
                assert(v[0] == "0bc");

                //s was not changed
                assert(s == "abc");
            }
        }

        /*
        # pop_back

            Remove last element from std::vector.

            No return val. Rationale: http://stackoverflow.com/questions/12600330/pop-back-return-value
        */
        {
            std::vector<int> v{0, 1};

            v.pop_back();
            assert(v == std::vector<int>{0});

            v.pop_back();
            assert(v == std::vector<int>{});
        }

        /*
        # insert

            This operation is inneficient for `std::vector` if it is not done at the end.

        # concatenate

            The range form of insert can be used to append one vector to anoter.
        */
        {
            // Single element form.
            {
                std::vector<int> v = {0,1};
                std::vector<int> v1;

                v.insert(v.begin(), -1);
                v1 = {-1, 0, 1};
                assert(v == v1);

                v.insert(v.end(), 2);
                v1 = {-1, 0, 1, 2};
                assert(v == v1);
            }

            // Range form.
            {
                std::vector<int> v = {0,1};
                std::vector<int> v1 = {2,3};

                v.insert(v.end(), v1.begin(), v1.end());
                assert((v == std::vector<int>{0, 1, 2, 3}));
            }
        }

        /*
        # erase

            Remove given elements from container given iterators to those elements.

            This operation is inneficient for std::vectors,
            since it may mean reallocation and therefore up to $O(n)$ operations.

            Returns a pointer to the new location of the element next to the last removed element.
        */
        {
            // Single element
            {
                std::vector<int> v{0, 1, 2};
                auto it = v.erase(v.begin() + 1);
                assert((v == std::vector<int>{0, 2}));
                assert(*it == 2);
            }

            // Range
            {
                std::vector<int> v{0, 1, 2, 3};
                auto it = v.erase(v.begin() + 1, v.end() - 1);
                assert((v == std::vector<int>{0, 3}));
                assert(*it == 3);
            }
        }

        /*
        # remove

            Helper to remove all elements that compare equal to a value from container.

            Does not actually remove the elements: only ensures that the beginning of the range
            does not contain the item to be removed.

            Ex:

                0, 1, 0, 2, 0, 1

            Value to remove: `0`

            Range to remove from:

                0, 1, 0, 2, 0, 1
                ----------

            After the remove:

                1, 2, X, Y, 0, 1
                ----------

            where `X` and `Y` are trash, and not necessarily 0!

            To actually remove the items, an `erase` is needed after remove
            because `remove` is not a class method and thus cannot remove items from a container.

            This is called the erase and remove idiom.

            After a remove the container becomes:

                1, 2, 0, 1

        # erase and remove idiom

        # remove and erase idiom

            See remove.
        */
        {
            // Verbose version
            {
                std::vector<int> v{0, 1, 0, 2, 0, 1};
                auto end = std::next(v.end(), -2);
                auto firstTrashIt = std::remove(v.begin(), end, 0);
                // Unpredictable result:
                std::cout << "remove:";
                for (auto& i : v) std::cout << " " << i;
                std::cout << std::endl;
                v.erase(firstTrashIt, end);
                assert((v == std::vector<int>{1, 2, 0, 1}));
            }

            // Compact version
            {
                std::vector<int> v{0, 1, 0, 2, 0, 1};
                auto end = std::next(v.end(), -2);
                v.erase(std::remove(v.begin(), end, 0), end);
                assert((v == std::vector<int>{1, 2, 0, 1}));
            }
        }

        // # remove_if
        // # filter
        // Algorithm. Remove if a given function evaluates to true on an element.
        {
            std::vector<int> v{0, 1, 2, 3, 4};
            auto end = v.end();
            v.erase(std::remove_if(v.begin(), end, odd), end);
            assert((v == std::vector<int>{0, 2, 4}));

            // Common combo with lambdas
            {
                std::vector<int> v{0, 1, 2, 3, 4};
                auto end = v.end();
                v.erase(std::remove_if(v.begin(), end,
                    [](int i) {return i % 2 == 1;}), end);
                assert((v == std::vector<int>{0, 2, 4}));
            }
        }

        // # transform
        // Algorithm. Replace elements by output of a function.
        {
            std::vector<int> v{0, 1, 2};
            std::transform(v.begin(), v.end(), v.begin(),
                    [](int i) {return i * i;});
            assert((v == std::vector<int>{0, 1, 4}));
        }

        // # clear
        // Make the vector empty.
        {
            std::vector<int> v{0, 1, 2};
            v.clear();
            assert(v.empty());
        }

        /*
        # print vector

        # vector to string

            No built-in way.

            http://stackoverflow.com/questions/4850473/pretty-print-c-stl-containers
            190 votes on question, 30 on top answer! Come on C++!

            http://stackoverflow.com/questions/1430757/c-vector-to-string?lq=1
        */
        // ERROR: no default operator `<<`.
        //cout << v;
    }

    // Random access is O(1) since array backed
    {

        std::vector<int> v{0, 1, 2};

        // First element:
        assert(v.front() == 0);
        assert(v.front() == v[0]);

        // Last element:
        assert(v.back() == 2);

        // Nth element:
        v[0] = 1;
        assert(v[0] == 1);

        /*
        BAD: just like array overflow will not change std::vector size,
        and is unlikelly to give an error
        */
        {
            //v1[2] = 2;
        }

        /*
        # back  Get reference to last  element in vector.
        # front Get reference to first element in vector.
        # at    Like `[]`, but does bound checking and throws `out_of_range` in case of overflow.
        */
        {
            std::vector<int> v{0, 1, 2};
            assert(v.front() == 0);
            assert(v.at(1)   == 1);
            assert(v.back()  == 2);
            try {
                assert(v.at(3) == 0);
            } catch (std::out_of_range& e) {
            } catch (...) {
                assert(false);
            }

            /* Undefined on empty. */
            {
                std::vector<int> v;
                //v.front();
                //v.back();
            }
        }
    }

    /*
    # bool std::vector

        *bool std::vectors are evil!*

        The standard requires `vector` to have an specialization for bool which packs bits efficiently.

        While efficient, in order to work this specialization breaks common std::vector interfaces
        that require taking addresses only in the case of this specialization, since it does not
        make sense to takes addresses anymore.

        Alternatives to `vector<bool>`: <http://stackoverflow.com/questions/670308/alternative-to-vectorbool>

        A good alternative seem to be deque<bool>, which behaves as intended.
    */
    {
        // Works fine and dandy as expected.
        {
            std::vector<int> v{1, 0};
            int& i(v[0]);
        }

        // Does not compile!!!
        {
            std::vector<bool> v{true, false};
            //bool& b(v[0]);
        }

        // It was not a problem with bool, the problem really is `vector<bool>`.
        {
            bool b[]{true, false};
            bool& b2(b[0]);
        }
    }
}
