/*
# pointer

    Pointers contain addresses of variables instead of the value.

    Using the dereference operator `*`, you can get the value from the address.
*/

#include "common.h"

typedef struct void_ptr_cb_payload { int i; } void_ptr_cb_payload;

int void_ptr_cb(int i, void* payload) {
    void_ptr_cb_payload* pay = payload;
    return i + pay->i;
}

typedef struct void_ptr_cb_payload2 { int i; int j; } void_ptr_cb_payload2;

int void_ptr_cb2(int i, void* payload) {
    void_ptr_cb_payload2* pay = payload;
    return i + pay->i + pay->j;
}

int void_ptr_caller(int i, int (*cb)(int i, void* payload), void* payload) {
    return i + cb(2, payload);
}

int main() {
    int i;
    int *pi, *pi2;
    /* BAD */
    /* you are modifying some random piece of memory!!!! */
    /* must declare like that: multiple stars */
    /**pi = 7;*/
    pi = &i;
    *pi = 1;
    assert(i == 1);
    assert(*pi == 1);
    i = 2;
    assert(i == 2);
    assert(*pi == 2);

    printf("(void*)pi = %p\n", (void*)pi);
    printf("(void*)(pi+1) = %p\n",(void*)(pi+1));

    /* OK: implicit conversion * -> int: */

        pi2 = pi + 1;
        printf("(void*)(pi2-pi) = %p\n", (void*)(pi2-pi));
        assert(pi2 - pi == 1);

    /* ERROR: incompatible pointer type */

        /*float* fp = &i;*/

    /* OK: works with explicit cast: */

        float* fp = (float*)&i;

    /*
    # single line multiple pointer declaration

        You must put an asterisk for each pointer, or they are not taken to be pointers!

        This is not very intuitive since the asterisk is part of the type, not of the variable.
    */
    {
        /* correct */
        {
            int i, *ip ;
            ip = &i;
        }

        /* ERROR: ip2 is not a pointer, but an int! */
        {
            /*int i;*/
            /*int* ip, ip2;*/
            /*ip = &i;*/
            /*ip2 = &i;*/
        }
    }

    /*
    # NULL pointer

        Good source: <http://c-faq.com/null/macro.html>

        Basic usage: indicate error as return value from function
    */
    {
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

        /* how it prints like: */

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
    }

    /*
    # void pointer

        Cannot be dereferenced without typecast.

        Can be typecast implicily to/from any *data* type.
        Not allowed implicitly in C++.

        For function pointers:

        - C leaves it undefined
        - POSIX 7 allows
        - C++ forbids it, C++11 allows it conditionally
    */
    {
        void* vp;
        int* ip;
        int i = 0;
        typedef struct S { int i; int j; } S;
        S s = {0, 1};

        /*
        There is no corresponding data type.

        Since there is no data, there is no data size.

        This means that `sizeof(void)` is not possible, nor are pointer arithmetic operations.
        */
        {
            /* it is however possible to get the size of a `void*` */

                printf("sizeof (void*) = %zu\n", sizeof(void*));

            /* ERROR: invalid application of sizeof to void type */

                /*vp = vp + 1;*/
        }

        /* int* to void*: */

            vp = (void*)&i;

        /* void* to int*: */

            ip = (int*)vp;

        /* void* to int. GCC 4.8: cast from pointer to int of different size: */
        /* `-Wpointer-to-int-cast */

            /*i = (int)vp;*/

        /*
        Typecast to the bad type.

        Compiles and runs!
        */
        {
            /* ERROR: aggretage value used where integer was expected */
            /* i = (int)s; */

            /* HAHA: you can't stop me now compiler! */
            vp = (void*)&s;
            ip = (int*)vp;
            i = *ip;
            /* Proabably defined because it is the first field. */
            /* Reordering is not possible, but what about padding before first field TODO? */
            /*assert(i == 0);*/
        }

        /*
        # Applications of void*

            If possible, avoid them, since they allow you to bypass type safety.

            Valid use cases:

            -   In libc, it is the return type of `malloc`, since it cannot know what type of pointer to return.
                You should use implicit casts with it only:
                <http://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc>

            -   Extra parameters to callback functions.

                The callback caller cannot know beforehand how many extra parameters. Solution:

                - add a `void *` argument to caller and callback. `payload` is a common argument name.
                - pass a struct pointer to the caller with the extra parameters
                - pass the `void *` argument to the callback on the caller body
                - in the callback body typecast the void* to the struct and use it

                Of course, you can typecast to a different type than passed,
                and if you do so welcome to the magic land of undefined behavior.
        */
        {
            void_ptr_cb_payload payload = {4};
            void_ptr_cb_payload2 payload2 = {4, 8};
            assert(void_ptr_caller(1, void_ptr_cb , &payload ) ==  7);
            assert(void_ptr_caller(1, void_ptr_cb2, &payload2) == 15);
        }
    }

    return EXIT_SUCCESS;
}
