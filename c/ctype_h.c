/*
# ctype.h

    Character classficiation and conversion functions.
*/

#include "common.h"

int main() {
    /* # isspace */
    {
        assert(isspace(' '));
        assert(isspace('\n'));
        assert(!isspace('a'));
    }

    /* # isdigit */
    {
        assert(isdigit('0'));
        assert(!isdigit('a'));
    }

    /* # ispunct */
    {
        assert(ispunct('"'));
        assert(ispunct('('));
        assert(ispunct('.'));
        assert(!ispunct('a'));
        assert(!ispunct('0'));
    }

    /*
    # toupper

    # tolower

        Work on characters.

        There is no built-in string version:
        http://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
    */
    {
        assert(tolower('A') == 'a');
        assert(toupper('a') == 'A');
    }

    return EXIT_SUCCESS;
}
