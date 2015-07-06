/*
# Typedef function

    http://stackoverflow.com/questions/3674200/what-does-a-typedef-with-parenthesis-like-typedef-int-fvoid-mean-is-it-a
*/

#include "common.h"

typedef int f_t(int, int);
/* Same: parenthesis is optional. */
typedef int (g_t)(int, int);

/* Parenthesis here is mandatory! */
typedef int (*fp_t)(int, int);

int f(int i, int j) {
    return i + j;
}

int main() {
    /* Declare function. */
    {
        f_t f;
        assert(f(1, 2) == 3);
    }

    /*
    Cannot define a function however with it,
    as it does not have parameter names.
    */

    /* Put function in a variable. */
    {
        /* Non pointer typedef. */
        {
            f_t *fp;
            fp = f;
            /* I think a typedef is the only way not to use `*` here. */
            assert(fp(1, 2) == 3);
        }

        /* Pointer typedef. */
        {
            fp_t fp;
            fp = f;
            assert((*fp)(1, 2) == 3);
        }
    }

    return EXIT_SUCCESS;
}
