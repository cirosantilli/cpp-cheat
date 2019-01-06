/* # typeof
 *
 * Like C++11 decltype.
 *
 * Partially reproductible with C11 `_Generic`.
 *
 * https://stackoverflow.com/questions/6513806/would-it-be-possible-to-add-type-inference-to-the-c-language/31709221#31709221
 */

#include "common.h"

int main(void) {
    /* Same as: double j = 0.5; */
    typeof(1 + 0.5) j = 0.5;
    assert(j == 0.5);

    /* Similar to C++ auto. */
    __auto_type k = 0.5;
    assert(sizeof(j) == sizeof(k));

    return EXIT_SUCCESS;
}
