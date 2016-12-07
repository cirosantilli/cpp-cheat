/*
# Virtual inheritance

# Virtual base class

# Dreaded diamond

    Solves the dreaded diamond problem:

          D
         / \
        B   C
         \ /
          A

    The problem is that D would have two instances of A data.

    With virtual inheritance, you say: don't make a copy of the data of this base class.

    Has nothing to do with the `virtual` keyword for methods:
    everything is done at compile time in this usage.

    - http://stackoverflow.com/questions/21558/in-c-what-is-a-virtual-base-class
    - http://stackoverflow.com/questions/254673/multiple-inheritance-from-two-derived-classes
*/

//#include "common.hpp"
#include <cassert>

class A {
    public:
        A(){ A::aDefault++; }
        A(int i) : i(i) {}
        int i;
        virtual int f() = 0;
        virtual int g() = 0;
        virtual int h() = 0;
        static int aDefault;
};
int A::aDefault = 0;
class B : public virtual A {
    public:
        B(int j) : j(j) {}
        int j;
        virtual int f() { return this->i + this->j; }
};
class C : public virtual A {
    public:
        C(int k) : k(k) {}
        int k;
        virtual int g() { return this->i + this->k; }
};
class D : public B, public C {
    public:
        D(int i, int j, int k) : A(i), B(j), C(k) {}
        virtual int h() { return this->i + this->j + this->k; }
};

int main() {
    D d = D(1, 2, 4);
    // TODO: if the default constructor is never called, why is it required by B and C?
    // http://stackoverflow.com/questions/9907722/why-is-default-constructor-called-in-virtual-inheritance
    assert(A::aDefault == 0);
    assert(d.f() == 3);
    assert(d.g() == 5);
    assert(d.h() == 7);
}
