/*
# rvalue reference

# &&

    http://www.artima.com/cppsource/rvalue.html

    C++11

    New type of reference.

    Old references are referred to as lvalue references,
    since they must be initialized by lvaues.

    Denoted by double ampersand `&&`.

    There is one difference between them and lvalue references:
    rvalue references can only be initialized by both rvalues,
    unlike lvalue references which can only be initialized by lvalues
    (except if they are const).

    Main motivation: implement move semantics.
*/

#include "common.hpp"

#if __cplusplus >= 201103L
/* Pair of function overload based only on if argument is an rvalue or a lvalue. */
std::string overloadRLvalue(int& i) {
    return "lval";
}

std::string overloadRLvalue(int&& i) {
    return "rval";
}

/*
ERROR: ambiguous with both of the above, because in C++:

    int i = lvalue;

Leads to copy construction (ambiguous with the `&` overload).

    int i = rvalue;

Leads to move construction (ambiguous with the `&&` overload).
*/
/*
std::string overloadRLvalue(int i) {
    return "val";
}
*/
#endif

int main() {
#if __cplusplus >= 201103L
    /*
    Cannot be bound to an lvalue on stack.

    This is the *key* property of rvalue references, since it allows function overload
    to differentiate lvalues from rvalues, and thus implement move contructors.
    */
    {
        int i = 0;

        int&& irr = 1;

        // ERROR: i is not rvalue, it is a lvalue!
        //int&& irrBad = i;
    }

    // On all other aspects besides initialization, rvalue references
    // are identical to lvalue references.
    {
        int&& irr = 0;
        assert(irr == 0);

        irr = 1;
        assert(irr == 1);
    }

    // Function overload can distinguish rvalues from lvalues.
    // This is essential for move semantics.
    {
        int i;
        assert(overloadRLvalue(i) == "lval");
        assert(overloadRLvalue(1) == "rval");
    }
#endif
}
