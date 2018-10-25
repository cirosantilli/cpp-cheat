/* # POD
 *
 * Plain old data:
 *
 * - https://en.cppreference.com/w/cpp/named_req/PODType
 * - https://stackoverflow.com/questions/146452/what-are-pod-types-in-c
 * - http://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special
 * - https://github.com/gcc-mirror/gcc/blob/gcc-8_2_0-release/libstdc%2B%2B-v3/testsuite/20_util/is_pod/value.cc a few tests, but nothing awesome
 */

#include <type_traits>

int main() {
/* POD restrictions have become more and more relaxed as the standard evolved.
 *
 * std::is_pod was added in C++11, so let's consider that standard onwards for now.
 */
#if __cplusplus >= 201103L
    /* Non-POD examples. Let's just walk all non-recursive non-POD branches of cppreference. */
    {
        /* Non-trivial implies non-POD.
         * https://en.cppreference.com/w/cpp/named_req/TrivialType
         */
        {
            /* Not trivial because we removed the default constructor
             * by using our own custom non-default constructor.
             */
            {
                struct C {
                    C(int i) {}
                };
                static_assert(std::is_trivially_copyable<C>());
                static_assert(!std::is_trivial<C>());
                static_assert(!std::is_pod<C>());
            }

            /* Not trivial because not trivially copyable. */
            {
                struct C {
                    C(C& c) {}
                };
                static_assert(!std::is_trivially_copyable<C>());
                static_assert(!std::is_trivial<C>());
                static_assert(!std::is_pod<C>());
            }
        }

        /* Non-standard layout implies non-POD.
         * https://en.cppreference.com/w/cpp/named_req/StandardLayoutType
         */
        {
            /* Non static members with different access control:
             * i is public and j is private.
             */
            {
                struct C {
                    public:
                        int i;
                    private:
                        int j;
                };
                static_assert(!std::is_standard_layout<C>());
                static_assert(!std::is_pod<C>());
            }

            /* virtual function */
            {
                struct C {
                    virtual void f() = 0;
                };
                static_assert(!std::is_standard_layout<C>());
                static_assert(!std::is_pod<C>());
            }

            /* Non-static member that is reference. */
            {
                struct C {
                    int &i;
                };
                static_assert(!std::is_standard_layout<C>());
                static_assert(!std::is_pod<C>());
            }

            /* Neither:
             *
             * - has no base classes with non-static data members, or
             * - has no non-static data members in the most derived class
             *   and at most one base class with non-static data members
             */
            {
                /* Non POD because has two base classes with non-static data members. */
                {
                    struct Base1 {
                        int i;
                    };
                    struct Base2 {
                        int j;
                    };
                    struct C : Base1, Base2 {};
                    static_assert(!std::is_standard_layout<C>());
                    static_assert(!std::is_pod<C>());
                }

                /* POD: has just one base class with non-static member. */
                {
                    struct Base1 {
                        int i;
                    };
                    struct C : Base1 {};
                    static_assert(std::is_standard_layout<C>());
                    static_assert(std::is_pod<C>());
                }
            }

            /* Base classes of the same type as the first non-static data member.
             * TODO failing on GCC 8.1 -std=c++11, 14 and 17.
             */
            {
                struct C {};
                struct D : C {
                    C c;
                };
                //static_assert(!std::is_standard_layout<C>());
                //static_assert(!std::is_pod<C>());
            };

            /* C++14 standard layout new rules, yay! */
            {
                /* Has two (possibly indirect) base class subobjects of the same type.
                 * Here C has two base classes which are indirectly "Base".
                 *
                 * TODO failing on GCC 8.1 -std=c++11, 14 and 17.
                 * even though the example was copy pasted from cppreference.
                 */
                {
                    struct Q {};
                    struct S : Q { };
                    struct T : Q { };
                    struct U : S, T { };  // not a standard-layout class: two base class subobjects of type Q
                    //static_assert(!std::is_standard_layout<U>());
                    //static_assert(!std::is_pod<U>());
                }

                /* Has all non-static data members and bit-fields declared in the same class
                 * (either all in the derived or all in some base).
                 */
                {
                    struct Base { int i; };
                    struct Middle : Base {};
                    struct C : Middle { int j; };
                    static_assert(!std::is_standard_layout<C>());
                    static_assert(!std::is_pod<C>());
                }

                /* None of the base class subobjects has the same type as
                 * for non-union types, as the first non-static data member
                 *
                 * TODO: similar to the C++11 for which we could not make a proper example,
                 * but with recursivity added.
                 */

                /* TODO come up with an example that is POD in C++14 but not in C++11. */
            }
        }
    }

    /* POD examples. Everything that does not fall in the non-POD examples. */
    {
        /* Can't get more POD than this. */
        {
            struct C {};
            static_assert(std::is_pod<C>());
        }

        /* Private member: became POD in C++11
         * https://stackoverflow.com/questions/4762788/can-a-class-with-all-private-members-be-a-pod-class/4762944#4762944
         */
        {
            struct C {
                private:
                    int i;
            };
#if __cplusplus >= 201103L
            static_assert(std::is_pod<C>());
#else
            static_assert(!std::is_pod<C>());
#endif
        }

        /* Derived.
         * https://stackoverflow.com/questions/4762788/can-a-class-with-all-private-members-be-a-pod-class/4762944#4762944
         */
        {
            struct C {};
            struct D : C {};
            static_assert(std::is_pod<D>());
        }
    }
#endif
}
