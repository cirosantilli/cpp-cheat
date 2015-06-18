/*
# Pure virtual

    Virtual function without implementation. Syntax:

        virtual f() = 0

    Makes it impossible instantiate the class.

    It is only possible to instantiate derived classes that override it.

    If a class has a pure virtual method is called as an *abstract class* or *interface*.

    In Java there is a language difference between those two terms,
    and it might be a good idea to differentiate them when speaking about C++:

    - interface: no data
    - abstract: data
*/

#include "common.hpp"

int main() {
    // Basic example.
    {
        // This is an abstract type because it has a pure virtual method.
        class Base {
            public:
                virtual int f() = 0;
        };

        class Derived : public Base {
            public:
                virtual int f() { return 1; }
        };

        // ERROR: abstract type.
        //Base b;

        Derived d;
        assert(d.f() == 1);

        // We can still have abstract pointers and references to abstract classes.
        Base *bp = &d;
        Base &br = d;
        assert(bp->f() == 1);
        assert(br.f() == 1);
    }

    /*
    It is not possible to implement pure virtual methods on another base class
    with multiple-inheritance: they must be implemented on the Derived class.

    In some languages where this is possible, this pattern is called a mixin:
    http://stackoverflow.com/a/20022860/895245
    */
    {
        class Base {
            public:
                virtual int f() = 0;
        };

        class Implementor {
            public:
                virtual int f() {
                    return 1;
                }
        };

        class Derived : public Base, public Implementor {};

        // ERROR: abstract.
        //Derived d;
    }
}
