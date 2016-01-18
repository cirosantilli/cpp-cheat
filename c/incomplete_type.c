/*
# Incomplete types

    There are three classes of types:

    - object: variables, arrays
    - functions
    - incomplete

    Incomplete types are types which only have a declaration but no definition.
*/

#include "common.h"

int main() {

    /*
    TODO what are all possible types of incomplete types?
    */
    {
        /* Declared structs and enums without definition. */
        struct S;
        /* ERROR */
        /*struct S s;*/

        /*
        TODO: are undefined enums incomplete? How to test this?
        Cannot test like this, because ISO forbids forward declare of enums.
        GCC however does allow it without -pedantic.
        */
        /*enum E;*/
        /*enum E e;*/

        /* Arrays without size. */
        extern int is[];
        /* ERROR */
        /*sizeof(int []);*/

        /* void: C99 6.2.5 Types */
        /* ERROR with -pedantic. But GCC allows it otherwise? */
        /*sizeof(void);*/
    }

    /* # Consequences of incomplete types */
    {
        /*
        Variables of that type cannot be created:
        the compiler wouldn't know how much space to allocate.
        */
        {
            struct S;
            /* ERROR */
            /*struct S s;*/

            /* Pointers to incomplete types however OK: all pointers have the same size. */
            {
                struct S;
                struct S *sp;
            }
        }

        /* sizeof cannot be used. */
        {
            struct S;
            /* ERROR */
            /*sizeof(struct S);*/
        }

        /* Cannot be used to define other types like structs */
        {
            struct S;
            /* ERROR */
            /*struct T {struct S s;};*/
        }
    }

    /*
    # struct that contains itself

    # Incomplete type cycles
    */
    {
        /*
        ERROR: s has incomplete type inside the definition of S:
        it only becomes complete after the definition is over.

        That would create an infinite loop:

        -   each S contains one S. and one i.

        -   therefore the size of each S must be 2 ints:

            size of S + size of int =
                    1 +           1 =
                                    2

        -   but then the size of S must be 3 ints:

                size of S + size of int =
                        2 +           1 =
                                        3

        -   and so on

        The solution is to store opaque pointers instead of the actual structs.
        */
        {
            /*
            struct S {
                struct S s;
                int i;
            };
            */
        }

        /* ERROR: struct s1 undefined */
        {
            /*
            struct S0 { struct S1 s1; };
            struct S1 { struct S0 s0; };
            */
        }

        /* ERROR: s1 has incomplete type */
        {
            /*
            struct S1;
            struct S0 { struct S1 s1; };
            struct S1 { struct S0 s0; };
            */
        }
    }

    /*
    # Opaque pointers

        You can have pointers to incomplete types.

        Forward declaration of S1 makes it makes it alright.

        Such pointers are called opaque pointers.
        http://stackoverflow.com/questions/3854113/what-is-an-opaque-value

        A common usage pattern is:

        - declare the opaque type in the .h file
        - declare functions that use the opaque pointer in the .h file
        - defined the type and the functions in the .c file

        Now clients can only pass around pointers,
        and use the type through the functions you give them,
        but not access the fields they choose.

        This is a way to implement private member variables in C.

        `FILE` is widely used as an example of an opaque pointer, but it is not strictly opaque:
        ANSI does not say that you cannot instantiate it, and popular implementations
        have allowed that: ANSI only says nothing about it's fields,
        so using them makes your code non-standard. TODO confirm.
    */
    {
        {
            struct S1;
            /* storage size of s isn't known . */
            /*struct S1 s1;*/
            struct S1* s1;
        }

        {
            struct S1;
            struct S0 { struct S1* s1; };
            struct S1 { struct S0* s0; };
        }

        /*
        The type itself has already been defined inside the struct definition,
        so the following is fine.
        */
        {
            struct S { struct S* s; };
        }
    }

    return EXIT_SUCCESS;
}
