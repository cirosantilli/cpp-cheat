/*
# exit

    Exit program at any point, including outside of the main function.

    Gets return value as an argument.

    On Linux, implemented with the sys_exit system call.
*/

#include "common.h"

void exit_func() {
    exit(EXIT_SUCCESS);
}

int main() {
    exit_func();
    /* Never gets run */
    return EXIT_FAILURE;
}
