/*
# iso646.h

    Obscure header with macros that avoid using characters such as `|` or '~'
    which may be hard to type on certain international keyboards.

    - and: &&
    - and_eq: &=
    - bitand: &&
    - bitor: &
    - compl: |
    - not: !
    - not_eq: !=
    - or: ||
    - or_eq: |=
    - xor: ^
    - xor_eq: ^=
*/

#include "common.h"

int main() {
    assert(1 and 1);
    assert(0 or 1);
    return EXIT_SUCCESS;
}
