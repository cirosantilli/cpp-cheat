/*
# Covariant return

    The return value of an overriding method that returns a pointer
    can return a pointer derived class of the return type of the overriden method.
*/

#include "common.hpp"

int main() {
    class Base {
        public:
            int i;
            Base(int i) : i(i) {}
            virtual Base* f() { return new Base(0); }
            virtual Base* g() { return new Base(0); }
            Base* h() { return new Base(0); }
    };

    class Derived : public Base {
        public:
            Derived(int i) : Base(i) {}

            // THIS is the covariant return.
            // It only works because `Derived` is derived from `Base`.
            virtual Derived* f() { return new Derived(1); }

            /*
            ERROR: conflicting return: int is not derived from `Base`.

            Contrast this to overlading where different returns are possible.

            The difference here is that polymorphism this is decided at runtime,
            so we must know the return beforehand to typecheck things properly.
            */
            //virtual int* g() { return new int(1); }

            // OK: all of this only applies to virtual methods.
            // Non-virtual methods just hide as usual, no overriding.
            int* h() { return new int(2); }
    };

    Base *bp;
    Derived d(-1);
    bp = d.f();

    // Derived class got called: polymorphism.
    assert(bp->i == 1);

    // Base class got called: no polymorphism.
    assert(bp->h()->i == 0);
}
