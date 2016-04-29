/*
# void

    Mysterious type with many unrelated use cases:

    - indicate that a function returns nothing: `void f();`
    - indicate that a function declaration takes no arguments: `int f(void);`
    - pointers that can be typecast to any type for polymorphism
*/
#include "common.h"

int main(void) {
    /* ERROR: variable or field declared void */
    /*void v;*/

    /* OK: can have pointers however. */
    void *vp;

    /* ERROR: invalid application of sizeof to void type */
    /*printf("sizeof (void) = %d\n", sizeof(void));*/

    return EXIT_SUCCESS;
}
