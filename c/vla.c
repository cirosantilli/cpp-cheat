/*
# VLA

# Variable length array

    Implementation:

    - increase/decrease stack pointer
    - requires one addition and one multiplication per declaration

    Pros and cons:

    - http://stackoverflow.com/questions/2034712/is-there-any-overhead-for-using-variable-length-arrays
    - http://stackoverflow.com/questions/16672322/malloced-array-vs-variable-length-array
*/

#include "common.h"

#if __STDC_VERSION__ >= 199901L
/*
# [*]

    The "[*]" declaration syntax is possible to avoid naming parameters.
*/

    void vla_arg(size_t, int vla[*]);
    void vla_arg(size_t size, int vla[size]) {}

    void vla_arg_k_and_r(size, vla)
        /*int vla[size];*/ /* ERROR: must come after. */
        size_t size;
        int vla[size];
    {}
#endif

int main() {
#if __STDC_VERSION__ >= 199901L
    {
        srand(time(NULL));
        int size = 1 + (rand() % 10);
        int vla[size];

        /* sizeof is evaluated at runtime for VLAs */
        assert(sizeof(vla) == size * sizeof(int));
    }

    /*
    VLAs can be passed to functions.

    <http://stackoverflow.com/questions/17371645/parameter-of-a-function?lq=1>
    */
    {
        size_t size = 2;
        int vla[size];
        vla_arg(size, vla);
    }

    /*
    If the size must come after the vla (for example, to interface witha FORTRAN
    interface that does so), the only possibility is to use K&R function definition syntax!

    This is one of the very few application of K&R syntax to C99.
    */
    {
        size_t size = 2;
        int vla[size];
        vla_arg_k_and_r(vla, size);
    }

    /*
    Initialize VLA: nope:
    http://stackoverflow.com/questions/17332360/initializing-variable-length-array
    */
#endif
    return EXIT_SUCCESS;
}
