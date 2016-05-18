/*
# Lexer
*/

#include "common.h"

int main(void) {
    /*
    # Maximal munch rule.

    http://stackoverflow.com/questions/5341202/why-doesnt-ab-work-in-c/24947922#24947922
    */
    {
        int i = 0;
        assert(i+++1 == 1);
        assert(i == 1);
    }

    return EXIT_SUCCESS;
}
