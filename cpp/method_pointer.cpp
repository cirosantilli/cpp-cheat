/*
# Method pointer

# .* operator

# ->* operator

    Yes, `.*` and `->*` are actual C++ only operators
    dedicated to calling member method pointers.

    http://stackoverflow.com/questions/1485983/calling-c-class-methods-via-a-function-pointer
*/

#include "common.hpp"

int main() {
    class C {
        public:
            int i;
            C(int i) : i(i) {}
            int m(int j) { return this->i + j; }
    };
    int (C::*p)(int) = &C::m;
    C c(1);
    C *cp = &c;

    // Operator .*
    assert((c.*p)(2) == 3);

    // Operator ->*
    assert((cp->*p)(2) == 3);

    // Bound this: TODO Impossible? Things accept the `this` as the next argument however:
    // http://stackoverflow.com/questions/10673585/start-thread-with-member-function
}
