/*
# builtin_return_address

    Get address that function will return to after return.

    It seems that it is not possible to jump to a location without assemby:
    http://stackoverflow.com/questions/8158007/how-to-jump-the-program-execution-to-a-specific-address-in-c

    This is most useful for debugging.
*/

#include "common.h"

int main();

void builtin_return_address_test() {
    /*
    - 0 means for current function
    - 1 for the parent of current function
    - etc.
    */
    printf("main                        = %p\n", main);
    printf("__builtin_return_address(0) = %p\n", __builtin_return_address(0));
    return;
}

int main() {
    builtin_return_address_test();
    return EXIT_SUCCESS;
}
