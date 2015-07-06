/*
# Delegating constructor

    Call one constructor from another in a given class.
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    /* Basic example. */
    {
        class C {
            public:
                int i;
                C() : C(1) {}
                C(int i) : i(i) {}
        };
        C c;
        assert(c.i == 1);
    }

    /* Nothing prevents recursion. */
    {
        class C {
            public:
                int i;
                C() : C(1) {}
                C(int i) : C() {}
        };
        /* Segfault because of stack overflow. */
        /*C c;*/
    }

    /* Cannot call multiple constructors of the same class. */
    {
        class C {
            public:
                int i;
                float f;
                /* ERROR. */
                /*C() : C(1), C(1.5) {}*/
                C(int i) : i(i) {}
                C(float f) : f(f) {}
        };
    }
#endif
}
