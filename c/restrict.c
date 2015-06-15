/*
# restrict

    Identifier qualifier.

    Says to the compiler that every pointer passed to a function that is marked restrictd
    does not refer to the same element.

    Can only qualify pointers. The most common use case is to qualify pointers passed to functions.

    Programmers must ensure that temselves. if they don't, undefined behaviour.

    No behaviour change, but allows for further compiler optimization,
    so it should be used whenever possible. See generated assembly to spot the difference.

    Great example showing how restrict could help optimize things: http://en.wikipedia.org/wiki/Restrict
*/

#include "common.h"

void restrict_double_add(int * restrict i, int * restrict j, int * restrict add) {
    *i += *add;
    *j += *add;
}

void double_add(int *i, int *j, int *add) {
    *i += *add;
    *j += *add;
}

/* It makes no sense to mark a single pointer as restricted. */
void restrict_double_add_one_restrict(int * restrict i, int *j, int *add) {
    *i += *add;
    *j += *add;
}

int main() {
#if __STDC_VERSION__ >= 199901L
    {
        int i = 0;
        int j = 0;
        int add = 1;
        double_add(&i, &j, &add);
        assert(i == 1);
        assert(j == 1);
    }

    {
        int i = 0;
        int j = 0;
        int add = 1;
        restrict_double_add(&i, &j, &add);
        assert(i == 1);
        assert(j == 1);
    }

#ifdef UNDEFINED_BEHAVIOUR
    /*
    BAD: undefined behaviour, because the same pointer is passed twice

    The compiler should be able to spot that one... but gcc 4.7 did not.
    */
    {
        int i = 1;
        int j = 1;
        restrict_double_add(&i, &j, &i);
        if (i != 2)
            printf("restrict i = %d\n", i);
        if (j != 3)
            printf("restrict j = %d\n", j);
    }
#endif

    /* OK: not restrict */
    {
        int i = 1;
        int j = 1;
        double_add(&i, &j, &i);
        assert(i == 2);
        assert(j == 3);
    }

    /* Outside functions. */
    /* TODO what does it mean then? */
    {
        int i;
        int * restrict ip;
    }

    /* ERROR: can only qualify pointers */
    /*int restrict ip;*/
#endif
    return EXIT_SUCCESS;
}
