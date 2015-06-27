/*
# Identifiers
*/

#include "common.h"

int main() {
    /*
    # $ is legal in identifiers

        Like in Java and JavaScript.
    */
    {
        int $ = 0;
        assert($ == 0);
    }
    return EXIT_SUCCESS;
}
