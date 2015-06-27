/*
# Literals
*/

#include "common.h"

int main() {
    /*
    # Binary int literals

        start with `0b`:
    */
    {
        assert(0b10000 == 16);
    }

    /*
    # D double specifier

        Java also allows it, but Java also allows 1D which is more useful.
    */
    {
        assert(1.2D == 1.2);
    }

    /*
    # String

    # \e

        Esc escape character. Useful for the ANSI escape sequences,
        and in particular terminal coloring.
    */
    {
        assert(((int)'\e') == 27);
    }

    return EXIT_SUCCESS;
}
