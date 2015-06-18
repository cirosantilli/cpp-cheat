/*
# inheriting constructor

    Reuse base class constructors:
    http://stackoverflow.com/questions/8093882/using-c-base-class-constructors

    Before C++11, is was necessary to call each constructor explicitly and forward the argments.
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    class Base {
        public:
            int i;
            Base() : i(1) {}
            Base(int i) : i(i) {}
    };

    class Derived : public Base {
        public:
            using Base::Base;
    };

    class DerivedNoUsing : public Base {};

    {
        // ERROR: no matching function.
        //DerivedNoUsing o0(2);
        //assert(o0.i == 2);

        // int is forwarded because of the `using`.
        Derived o0(2);
        assert(o0.i == 2);
    }

    // Default and copy constructors are forwarded without `using`.
    {
        DerivedNoUsing o0;
        assert(o0.i == 1);

        DerivedNoUsing o1(o0);
        assert(o1.i == 1);
    }
#endif
}
