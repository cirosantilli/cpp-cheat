/*
# Trailing return type

    Introduced in C++11 to support lambdas where it is mandatory.

    But can also be used for regular functions.

    - http://stackoverflow.com/questions/11215227/should-the-trailing-return-type-syntax-style-become-the-default-for-new-c11-pr
    - http://stackoverflow.com/questions/12224325/what-is-the-meaning-of-auto-when-using-c-trailing-return-type
*/

#include "common.hpp"

#if __cplusplus >= 201103L
/* auto is mandatory here. */
auto f() -> int { return 1; }
#endif

int main() {
#if __cplusplus >= 201103L
    assert(f() == 1);
#endif
}
