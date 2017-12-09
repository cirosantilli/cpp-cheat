/*
Allows to convert objects to primitives and other objects.

http://en.cppreference.com/w/cpp/language/cast_operator
*/

#include "common.hpp"

class ToInt {
    public:
        int i;
        ToInt(int i) : i(i) {}
        operator int() {
            return this->i;
        }
};

class ToToInt {
    public:
        int i;
        ToToInt(int i) : i(i) {}
        operator ToInt() {
            return ToInt(this->i);
        }
};

int main() {
    // Explicit cast.
    assert((int)ToInt(0) == 0);

    // Implicit conversion.
    assert(ToInt(0) == 0);

    // ERROR: Only a single implicit cast is possible at a time.
    //assert(ToToInt(0) == 0);

    // OK, on implicit cast.
    assert((ToInt)ToToInt(0) == 0);

    // OK, all explicit.
    assert((int)(ToInt)ToToInt(0) == 0);
}
