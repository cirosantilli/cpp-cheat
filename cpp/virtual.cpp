/*
# virtual

    Keyword that enables polymorphism.

    http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods
*/

#include "common.hpp"

int main() {

    /*
    # Polymorphism

        The pointer t the base class can have different effects
        depending on what actual object it points to.

    # Override method

        Method of the derived class with compatible signature to base class
        overrides the base method.

        For incompatible signatures, or base methods that are not virtual,
        _hiding_ happnes, not overhiding.
    */
    {
        class Base {
            public:
                virtual int f() { return 0; }
        };

        class Derived1 : public Base {
            public:
                virtual int f() { return 1; }
        };

        class Derived2 : public Base {
            public:
                virtual int f() { return 2; }
        };

        // Depending on what bp points to, we call different functions.
        // This is polymorphism.

        Base *bp;

        Base b;
        bp = &b;
        assert(bp->f() == 0);

        Derived1 d1;
        bp = &d1;
        assert(bp->f() == 1);

        Derived2 d2;
        bp = &d2;
        assert(bp->f() == 2);
    }

    // Without `virtual`, no polymorphism happens!
    {
        class Base {
            public:
                int f() { return 0; }
        };

        class Derived : public Base {
            public:
                int f() { return 1; }
        };

        Base *bp;

        Base b;
        bp = &b;
        assert(bp->f() == 0);

        Derived d;
        bp = &d;
        // Base method called!
        assert(bp->f() == 0);
    }

    /*
    If the derived signature is not compatible with the virtual,
    no polymorphism happens!

    Also see "covariant return" for compatibility of return types.
    */
    {
        class Base {
            public:
                virtual int f() { return 0; }
        };

        class Derived : public Base {
            public:
                virtual int f(int i) { return i; }
        };

        Base *bp;

        Base b;
        bp = &b;
        assert(bp->f() == 0);

        Derived d;
        bp = &d;
        // Base method called!
        assert(bp->f() == 0);

        // ERROR: no matching function.
        //assert(bp->f(1) == 1);
    }

    /*
    `virtual` on the overriding method is optional, although highly recommended.

    Even if not given, the method is still `virtual`.

    So just always use it.
    */
    {
        class Base {
            public:
                virtual int f() { return 0; }
        };

        class Derived1 : public Base {
            public:
                /* Note no virtual here. */
                int f() { return 1; }
        };

        class Derived2 : public Derived1 {
            public:
                int f() { return 2; }
        };

        // Polymorphism works. So Derived::f is actually `virtual`.
        Derived1 *dp;
        Derived2 d2;
        dp = &d2;
        assert(dp->f() == 2);
    }
}
