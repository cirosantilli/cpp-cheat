/*
# Nested functions

        Function defined inside another function (the outter function here is `main`)

        This is not a redefinition because it is inside a parenthesis block
        much like a variable definition inside a parenthesis block.

        In C++, you can use nested classes with static methods, or C++11 lambdas:
        http://stackoverflow.com/questions/4324763/c-can-we-have-functions-inside-functions
*/

#include "common.h"

int nested() { return 0; }


int main() {
    assert(nested() == 0);
    int nested() { return 1; }
    {
        assert(nested() == 1);
        int nested() { return 2; }

        /* ERROR: redefinition */
        /*int nested() { return 2; }*/

        /* Like variable redefinitions, the nested version overrides all external version */
        /* which have become completelly innacessible. */
        assert(nested() == 2);
    }
    assert(nested() == 1);
    return EXIT_SUCCESS;
}
