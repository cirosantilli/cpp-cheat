/*
# global scope

    What you can or can't do on global scope.
*/

#include "common.h"

/* This is a global variable: can be accessed and modified everywhere */
int global = 1;
int constGlobal = 1;

/* OK, const. Operators are magic functions. */
int global2 = 1 + 1;

/* ERROR: only var declarations with const initialization allowed. Compare to C++. */

    int ret1() {
        return 1;
    }

    /* Non-const. */
    /*int global2 = global + 1;*/
    /*int global2 = constGlobal + 1*/

    /* Funcion call. */
    /*puts("asdf");*/
    /*int global3 = ret1();*/

/* ERROR Cannot create scopes or branch in global scope. */

    /*{}*/
    /*if(1){}*/

int main(void) {
    assert(global == 1);
    assert(constGlobal == 1);
    assert(global2 == 2);
    return EXIT_SUCCESS;
}
