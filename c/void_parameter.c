/*
# void parameter

    http://stackoverflow.com/questions/693788/c-void-arguments
*/

#include "common.h"

/* Prototype that takes no arguments. */
void void_arg(void);

/* ERROR: void must be the only parameter */
/*void void_int_arg(int, void);*/

/* WARN: parameter has void type */
/*void void_arg2(void v);*/

/* ERROR: incomplete type. */
/*void void_arg2(void v) {}*/

void def(void) {}

int main() {
    return EXIT_SUCCESS;
}
