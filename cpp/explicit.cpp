/*
# explicit keyword

    Keyword specifies that a given constructor can only be used explicitly.
*/

#include "common.hpp"

class Implicit {
    public:
        int i;
        Implicit(int i) : i(i) {}

        operator int() {
            return this->i;
        }
};

class Implicit2 {
    public:
        int i;
        Implicit2(Implicit i) : i(i) {}
};

class Explicit {
    public:
        int i;

        explicit Explicit(int i) : i(i) {}

        // TODO this makes no sense right, since it is not a ctor that takes a single arg?
        // why does it compile without warning
        explicit Explicit(int i, int j) : i(i + j) {}

        // ERROR: only for constructors and conversion functions since C++11.
        //explicit void method(){}

#if __cplusplus >= 201103L
        explicit operator int() {
            return this->i;
        }

        // Cannot do this test here as the `int i = o` would then use it.
        //operator float() {
            //return (float)this->i;
        //}
#endif
};

int main() {
    // Without implicit, the cast is made with the constructor that takes one argument.
    {
        Implicit o = 1;
        assert(o.i == 1);
    }

    // ERROR: Only a single cast can be made.
    //{ Implicit2 o = 1; }
    {
        Implicit2 o = Implicit(1);
        assert(o.i == 1);
    }

    // ERROR: explicit prevents implicit casts.
    //{ Explicit o = 1; }

    // Explicit casts are still allowed.
    {
        Explicit o = (Explicit)1;
        assert(o.i == 1);
    }

    // Operator
    {
        {
            Explicit o(1);
            // ERROR
            //int i = o;
        }

        {
            Explicit o(1);
            int i = (int)o;
        }

        {
            Implicit o(1);
            int i = o;
            assert(i == 1);
        }
    }
}
