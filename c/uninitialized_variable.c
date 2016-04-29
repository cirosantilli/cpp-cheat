/* # Uninitialized variables */

#include "common.h"

int uninitializedGlobal;

int main(void) {
#ifdef UNDEFINED_BEHAVIOUR
    /*
    Undefined behaviour for local variables:
    http://stackoverflow.com/questions/11962457/why-is-using-an-uninitialized-variable-undefined-behavior-in-c
    http://stackoverflow.com/questions/1597405/what-happens-to-a-declared-uninitialized-variable-in-c-does-it-have-a-value/36725211#36725211
    WARN -Wuninitialized
    */
    {
        int uninitializedLocal;
        printf("uninitializedLocal = %d\n", uninitializedLocal);
    }
#endif

    /* Fixed to 0 for global or static function variables. */
    {
        assert(uninitializedGlobal == 0);
    }

    return EXIT_SUCCESS;
}
