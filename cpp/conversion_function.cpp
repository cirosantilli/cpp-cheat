/*
Allows to convert objects to primitives and other objects implicitly
or with the cast operator.
*/

#include "common.hpp"

class C0 {
    public:
        int i;

        C0(int i) : i(i) {}

        operator int() {
            return this->i;
        }
};

class C1 {
    public:
        int i;

        C1(int i) : i(i) {}

        operator C0() {
            return C0(this->i);
        }
};

int main() {
    C1 o(1);

    // ERROR: Only a single cast is possible.
    //{ int i = o; }

    // OK: one explicit, one implicit.
    { int i = (C0)o; }

    // OK: both explicit.
    { int i = (int)(C0)o; }
}
