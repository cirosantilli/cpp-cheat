/*
# const_cast

    Change (add/remove) constantness and volatility of objects (property called cv-qualification).

    Does not compile to any extra CPU instructions:
    only changes type information for the compiler.

    TODO when should it be used?

    - http://stackoverflow.com/questions/357600/is-const-cast-safe/357640#357640
    - avoiding repetition between const and non const versions of arguments is an use case:
        - http://stackoverflow.com/questions/123758/how-do-i-remove-code-duplication-between-similar-const-and-non-const-member-func
        - http://stackoverflow.com/questions/5324256/is-const-castconst-type-ever-useful/5326238#comment69750469_5326238
*/

#include "common.hpp"

int main() {
    // Remove const.
    {
        // UB if data is const.
        {
            const int i = 0;
            const int *ip = &i;

            // ERROR.
            //*ip = 1;

            // UB
            // http://stackoverflow.com/questions/19208560/can-we-use-const-cast-to-modify-a-constant-variable
            //*(const_cast<int*>(ip)) = 1;
        }

        // Fine otherwise.
        {
            int i = 0;
            const int *ip = &i;

            // ERROR.
            //*ip = 1;

            // OK.
            *(const_cast<int*>(ip)) = 1;
            assert(i == 1);
        }
    }

    // Only works for references or pointers.
    {
        int i;
        // ERROR
        //const_cast<const int>(i);
        const_cast<const int&>(i);
        const_cast<const int*>(&i);
    }

    // ERROR: Returns rvalues. Therefore cannot initialize non-const references.
    {
        int i = 0;
        int *ip;
        //const int*& ipa = const_cast<const int*>(ip);
        //ipa is a non const reference.
        //int *const& would be a const reference.
    }

    // Only has effect for a single statement.
    {
        int i = 0;
        const int *ip = &i;
        const_cast<int*>(ip);
        // ERROR.
        //*ip = 1;
    }
}
