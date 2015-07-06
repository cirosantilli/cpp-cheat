/*
# Struct operators
*/

#include "common.h"

int main() {
    /*
    # Assign structs

    # = for struct

        Assigns fields one by one.
    */
    {
        struct S { int i; float f; };
        struct S s  = { 1, 1.0 };
        struct S s2 = { 2, 2.0 };
        s = s2;
        assert(s.i == 2);
        assert(s.f == 2.0);
    }

    /*
    Assignment to an initializer only works for initialization.

    We use a C99 compound literal to achieve the same effect however.
    */
    {
        struct S { int i; };
        struct S s;
        /*s = { 1 };*/
        /*s = { .i = 1 };*/
    }

    /*
    # == for struct

    # Compare structs

        Does not exist.

        There have been failed proposals.

        http://stackoverflow.com/questions/141720/how-do-you-compare-structs-for-equality-in-c
    */
    {
        struct S { int i; };
        struct S s  = { 1 };
        struct S s2 = { 1 };
        /*assert(s == s2);*/

        /*
        # memcmp structs

            May not work because the padding is undefined, unless you memset it beforehand.
        */
    }

    /*
    Inequalities do not exist either: `<` `>` `<=` `>=`

    Here there is a stronger rationale than for `==`:
    if `s.a < s2.a` and `s.b > s2.b`, what does `s < s2` eval to?
    I.e.: what is the precedence of fields?
    */

    /*
    # sizeof for struct

    # struct size

        The way data is packed in a struct is not specified in the standard

        Common compiler strategy: align data to 32 bits
        which makes access faster, using slightly more memory.
    */
    {
        struct S {
            char c;
            int i;
        };

        /* Likely to be 8 on a 2013 32 bit machine. */
        printf("struct sizeof = %zu\n", sizeof(struct S));

        assert(sizeof(char) + sizeof(float) <= sizeof(struct S));
    }

    return EXIT_SUCCESS;
}
