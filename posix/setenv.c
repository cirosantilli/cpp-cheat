/*
# setenv

    Not specified by ANSI C, unlike getenv.

    Effects:

    - visible on future getenv calls of same program
    - passed on exec syscalls to children

# putenv

    Deprecated for `setenv` in POSIX 7.
*/

#include "common.h"

int main(void) {
    assert(setenv("HOME", "asdf", true) != -1);
    assert(strcmp(getenv("HOME"), "asdf") == 0);

    /* With overwrite false, if existing is not overwritten.
     * but error is not returned.
     */
    assert(setenv("HOME", "qwer", false) != -1);
    assert(strcmp(getenv("HOME"), "asdf") == 0);

    return EXIT_SUCCESS;
}
