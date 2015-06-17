/*
# Attributes

    C++11 introduces a generalized attribute syntax.

    Similar syntaxes have been rmplemented as extensions for a long time in GCC via `__attribtes__`
    and in Microsoft with `#pragma`. Now some have been standardized!

    Intended only for functions which don't change behaviour: only to help
    compilers optimize or geneate better error messages.

    http://www.stroustrup.com/C++11FAQ.html#attributes

    Attributes can be defined for various objects, and there are 2 standard ones:
    `noreturn` and `carries_dependency`

    C11 also has some attributes like `_Noreturn`, but no generalized syntax.
*/

#include "common.hpp"

#if __cplusplus >= 201103L
void noreturn_func [[ noreturn ]] () { throw 1; }
#endif

int main() {
#if __cplusplus >= 201103L
    try {
        noreturn_func();
    } catch (int i) {}
#endif
}
