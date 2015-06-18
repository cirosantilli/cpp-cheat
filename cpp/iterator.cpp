/*
# iterator

    Iteration could be done with random access in certain data structures with a for i loop.

    Iterators are better becase you can also use them for structures without random access,
    so if you decide to change structures in the future the job will be much easier.

    # iterator categories

        Iterators are categorized depending on the operations they can do:

            <http://www.cplusplus.com/reference/iterator/>

        The clases are (from least to most versatile):

        - Input Output
        - Forward
        - Bidirectional
        - Random Access

        The most versatile iterators (random access) behave much like pointers,
        and overload most pointer operations such as integer increment `it + 1` and
        pointer dereference `*it` in a similar way to pointers.

        Those classes are not language enforced via inheritance like in Java,
        but could be used by programmers to implement typedefs that explain
        the types of operations permitted. So if you are going to use a typedef
        solution not to tie yourself to a given container, consider naming the
        typdefed as one of the classes to indicate the operationt can do:

            typedef random_it std::vector<int>::iterator;

        It is possible to retreive the class of an interator via `std::iterator_traits<ITER>::interator_category`.
*/

#include "common.hpp"

int main() {
    // Before C++11: begin and end were the only way to use iterators.
    // After C++11; the range based syntax is the best way to use them.
    {
        /*
        # forward iteration

            Can be done on all containers.

            # begin

                Returns an iterator to the first element.

            # end

                Returns an iterator to the first element *after* the last.
        */
        {
            std::vector<int> v{1, 2, 0};
            int i = 0;
            int is[]{1, 2, 0};

            for (auto it = v.begin(); it != v.end(); ++it) {
                assert(*it == is[i]);
                ++i;
            }
        }

        /*
        # backwards iteration

            Can only be done on biderectional containers.

            # rbegin

                Reversed begin.

                Returns a `reverse_iterator` that points to the last emlement.

                ++ on reversed iterators decreases them.

            # rend

                Returns a reversed iterator to the element before the first.
        */
        {
            std::vector<int> v{1, 2, 0};
            int i;
            int is[]{1, 2, 0};

            i = 2;
            for (auto it = v.rbegin(); it != v.rend(); ++it) {
                assert(*it == is[i]);
                //cout << *it << endl;
                --i;
            }
        }
    }

    /*
    # range based for loop #foreach

        C++11

        Like python foreach or Java improved-for loop.

        This is the best way to iterate a container with C++11.

        Much easier to write or read.

        Also have the advantage that you don't need to specify iterator type!

        Behind the scenes, this method is still based on iterators,
        and the class to be iterated needs to implement:

        - begin()
        - end()

        And the iterator returned must implement:

        - operator++()
        - operator!=()
        - operator*()
    */
    {
#if __cplusplus >= 201103L
        //forward
        {
            // If `int&` is used, no useless copies are made.
            // and the vector can be modified directly.
            {
                std::vector<int> v{1, 2, 0};
                int is[]{1, 2, 0};
                int i = 0;
                for (int& iv : v) {
                    assert(iv == is[i]);
                    //cout << iv << endl;
                    iv++;
                    i++;
                }
                assert((v == std::vector<int>{2, 3, 1}));
            }

            // Without `&`, makes copies of each element.
            // Usually not what we want.
            {
                std::vector<int> v{1, 2, 0};
                int is[]{1, 2, 0};
                int i = 0;
                for (int iv : v) {
                    assert(iv == is[i]);
                    //cout << iv << endl;
                    iv++;
                    i++;
                }
                assert((v == std::vector<int>{1, 2, 0}));
            }

            // Less code duplication with auto.
            // This is the best way to do it.
            {
                std::vector<int> v{1, 2, 0};
                int is[]{1, 2, 0};
                int i = 0;
                for (auto& iv : v) {
                    assert(iv == is[i]);
                    //cout << *it << endl;
                    i++;
                }
            }
        }

        /*
        # range based for loop for arrays

            Also works for bare arrays for which the size is known at compile time!
        */
        {
            {
                int is[]{1, 2};
                for (int& i : is) {
                    i *= 2;
                }
                assert(is[0] == 2);
                assert(is[1] == 4);
            }

            /*
            does not work for dynamic memory since
            there would be no way to know the array size at compile time
            */
            {
                //int *is = new int[2];
                //is[0] = 1;
                //is[0] = 2;
                //for (int &i : is) {
                //    i *= 2;
                //}
                //delete[] is;
            }
        }
#endif
        /*
        backwards

            TODO possible? Seems not out of the C++11 box: <http://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop>

            Auto is a lifesaver here to avoid typing the iterator type.
        */
        {
            std::vector<int> v = {1, 2, 0};
            int i;
            int is[] = {1, 2, 0};

            //forward
            {
                i = 2;
                for (auto it = v.rbegin(); it != v.rend(); ++it) {
                    assert(*it == is[i]);
                    //cout << *it << endl;
                    i--;
                }
            }
        }
    }

    /*
    # generic containers

        There is no standard iterator independent from container.

        This can be done via type erasure techinques.

        But would mean loss of performance because of lots of polymorphic calls
        and stdlib is obssessed with performance.

        The best solution seems to use typedefs:

            typedef it_t std::vector<int>::iterator;

        And then if ever your container changes all you have to do is modify one single typedef:

            typedef it_t set<int>::iterator;

        TODO isnt auto and range based for a better solution in c++11?
    */
    {
        std::vector<int> v{1, 2};
        std::set<int> s{1, 2};
        std::vector<int>::iterator itVec(v.begin());
        std::set<int>::iterator itSeti(s.begin());

        // Does not exist:

            //iterator<int> itVec = v.begin();
            //iterator<int> itSeti = s.begin();

        // Best workaround is using auto:

            auto vit(v.begin());
            auto sit(v.begin());
    }

    // No born checking is done
    {
        std::vector<int> v{1, 2};

        // Last element.
        *(v.end() - 1);

        // After last element no born check.
        *(v.end());

        // No such method.
        //(v.end().hasNext());
    }

    /*
    Base pointers and arrays can be used anywhere iterators can.

    The stdlib functions have specializations for pointers.

    <http://stackoverflow.com/questions/713309/c-stl-can-arrays-be-used-transparently-with-stl-functions>
    */
    {
        int is[]{2, 0, 1};
        int j = 0;
        for (auto& i : is) {
            assert(i == is[j]);
            j++;
        }
    }

    /*
    # size_t for containers

        See size_type.

    # size_type

        Random access containers such as std::vectors, strings, etc have a `size_type` member typedef
        that represents a type large enough to hold its indexes.

        For arrays, this type is exactly the C `size_t`.

        For a std::vector, it will also probably be `size_t`, since std::vectors are array backed,
        but using `size_type` gives more generality.

        This type is returned by methods such as `size()`.
    */
    {
        std::vector<int> v{2, 0, 1};
        std::vector<int>::size_type i(1);
        v[i] = 1;
    }

    /*
    # iterator_traits

        Contain information about iterators.

        This allows to create template functions that take generic iterators independent of the
        exact container type as is the case for many function sunder `<algorithm>`.
    */
    {
        //value_type
        //pointer
        //reference
        {
            typedef std::iterator_traits<std::vector<int>::iterator>::value_type ValueType;
            typedef std::iterator_traits<std::vector<int>::iterator>::pointer    Pointer;
            typedef std::iterator_traits<std::vector<int>::iterator>::reference  Reference;
            assert(typeid(ValueType) == typeid(int));
            assert(typeid(Pointer)   == typeid(int*));
            assert(typeid(Reference) == typeid(int&));
        }

        /*
        # difference_type

            The type returned on a difference between two pointers.

            Unlike size_type, this value is signed, since the difference may well be negative.
        */
        {
            typedef typename std::iterator_traits<std::vector<int>::iterator>::difference_type DifferenceType;
            std::vector<int> v{0, 1};
            assert(typeid(v.end() - v.begin()) == typeid(DifferenceType));
        }

        /*
        # iterator_category

            iterator_category is a struct *type*, not a value.

            Therefore, in order to compare it one must use `typeid`.
        */
        {
            assert(typeid(std::iterator_traits<std::vector<int>::iterator>::iterator_category)
                    == typeid(std::random_access_iterator_tag));
        }
    }
}
