/*
# assert.h

    Defines the assert *macro*, which upon failure:

    - prints the file and line of the failure
    - calls abort

    Do not forget that `assert` is a *macro*, or this may lead to unexpected effects, such as:

    - unused variable warning because asserts got removed
    - in C++, no `std::` namespace
*/

#include "common.h"

int main() {
    assert(1);
    return EXIT_SUCCESS;
}
