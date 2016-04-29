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

    /*
    Cannot initialize anything else when a delegation is used:
    http://stackoverflow.com/questions/12190051/member-initialization-while-using-delegated-constructor
    */
    {
        class C {
            public:
                int i;
                int j;
                C() : i(i) {}
                //C(int i) : C(), i(i) {}
        };
        C c;
        assert(c.i == 1);
    }

    /*
    Works with inheritance.
    TODO: Is this still called a "delegated constructor"?
    */
    {
        class B {
            public:
                int i;
                B() : i(1) {}
        };
        class C : public B {
            public:
                int j;
                C() : B(), j(2) {}
        };
        C c;
        assert(c.i == 1);
        assert(c.j == 2);
    }
#endif
}
