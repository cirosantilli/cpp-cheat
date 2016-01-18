/*
# assert fail

    Let's see what happens when an assert fails.

    Expected outcome: it should call abort, and not print anything to the screen
*/

#include "common.h"

int main() {
    assert(0);
    puts("here");
    return EXIT_SUCCESS;
}
