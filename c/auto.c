/*
# auto

    Is the name for the default way to declare var
    that is neither volatile nor register.

    Sadly, in C++11 is is something completely different: type inference.
*/

#include "common.h"

int main() {
    /* SAME: */
    int i;
    auto int i2;

    /* ERROR: */
    /*auto i3;*/

    return EXIT_SUCCESS;
}
