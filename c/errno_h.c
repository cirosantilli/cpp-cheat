/*
# errno.h

    Used for error handling.

    Defines `errno`, which can be set by user or library functions to indicate the error type.

    It is commonly used in operations such as file IO.

    Also define a few possible values which libc may set `errno` to:

    - EDOM. Domain error. Generated for example on `sqrt(-1.0)` of `math.h`.
    - EILSEQ
    - ERANGE

    *Many* more such errors are defined for example by POSIX.

    Each error has an error message string associated to it.
    To get that error message, consider using `strerror`.
    To print an error message to stderr, consider using `perror`.

    Success of calls does not normally set errno,
    and you can and should set it yourself in most cases:
    http://stackoverflow.com/questions/9856822/should-i-set-errno
*/

#include "common.h"

int main() {
    /* No error */
    errno = 0;

    /* EDOM error */
    errno = EDOM;

    /* TODO observe some interesting side effects. */

    return EXIT_SUCCESS;
}
