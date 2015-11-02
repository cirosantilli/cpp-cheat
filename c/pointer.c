/*
# Pointer

    Pointers contain addresses of variables instead of the value.

    Using the dereference operator `*`, you can get the value from the address.
*/

#include "common.h"

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
    /*float *fp = &i;*/

    /* OK: works with explicit cast: */
    float *fp = (float *)&i;

    /*
    # Single line multiple pointer declaration

        You must put an asterisk for each pointer, or they are not taken to be pointers!

        This is not very intuitive since the asterisk is part of the type, not of the variable.
    */
    {
        /* Correct */
        {
            int i, *ip ;
            ip = &i;
        }

        /* ERROR: ip2 is not a pointer, but an int! */
        {
            /*int i;*/
            /*int *ip, ip2;*/
            /*ip = &i;*/
            /*ip2 = &i;*/
        }
    }

    /*
    # Two varibles with the same address

        Impossible:
        http://stackoverflow.com/questions/15590727/same-address-of-two-variables

        Possible in C++ with references `&`.
    */

    return EXIT_SUCCESS;
}
