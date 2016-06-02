/*
# ctype.h

    Character classification and conversion functions.

# unsigned char typecast

    I think it is required to avoid undefined behaviour, because
    char may or not be signed
    http://stackoverflow.com/questions/2054939/is-char-signed-or-unsigned-by-default
    and ctype functions UB if input is neither fits into `unsigned char` nor is EOF.

    Mentioned at: http://www.greenend.org.uk/rjk/tech/cfu.html

    Conversions to unsigned types are always defined (modulo),
    and char -> unsigned char is a bijection.
*/

#include "common.h"

int main(void) {
    /* # isspace */
    {
        assert(isspace((unsigned char)' '));
        assert(isspace((unsigned char)'\n'));
        assert(!isspace((unsigned char)'a'));
    }

    /* # isdigit */
    {
        assert(isdigit((unsigned char)'0'));
        assert(!isdigit((unsigned char)'a'));
    }

    /* # ispunct */
    {
        assert(ispunct((unsigned char)'"'));
        assert(ispunct((unsigned char)'('));
        assert(ispunct((unsigned char)'.'));
        assert(!ispunct((unsigned char)'a'));
        assert(!ispunct((unsigned char)'0'));
    }

    /*
    # toupper

    # tolower

        Work on characters.

        There is no built-in string version:
        http://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
    */
    {
        assert(tolower((unsigned char)'A') == 'a');
        assert(toupper((unsigned char)'a') == 'A');
    }

    return EXIT_SUCCESS;
}
