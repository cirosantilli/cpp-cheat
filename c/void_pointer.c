/*
# void pointer

# void *

    Cannot be dereferenced without typecast.

    Can be typecast implicily to/from any *data* type.
    Not allowed implicitly in C++.

    For function pointers casts:

    - C leaves it undefined
    - POSIX 7 allows
    - C++ forbids it, C++11 allows it conditionally
*/

#include "common.h"

typedef struct cb_payload { int i; } cb_payload;

int cb(int i, void* payload) {
    cb_payload* pay = payload;
    return i + pay->i;
}

typedef struct cb_payload2 { int i; int j; } cb_payload2;

int cb2(int i, void* payload) {
    cb_payload2* pay = payload;
    return i + pay->i + pay->j;
}

int caller(int i, int (*cb)(int i, void* payload), void* payload) {
    return i + cb(2, payload);
}

int main(void) {
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
        /* It is however possible to get the size of a `void*`. */
        printf("sizeof (void*) = %zu\n", sizeof(void*));

        /* ERROR: invalid application of sizeof to void type. */
        /*vp = vp + 1;*/
    }

    /* int* to void*: */
    vp = (void*)&i;

    /* void* to int*: */
    ip = (int*)vp;

    /* void* to int. */
    /* WARN GCC 4.8: cast from pointer to int of different size: -Wpointer-to-int-cast */
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

        /* TODO: UB, ID or good?  */
        /*assert(i == 0);*/
    }

    /*
    # Applications of void*

        If possible, avoid them, since they allow you to bypass type safety.

        Valid use cases:

        -   In libc, it is the return type of `malloc`, since it cannot know what type of pointer to return.
            You should use implicit casts with it only:
            http://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc

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
        cb_payload payload = {4};
        cb_payload2 payload2 = {4, 8};
        assert(caller(1, cb , &payload ) ==  7);
        assert(caller(1, cb2, &payload2) == 15);
    }

    return EXIT_SUCCESS;
}
