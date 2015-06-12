/*
# Function pointers

    Functions can be stored in pointers and used through them.

    This is spcially useful to many related lots of functions inside a single
    struct to achieve a similar effect to that found on object oriented programming.
*/

#include "common.h"

int add_int(int n, int m) {
    return n+m;
}

int sub_int(int n, int m) {
    return n-m;
}

int int_func_func_int_int(int (*function_ptr)(int, int), int m, int n) {
    return (*function_ptr)(m, n);
}

int main() {
    /*
    Basic usage.

    Declare a function pointer named `f` that points to functions that take 2 ints
    and return one int.
    */
    {
        int (*f)(int n, int m);
        f = add_int;
        assert((*f)(1, 2) == 3);
        f = sub_int;
        assert((*f)(1, 2) == -1);
    }

    assert(add_int != sub_int);

    /* Function pointers can also be passed to functions of course. */
    {
        assert(int_func_func_int_int(add_int, 2, 1) == 3);
        assert(int_func_func_int_int(sub_int, 2, 1) == 1);
    }

    /*
    Array of function pointers.

    The array indication goes after the name of the array!
    */
    {
        int (*fs[])(int n, int m) = {add_int, sub_int};
        assert((*fs[0])(1, 2) ==  3);
        assert((*fs[1])(1, 2) == -1);
    }

    /*
    There are multiple ways to initialize and use function pointers because of implicit conversions.

    http://stackoverflow.com/questions/6893285/why-do-function-pointer-definitions-work-with-any-number-of-ampersands-or-as
    */
    {
        /* Alternative initialization methods. */
        int (*fs[])(int n, int m) = {
            &add_int,
            add_int,
            *add_int,
            **********************add_int,
        };

        /* Alternative call methods. */
        for (int i = 0; i < 4; i++) {
            assert((      fs[i])(1, 2) == 3);
            assert((     *fs[i])(1, 2) == 3);
            assert((******fs[i])(1, 2) == 3);
            /*assert((&fs[i])(1, 2) == 3);*/
        }

        /* ERROR no alternative for the declaration. */
        {
            /*int (f)(int n, int m) = add_int;*/
        }
    }

    return EXIT_SUCCESS;
}
