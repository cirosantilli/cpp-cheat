/*
# Most vexing parse

    Default constructor vs function declaration syntax gotcha!

    http://stackoverflow.com/questions/180172/default-constructor-with-empty-brackets
*/

#include "common.hpp"

int main() {

    class C {
        public:
            int i;
            C() : i(1) {}
            C(int i) : i(i) {}
    };

    /*
    BAD

    Declares *FUNCTION* called `c` that returns `C` inside function main.

    This is the same as in C, where it is possible to declare a function from inside another function,
    but not define it.

    Therefore there would be not way for C++ to distinguish between the two,
    and still be backwards compatible with C.
    */
    {
        C c();

        // ERROR: function definition is not possible inside another function.
        //C c() {return C();}

        //c.i;
    }

    // If you want to call a default constructor, use:
    {
        C c;
        assert(c.i == 1);
    }

    /*
    For non-default constructors, things work as expected,
    as this syntax could not possibly be a function declaration.
    */
    {
        C c(2);
        assert(c.i == 2);
    }
}
