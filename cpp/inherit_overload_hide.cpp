/*
# Inherit overload hide

    Inheritance hides base class methods with the same name even if they have different arguments.

    Use `using` to prevent that.

    - http://stackoverflow.com/questions/1896830/why-should-i-use-the-using-keyword-to-access-my-base-class-method
    - http://stackoverflow.com/questions/4837399/c-rationale-behind-hiding-rule
*/

#include "common.hpp"

int main() {
    class Base {
        public:
            int overload(){ return 1; }
            int no_overload(){ return 2; }
            int no_base(){ return 3; }
    };

    class Derived : public Base {
        public:
            using Base::overload;

            int overload(int i) {
                return i + 1;
            }

            int no_base(int i){ return i + 2; }
    };

    Derived c;

    // ERROR: no matching function.
    //assert(c.no_base() == 3);
    assert(c.no_base(1) == 3);

    // Visible because of the using.
    assert(c.overload() == 1);
    assert(c.overload(1) == 2);

    assert(c.no_overload() == 2);
}
