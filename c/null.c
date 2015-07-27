/*
# null pointer constant

    Good source: http://c-faq.com/null/macro.html

    Basic usage: indicate error as return value from function

    C99 7.17/3 Common definitions `<stddef.h>` says:

    # NULL

        > NULL: macro which expands to an implementation-defined null pointer constant;

        Then form the definition of "null pointer constant", it is either of:

        - `0`
        - `(void*)0`

        Thus in x86-64, is it possible to differentiate them by size:
        `0` is 4 bytes, while `(void*)` is 8.

        C++:

        -   ensures that NULL is an "rvalue of integer type that evaluates to zero" (`0`):
            it cannot be a pointer.

        -   introduces the related `nullptr`, which is guaranteed to be a pointer type.

            This is specially important because of function overload.

    # Null pointer constant

    # Null pointer

        Null pointer constant and null pointer are note the same thing!!!

        6.3.2/3 Pointers:

        > An integer constant expression with the value 0, or such an expression cast to type
        void *, is called a null pointer constant.55) If a null pointer constant is converted to a
        pointer type, the resulting pointer, called a null pointer, is guaranteed to compare unequal
        to a pointer to any object or function.

        6.3.2/4 Pointers:

        > Conversion of a null pointer to another pointer type yields a null pointer of that type.
        Any two null pointers shall compare equal.

        Therefore there are multiple `null` pointer types: `(void *)0`, `(int *)0`, etc.

    # argc[argv]

        Null pointer

        5.1.2.2.1/2 Program startup:

        > argv[argc] shall be a null pointer.
*/

#include "common.h"

int *ip;

int main() {
    /*
    It never points to any possible valid memory location:
    global, local variable, malloc return, ...

    In other words, taking `&` of a variable never gives it.
    */
    {
        int i = 0;
        /* WARN GCC 4.7 warning: &i will never be null. Smart. */
        /*assert(&i != NULL);*/
    }

    /*
    How it prints like: implementation defined.

    C99 7.19.6.1/8 The fprintf function:

    > `p`: The argument shall be a pointer to void. The value of the pointer is
    converted to a sequence of printing characters, in an implementation-defined
    manner.
    */
    {
        printf("printf NULL %%p = %p\n", NULL);
    }

    /*
    # == for null pointers

        Treated specially at 6.5.9/5 Equality operators:

        > If one operand is a pointer and the other is a
        null pointer constant, the null pointer constant is converted to the type of the pointer. 

        And 6.5.9/6:

        > Two pointers compare equal if and only if both are null pointers, [...]
    */
    {
        /*
        True, since both are null pointers.

        TODO error or warning? WARN GCC 4.8: comparison of distinct pointers without cast.
        */
        {
            /*assert((char *)0 == (int *)0);*/
        }

        /*
        True: one is a pointer, and the other is a null pointer constant.
        */
        {
            assert((char *)0 == NULL);

            /* Above is converted to: */
            assert((char *)0 == (char *)NULL);

            /* True because `0` is a null pointer constant: */
            assert((char *)0 == 0);

            /*
            True because NULL is either:

            - `0`
            - `(void *)0`, which is a null pointer constant
            */
            assert(NULL == 0);
        }

        /*
        As a consequence, if(p) can be used directly on null checks,
        as it is equivalent to:

            if (p != 0)
        */
        {
            if (NULL)
                assert(false);
        }
    }

    /* WARN: comparison of distinct pointer types requires a cast: */
    {
        /*assert((int*)0 == (char*)0);*/
    }

    /*
    Never dereference the NULL pointer since it is guaranteed to point to nothing.

    TODO Undefined behaviour? On Linux leads to a Segmentation fault.
    */
    {
        /*volatile int i = *(int*)NULL;*/
    }

    return EXIT_SUCCESS;
}
