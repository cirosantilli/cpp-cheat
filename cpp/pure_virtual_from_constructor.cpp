/*
# Pure virtual from constructor

    Calling virtual method from base constructor is not possible
    http://stackoverflow.com/questions/496440/c-virtual-function-from-constructor

 Not possible because derived class has not yet been initialized.

    Workaround? http://www.parashift.com/c%2B%2B-faq-lite/calling-virtuals-from-ctor-idiom.html
*/

#include "common.hpp"

int main() {
    // Basic example.
    {
        class Base {
            public:
                int i;
                int j;
                Base() {
                    this->i = a();
                    // LINKER ERROR: undefined reference to b().
                    //this->j = b();
                }
                virtual int a() { return 0; }
                virtual int b() = 0;
                int c() { return b(); }
        };

        class Derived : public Base {
            public:
                virtual int a() { return 1; }
                virtual int b() { return 2; }
        };

        Derived c;

        // Base::a is called not Derived::a
        // because it is the constructor.
        assert(c.i == 0);

        // Base::b is called because we are not in the constructor.
        assert(c.c() == 2);
    }

    // The simplest solution seems to be to define a separate init function.
    // Downside: requires you to write a new constructor on the derived, and forward all arguments.
    {
        class Base {
            public:
                int i;
                int j;
                Base() {}
                void init() {
                    this->i = a();
                    this->j = b();
                }
                virtual int a() { return 0; }
                virtual int b() = 0;
        };

        class Derived : public Base {
            public:
                Derived() { init(); }
                virtual int a() { return 1; }
                virtual int b() { return 2; }
        };

        Derived c;
        assert(c.i == 1);
        assert(c.j == 2);
    }
}
