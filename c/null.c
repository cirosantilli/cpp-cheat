/*
# NULL

    Good source: <http://c-faq.com/null/macro.html>

    Basic usage: indicate error as return value from function
*/

#include "common.h"

int main() {
    /*
    Why it works: it never points to any possible valid memory location.
    (`&` operator never gives anything equal to it).
    this is so guaranteed that gcc emmits a warning in the following code
    */
    {
        int i = 0;
        /* WARN GCC 4.7 warning: &i will never be null. Smart. */
        /*assert(&i != NULL);*/
    }

    /* How it prints like: */
    printf("NULL = %p\n", NULL);

    /* `if(NULL)` and `if(!NULL)` in error checking code always work as expected */
    assert(!NULL);

    /*
    # NULL macro vs 0

        Relationship to 0: typecasting `(int)0` to any pointer type as
        `(int*)0`, `(char*)0` always gives NULL.

        This is a valid way of representing the NULL pointer,
        but it is better style to always use the `NULL` macro

        The exact definition of `NULL` is implementation dependant.
        A very common implementation is as `(void*)0`.

        C++11 also introduces the related `nullptr`.
    */
    {
        assert(NULL == (int*)0);
        assert(NULL == (char*)0);
        printf("sizeof(NULL) = %zu\n", sizeof(NULL));
    }

    /* ERROR: comparison of distinct pointer types requires a cast: */
    {
        /*assert((int*)0 == (char*)0);*/
    }

    /*
    Never dereference the NULL pointer since it is guaranteed to point to nothing.

    TODO to ANSI C, undefined behaviour? or guaranteed error?

    May lead to a Segmentation fault.
    */
    {
        /*volatile int i = *(int*)NULL;*/
    }

    return EXIT_SUCCESS;
}
