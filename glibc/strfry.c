/* # strfry
 *
 * Randomly shuffle a string.
 *
 * Return the string itself.
 *
 * C++ has std::shuffle.
 *
 * TODO mnemonic? Fry a string?
 */

#include "common.h"

int main(void) {
    char s[] = "abcd";
    printf("%s\n", strfry(s));
    printf("%s\n", strfry(s));
}
