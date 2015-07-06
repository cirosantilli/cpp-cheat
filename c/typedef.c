/*
# typedef

    Create new types based on old ones

    On libc, the convention append `_t` to typedefs is used
    ex: `size_t`, `wchar_t`, etc.

    Some of those macros are defined to be strcitly integer types (like size_t)
    while others can be either integer or floating points according to the implementation.

    To print integer typedefs such with `printf`, see `printf`.
*/

#include "common.h"

int main() {
    {
        typedef int Newint;
        Newint i = 1;
        assert(sizeof(Newint) == sizeof(int));
    }

    /* ERROR: unlike macros, typedef has scope just like that of variables: */
    {
        /*Newint i = 1;*/
    }

    /*
    typedef position is very flexible.

    Only use the first though if you want to be sane.
    */
    {
        typedef unsigned int uint;

        /* WARN: GCC compiles but warns you about this insanity. */
        /*unsigned typedef int vint;*/
        /*unsigned int typedef wint;*/

        /* ERROR. This is the only one that fails to compile. */
        /*unsigned int xint typedef;*/
    }

    /*
    Repeated typedef:
    http://stackoverflow.com/questions/8594954/repeated-typedefs-invalid-in-c-but-valid-in-c

    Allowed in C++ and C11, forbidden in C99.
    */
    {
#if __STDC_VERSION__ >= 201112L
        typedef int i;
        typedef int i;
        i j = 0;
#endif
    }

    /* Multiple typedefs in one statement. */
    {
        typedef int i, j;
        i k = 0;
        j l = 1;
        k = l;
    }

    /*
    # typdef pointer

        The pointer sticks to the typedef.
    */
    {
        typedef int * ip_t;
        /* Both are pointer types. */
        ip_t ip, jp;
        int i, j;
        ip = &i;
        jp = &j;
    }

    return EXIT_SUCCESS;
}
