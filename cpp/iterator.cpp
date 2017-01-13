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

template<typename T>
class MyInsertIterator : public std::insert_iterator<T> {
    public:
        using std::insert_iterator<T>::insert_iterator;
        MyInsertIterator& operator=(const typename T::value_type& rhs) {
            this->std::insert_iterator<T>::operator=(rhs + 1);
            // Same, but a bit less DRY.
            //this->container->insert(rhs + 1);
        }
        MyInsertIterator& operator=(const std::string& rhs) {
            this->std::insert_iterator<T>::operator=(std::stoi(rhs));
        }
};

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

#if __cplusplus >= 201103L
    /*
    # range based for loop

    # foreach

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

        Those methods are usually trivial, except for ++ which can actually
        make a smart choice of what is the next value.
        I bet http://www.boost.org/doc/libs/1_62_0/libs/iterator/doc/index.html
        will make implementation easier with some defaults.
    */
    {
        // Implement it yourself.
        {
            class Iterable {
                private:
                    class Iterator {
                        public:
                            Iterator(int *ip) : ip(ip) {}
                            Iterator& operator++() {
                                this->ip++;
                                return *this;
                            }
                            bool operator!=(const Iterator& other) const {
                                return this->ip != other.ip;
                            }
                            // cont& could be used if there is no backing data,
                            int& operator*() const {
                                return *this->ip;
                            }
                        private:
                            int *ip;
                    };
                public:
                    Iterable() : is{1, 2, 3} {
                    }
                    Iterator begin() {
                        return Iterator(&is[0]);
                    }
                    Iterator end() {
                        return Iterator(&is[3]);
                    }
                private:
                    int is[3];
            };

            // Range based for loop works with that bare skelleton.
            // Try removing any method of the above, and watch it blow up.
            {
                int sum = 0;
                Iterable it;
                for (auto const& x : it) {
                    sum += x;
                }
                assert(sum == 6);
            }

            // Modification is also possible with this
            // default-ish setup and references.
            {
                int sum = 0;
                Iterable it;
                for (auto& x : it) {
                    x++;
                }
                for (auto& x : it) {
                    sum += x;
                }
                assert(sum == 9);
            }
        }

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

            // forward
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

        // POSSIBLE RUNTIME ERROR.
        // After last element no born check.
        //*(v.end());

        // No such method.
        //(v.end().hasNext());
    }

    /*
    Base pointers and arrays can be used anywhere iterators can.

    The stdlib functions have specializations for pointers.

    http://stackoverflow.com/questions/713309/c-stl-can-arrays-be-used-transparently-with-stl-functions
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

    /*
    # const_iterator

        begin is overloaded by method const-ness, to return either
        ::iterator or ::const_iterator

        http://stackoverflow.com/questions/12646998/how-does-begin-know-which-return-type-to-return-const-or-non-const

        const_iterator returns const values, so it cannot be used to modify the container.
    */
    {
        // Basic example.
        {
            const std::vector<int> v{0};

            // ERROR.
            //std::vector<int>::iterator it = v.begin();

            // OK.
            std::vector<int>::const_iterator it = v.begin();
            // ERROR: cannot modify because const_iterator.
            //*it = 1;
        }

        // iterator can be converted to const_iterator.
        {
            std::vector<int> v{0};
            std::vector<int>::iterator it = v.begin();
            *it = 1;
            std::vector<int>::const_iterator itc = it;
            // ERROR.
            //*itc = 1;
        }
    }

    /*
    # Output Iterators

        Assignment inserts with some function, dereference returns *this.

        Used by several `algorithm` functions.

    # insert_iterator

        Inserts with `.insert()`.

    # inserter

        Convenience function that saves a lot of typing with auto.

        http://stackoverflow.com/questions/9270563/what-is-the-purpose-of-stdmake-pair-vs-the-constructor-of-stdpair/41521422#41521422

    # back_inserter

    # back_insert_iterator

    # front_inserter

    # front_insert_iterator

        Analogous to `inserter`, but with `push_back` and `push_front`..
    */
    {
        // vector example.
        {
            std::vector<int> v{0, 1};
            // inserter + auto saves us from typing:
            // std::insert_iterator<std::vector<int>>
            auto it = std::inserter(v, v.end());
            it = 2;
            it++;
            // Dereference is the same as without, thus useless here.
            ********it = 3;
            assert(v == std::vector<int>({0, 1, 2, 3}));
        }

        // set example.
        // begin vs end
        // http://stackoverflow.com/questions/5909624/is-there-a-difference-between-using-begin-vs-end-for-stdinserter-for-std
        {
            std::set<int> s{0, 1};
            auto it = std::inserter(s, s.end());
            it = 2;
            it++;
            it = 3;
            assert(s == std::set<int>({0, 1, 2, 3}));
        }

        /*
        Modify value before inserting.

        TODO: easier way, maybe with boost iterators?

        Some algorithms like std::transform also take an unary predicate
        that does the job, but it may be that the algorithm does not have such API.
        */
        {
            std::set<int> v{0, 1};
            auto it = MyInsertIterator<decltype(v)>(v, v.end());

            // Increment and insert.
            it = 2;
            it++;
            it = 3;
            it++;

            // Adapt a different input type.
            it = "5";

            assert(v == std::set<int>({0, 1, 3, 4, 5}));
        }
    }
}
