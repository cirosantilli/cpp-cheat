/*
# bitfield

    Gives support for fields which contain a single bit in the language.
*/

#include "common.h"

int main() {
    struct S {
        unsigned b1 : 1;
        unsigned b2 : 2;
        unsigned b3 : 3;

        /* padding untill next int is added automatically because */
        /* next data is not a bitfield and accesses is faster if it is aligned */

            int i;

        unsigned b4 : 1;

        /* manually adds padding untill next field */
        /* even if it is a bitfield */

            unsigned : 0;

        unsigned b5 : 1;
    } s ;

    assert(sizeof(struct S) == 16);

    s.b1 = 1;
    assert(s.b1 == 1);

    /* WARN */
    /* overflow */
    /* truncate */
    /*s.b1 = 2;*/

    int i = 2;
    s.b1 = i;
    assert(s.b1 == 0);

    /* Only takes lsb. */
    i = 3;
    s.b1 = i;
    assert(s.b1 == 1);

    return EXIT_SUCCESS;
}
