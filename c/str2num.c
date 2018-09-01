/* http://stackoverflow.com/questions/7021725/converting-string-to-integer-c/12923949#12923949 */

#include "str2num.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i;
    /* Lazy to calculate this size properly. */
    char s[256];

    /* Simple case. */
    assert(str2int(&i, "11", 10) == STR2NUM_SUCCESS);
    assert(i == 11);

    /* Negative number . */
    assert(str2int(&i, "-11", 10) == STR2NUM_SUCCESS);
    assert(i == -11);

    /* Different base. */
    assert(str2int(&i, "11", 16) == STR2NUM_SUCCESS);
    assert(i == 17);

    /* 0 */
    assert(str2int(&i, "0", 10) == STR2NUM_SUCCESS);
    assert(i == 0);

    /* INT_MAX. */
    sprintf(s, "%d", INT_MAX);
    assert(str2int(&i, s, 10) == STR2NUM_SUCCESS);
    assert(i == INT_MAX);

    /* INT_MIN. */
    sprintf(s, "%d", INT_MIN);
    assert(str2int(&i, s, 10) == STR2NUM_SUCCESS);
    assert(i == INT_MIN);

    /* Leading and trailing space. */
    assert(str2int(&i, " 1", 10) == STR2NUM_INCONVERTIBLE);
    assert(str2int(&i, "1 ", 10) == STR2NUM_INCONVERTIBLE);

    /* Trash characters. */
    assert(str2int(&i, "a10", 10) == STR2NUM_INCONVERTIBLE);
    assert(str2int(&i, "10a", 10) == STR2NUM_INCONVERTIBLE);

    /* int overflow.
     *
     * `if` needed to avoid undefined behaviour
     * on `INT_MAX + 1` if INT_MAX == LONG_MAX.
     */
    if (INT_MAX < LONG_MAX) {
        sprintf(s, "%ld", (long int)INT_MAX + 1L);
        assert(str2int(&i, s, 10) == STR2NUM_OVERFLOW);
    }

    /* int underflow */
    if (LONG_MIN < INT_MIN) {
        sprintf(s, "%ld", (long int)INT_MIN - 1L);
        assert(str2int(&i, s, 10) == STR2NUM_UNDERFLOW);
    }

    /* long overflow */
    sprintf(s, "%ld0", LONG_MAX);
    assert(str2int(&i, s, 10) == STR2NUM_OVERFLOW);

    /* long underflow */
    sprintf(s, "%ld0", LONG_MIN);
    assert(str2int(&i, s, 10) == STR2NUM_UNDERFLOW);

    return EXIT_SUCCESS;
}
