// # POD
//
// Plain old data:
//
// - https://stackoverflow.com/questions/146452/what-are-pod-types-in-c/52989731#52989731
// - http://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special
// - https://en.cppreference.com/w/cpp/named_req/PODType
// - https://github.com/gcc-mirror/gcc/blob/gcc-8_2_0-release/libstdc%2B%2B-v3/testsuite/20_util/is_pod/value.cc a few tests, but nothing awesome
//
// POD restrictions have become more and more relaxed as the standard evolved.
//
// std::is_pod was added in C++11, so let's only consider that standard onwards for now.

#include <type_traits>
#include <array>
#include <vector>

int main() {
#if __cplusplus >= 201103L
    // # Not POD
    //
    // Non-POD examples. Let's just walk all non-recursive non-POD branches of cppreference.
    {
        // Non-trivial implies non-POD.
        // https://en.cppreference.com/w/cpp/named_req/TrivialType
        {
            // Has one or more default constructors, all of which are either
            // trivial or deleted, and at least one of which is not deleted.
            {
                // Not trivial because we removed the default constructor
                // by using our own custom non-default constructor.
                {
                    struct C {
                        C(int) {}
                    };
                    static_assert(std::is_trivially_copyable<C>(), "");
                    static_assert(!std::is_trivial<C>(), "");
                    static_assert(!std::is_pod<C>(), "");
                }

                // No, this is not a default trivial constructor either:
                // https://en.cppreference.com/w/cpp/language/default_constructor
                //
                // The constructor is not user-provided (i.e., is implicitly-defined or
                // defaulted on its first declaration)
                {
                    struct C {
                        C() {}
                    };
                    static_assert(std::is_trivially_copyable<C>(), "");
                    static_assert(!std::is_trivial<C>(), "");
                    static_assert(!std::is_pod<C>(), "");
                }
            }

            // Not trivial because not trivially copyable.
            {
                struct C {
                    C(C&) {}
                };
                static_assert(!std::is_trivially_copyable<C>(), "");
                static_assert(!std::is_trivial<C>(), "");
                static_assert(!std::is_pod<C>(), "");
            }
        }

        // Non-standard layout implies non-POD.
        // https://en.cppreference.com/w/cpp/named_req/StandardLayoutType
        {
            // Non static members with different access control.
            {
                // i is public and j is private.
                {
                    struct C {
                        public:
                            int i;
                        private:
                            int j;
                    };
                    static_assert(!std::is_standard_layout<C>(), "");
                    static_assert(!std::is_pod<C>(), "");
                }

                // These have the same access control.
                {
                    struct C {
                        private:
                            int i;
                            int j;
                    };
                    static_assert(std::is_standard_layout<C>(), "");
                    static_assert(std::is_pod<C>(), "");

                    struct D {
                        public:
                            int i;
                            int j;
                    };
                    static_assert(std::is_standard_layout<D>(), "");
                    static_assert(std::is_pod<D>(), "");
                }
            }

            // Virtual function.
            {
                struct C {
                    virtual void f() = 0;
                };
                static_assert(!std::is_standard_layout<C>(), "");
                static_assert(!std::is_pod<C>(), "");
            }

            // Non-static member that is reference.
            {
                struct C {
                    int &i;
                };
                static_assert(!std::is_standard_layout<C>(), "");
                static_assert(!std::is_pod<C>(), "");
            }

            // Neither:
            //
            // - has no base classes with non-static data members, or
            // - has no non-static data members in the most derived class
            //   and at most one base class with non-static data members
            {
                // Non POD because has two base classes with non-static data members.
                {
                    struct Base1 {
                        int i;
                    };
                    struct Base2 {
                        int j;
                    };
                    struct C : Base1, Base2 {};
                    static_assert(!std::is_standard_layout<C>(), "");
                    static_assert(!std::is_pod<C>(), "");
                }

                // POD: has just one base class with non-static member.
                {
                    struct Base1 {
                        int i;
                    };
                    struct C : Base1 {};
                    static_assert(std::is_standard_layout<C>(), "");
                    static_assert(std::is_pod<C>(), "");
                }

                // Just one base class with non-static member: Base1, Base2 has none.
                {
                    struct Base1 {
                        int i;
                    };
                    struct Base2 {};
                    struct C : Base1, Base2 {};
                    static_assert(std::is_standard_layout<C>(), "");
                    static_assert(std::is_pod<C>(), "");
                }
            }

            // Base classes of the same type as the first non-static data member.
            // TODO failing on GCC 8.1 -std=c++11, 14 and 17.
            {
                struct C {};
                struct D : C {
                    C c;
                };
                //static_assert(!std::is_standard_layout<C>(), "");
                //static_assert(!std::is_pod<C>(), "");
            };

            // C++14 standard layout new rules, yay!
            {
                // Has two (possibly indirect) base class subobjects of the same type.
                // Here C has two base classes which are indirectly "Base".
                //
                // TODO failing on GCC 8.1 -std=c++11, 14 and 17.
                // even though the example was copy pasted from cppreference.
                {
                    struct Q {};
                    struct S : Q { };
                    struct T : Q { };
                    struct U : S, T { };  // not a standard-layout class: two base class subobjects of type Q
                    //static_assert(!std::is_standard_layout<U>(), "");
                    //static_assert(!std::is_pod<U>(), "");
                }

                // Has all non-static data members and bit-fields declared in the same class
                // (either all in the derived or all in some base).
                {
                    struct Base { int i; };
                    struct Middle : Base {};
                    struct C : Middle { int j; };
                    static_assert(!std::is_standard_layout<C>(), "");
                    static_assert(!std::is_pod<C>(), "");
                }

                // None of the base class subobjects has the same type as
                // for non-union types, as the first non-static data member
                //
                // TODO: similar to the C++11 for which we could not make a proper example,
                // but with recursivity added.

                // TODO come up with an example that is POD in C++14 but not in C++11.
            }
        }
    }

    // # POD
    //
    // POD examples. Everything that does not fall neatly in the non-POD examples.
    {
        // Can't get more POD than this.
        {
            struct C {};
            static_assert(std::is_pod<C>(), "");
            static_assert(std::is_pod<int>(), "");
        }

        // Array of POD is POD.
        {
            struct C {};
            static_assert(std::is_pod<C>(), "");
            static_assert(std::is_pod<C[]>(), "");
        }

        // Private member: became POD in C++11
        // https://stackoverflow.com/questions/4762788/can-a-class-with-all-private-members-be-a-pod-class/4762944#4762944
        {
            struct C {
                private:
                    int i;
            };
#if __cplusplus >= 201103L
            static_assert(std::is_pod<C>(), "");
#else
            static_assert(!std::is_pod<C>(), "");
#endif
        }

        // Most standard library containers are not POD because they are not trivial,
        // which can be seen directly from their interface definition in the standard.
        // https://stackoverflow.com/questions/27165436/pod-implications-for-a-struct-which-holds-an-standard-library-container
        {
            static_assert(!std::is_pod<std::vector<int>>(), "");
            static_assert(!std::is_trivially_copyable<std::vector<int>>(), "");
            // Some might be though:
            // https://stackoverflow.com/questions/3674247/is-stdarrayt-s-guaranteed-to-be-pod-if-t-is-pod
            static_assert(std::is_pod<std::array<int, 1>>(), "");
        }
    }

    // # POD effects
    //
    // Now let's verify what effects does PODness have.
    //
    // Note that this is not easy to do automatically, since many of the
    // failures are undefined behaviour.
    //
    // A good initial list can be found at:
    // https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special/4178176#4178176
    {
        struct Pod {
            uint32_t i;
            uint64_t j;
        };
        static_assert(std::is_pod<Pod>(), "");

        struct NotPod {
            NotPod(uint32_t i, uint64_t j) : i(i), j(j) {}
            uint32_t i;
            uint64_t j;
        };
        static_assert(!std::is_pod<NotPod>(), "");

        // default initialization is affected by PODness: https://en.cppreference.com/w/cpp/language/default_initialization
        // TODO example
        {
        }

        // __attribute__((packed)) only works for POD, and is ignored for non-POD, and emits a warning
        // https://stackoverflow.com/questions/35152877/ignoring-packed-attribute-because-of-unpacked-non-pod-field/52986680#52986680
        {
            struct C {
                int i;
            };

            struct D : C {
                int j;
            };

            struct E {
                D d;
            } /*__attribute__((packed))*/;

            static_assert(std::is_pod<C>(), "");
            static_assert(!std::is_pod<D>(), "");
            static_assert(!std::is_pod<E>(), "");
        }
    }
#endif
}
