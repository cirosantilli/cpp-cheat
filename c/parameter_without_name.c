/*
# Parameter without name

    Function declarations don't need parameter names.

    If those are used for documentation purposes,
    they don't need to match those of the definition.
    This is highly confusing however.

    Definitions need parameter names.

    C++ missing names are also allowed on definitions.
*/

#include "common.h"

int f(int, float f);
int f(int i, float g) { return i + (int)g; }

/* ERROR: not possible for definitions. */
/*int g(int){}*/

int void_parameter(void) { return 1; }

int main() {
    assert(f(1, 1.5) == 2);

    /* The exception is the "void paramter". */
    assert(void_parameter() == 1);

    return EXIT_SUCCESS;
}
