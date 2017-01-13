#include "common.hpp"

class B {
    public:
        int i;
        int iAmbiguous;
        int f() {
            return 0;
        }
        int fAmbiguous() {
            return 0;
        }
};

class B2 {
    public:
        int iAmbiguous;
        int fAmbiguous() {
            return 1;
        }
};


class C : public B, public B2 {
    public:
        int i;
        int f() {
            return 2;
        }
};

int main() {
    C c;
    C *cp = &c;

    // Refer to members of base vs derived class with same name.
    c.i = 0;
    c.C::i = 0;
    cp->C::i = 0;
    c.B::i = 1;
    assert(c.i      == 0);
    assert(c.C::i   == 0);
    assert(cp->C::i == 0);
    assert(c.B::i   == 1);
    assert(cp->B::i == 1);

    // ERROR: ambiguous because on multiple base classes.
    //c.iAmbiguous = 0;
    c.B::iAmbiguous = 0;

    // Analogous for methods.
    callStack.clear();
    assert(c.f() == 2);
    assert(c.B::f() == 0);

    // ERROR ambiguous.
    //c.fAmbiguous();
    assert(c.B::fAmbiguous() == 0);
    assert(c.B2::fAmbiguous() == 1);
}
