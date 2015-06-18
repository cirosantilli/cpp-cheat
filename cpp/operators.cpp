/*
# Assign operator
*/

#include "common.hpp"

int main() {

    /*
    Unlike in C, some C++ operators return lvalues.

    - http://www.quora.com/Why-does-the-pre-increment-operator-in-C++-gives-lvalue-instead-of-rvalue-as-in-C
    */
    {
        // =
        {
            int i = 0, j = 1, k = 2;
            (i = j) = k;
            assert(i == 2);
            assert(j == 1);
            assert(k == 2);
        }

        // Prefix ++
        {
            int i = 0;
            assert(++++i == 2);
            assert(i == 2);

            // ERROR: but not postfix.
            //i++++;
        }

        // ERROR: as in C, most other operators do not return lvalues
        //(i + j) = k;
    }
}
