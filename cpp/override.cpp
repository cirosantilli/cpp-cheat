// https://stackoverflow.com/questions/13880205/is-the-override-keyword-just-a-check-for-a-overridden-virtual-method/54535784#54535784
// https://stackoverflow.com/questions/29145476/requiring-virtual-function-overrides-to-use-override-keyword

#include "common.hpp"

struct Base {
    virtual void f() = 0;
    virtual void g() = 0;
    virtual void h(int) = 0;
    void i() {}
};

struct Derived : Base {
    void f() override;
    void g() override {};

    void h(int) {};
#if 1
    void h(float) {};
#else
    // g++6.4.0: error: ‘void Derived::h(float)’ marked ‘override’, but does not override
    void h(float) override {};
#endif

#if 1
    void i() {}
#else
    // g++6.4.0: error: ‘void Derived::i()’ marked ‘override’, but does not override
    void i() override {}
#endif
};

#if 1
void Derived::f() {}
#else
// g++6.4.0: error: virt-specifiers in ‘f’ not allowed outside a class definition
void Derived::f() override {}
#endif

int main() {
    Derived derived;

    // Yup, it is a valid identifier in normal contexts.
    int override = 1;
}
