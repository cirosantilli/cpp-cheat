/*
# NDEBUG

    If defined *before assert.h* is included, asserts do nothing.

    Commonly defined form the command line.
*/

#define NDEBUG
#include <assert.h>
#include <stdlib.h>

int main() {
    assert(0);
    return EXIT_SUCCESS;
}
