/*
# Compound struct literal

    Create literals for structs.

    They behave exactly like initialized objects, except that they have no variable name.
*/

#include "common.h"

int main() {
    struct S { int i; int j; };

    /* Basic example. */
    {
        struct S s;
        s = (struct S){1, 2};
        /* Remember that this would fail. */
        /*s = {1, 2};*/
        assert(s.i == 1);
        assert(s.j == 2);
    }

    /* With designated initializer syntax. */
    {
        struct S s;
        s = (struct S){.j = 2, .i = 1};
        assert(s.i == 1);
        assert(s.j == 2);
    }

    /* They do generate lvalues. */
    {
        struct S *sp;
        sp = &(struct S){1, 2};
        assert(sp->i == 1);
        assert(sp->j == 2);

        /* Unlike string literals, they can be modified. */
        sp->i = 3;
        sp->j = 4;
        assert(sp->i == 3);
        assert(sp->j == 4);
    }

    /*
    # Lifetime of compound struct literals

        - if inside a function, automatic associated with current block.
        - otherwise, static

        http://stackoverflow.com/questions/14955194/lifetime-of-referenced-compound-array-literals
    */

    /* Can also be used to initialize variables, although that is useless. */
    struct S s = (struct S){1, 2};

    return EXIT_SUCCESS;
}
