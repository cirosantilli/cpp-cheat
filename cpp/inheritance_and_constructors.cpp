/*
# Inheritance and constructors.
*/

#include "common.hpp"

int main() {
    /*
    If no base constructor is called on the initialization list,
    the default constructor is called for the base, before the derived.
    */
    {
        class Base {
            public:
                Base() {
                    callStack.push_back("Base()");
                }
        };

        class Derived : public Base {
            public:
                Derived() {
                    callStack.push_back("Derived()");
                }
        };

        Derived d;
        assert(callStack.back() == "Derived()");
        callStack.pop_back();
        assert(callStack.back() == "Base()");
        callStack.pop_back();
    }

    /*
    If the base does not have a default constructor,
    you *must* use the initializer list, or it won't compile.
    */
    {
        class Base {
            public:
                int i;
                Base(int i) : i(i) {}
        };

        class Derived : public Base {
            public:
                /* Base(1) is mandatory here! */
                Derived() : Base(1) {}
        };

        Derived d;
        assert(d.i == 1);
    }

    /* Can only call one constructor of each base class. */
    {
        class Base {
            public:
                Base() {}
                Base(int i) {}
        };

        class Derived : public Base {
            public:
                Derived() : Base() /*, Base(1) */ {
                    callStack.push_back("Derived()");
                }
        };
    }
}
