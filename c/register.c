/*
# register

    Hint to compiler that ri be stored in register
    instead of in RAM.

    Not necessarily honored.

    Almost always done without a hint if possible.
*/

#include "common.h"

int main() {
    {
        register int ri;
    }

    /* ERROR: cpu registers don't have addresses! */
    {
        register int ri;
        /*int* ip = &ri;*/
    }

    /*
    BAD: impossible to store compound types in registers
    compiler will certainly not honor `register` hint
    */
    {
        struct S { int i; };
        register struct S s;
    }

    return EXIT_SUCCESS;
}
