/*
http://stackoverflow.com/questions/7021725/converting-string-to-integer-c/12923949#12923949
*/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    STR2INT_SUCCESS,
    STR2INT_OVERFLOW,
    STR2INT_UNDERFLOW,
    STR2INT_INCONVERTIBLE
} str2int_errno;

/*
Convert string s to int out.

@param[out] out The converted int. Cannot be NULL.

@param[in] s Input string to be converted.

    The format is the same as strtol,
    except that the following are inconvertible:

    - empty string
    - leading whitespace
    - any trailing characters that are not part of the number

    Cannot be NULL.

@param[in] base Base to interpret string in. Same range as strtol (2 to 36).

@return Indicates if the operation succeeded, or why it failed.
*/
str2int_errno str2int(int *out, char *s, int base) {
    char *end;
    if (s[0] == '\0' || isspace(s[0]))
        return STR2INT_INCONVERTIBLE;
    errno = 0;
    long l = strtol(s, &end, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        return STR2INT_OVERFLOW;
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        return STR2INT_UNDERFLOW;
    if (*end != '\0')
        return STR2INT_INCONVERTIBLE;
    *out = l;
    return STR2INT_SUCCESS;
}

int main(void) {
    int i;
    /* Lazy to calculate this size properly. */
    char s[256];

    /* Simple case. */
    assert(str2int(&i, "11", 10) == STR2INT_SUCCESS);
    assert(i == 11);

    /* Negative number . */
    assert(str2int(&i, "-11", 10) == STR2INT_SUCCESS);
    assert(i == -11);

    /* Different base. */
    assert(str2int(&i, "11", 16) == STR2INT_SUCCESS);
    assert(i == 17);

    /* 0 */
    assert(str2int(&i, "0", 10) == STR2INT_SUCCESS);
    assert(i == 0);

    /* INT_MAX. */
    sprintf(s, "%d", INT_MAX);
    assert(str2int(&i, s, 10) == STR2INT_SUCCESS);
    assert(i == INT_MAX);

    /* INT_MIN. */
    sprintf(s, "%d", INT_MIN);
    assert(str2int(&i, s, 10) == STR2INT_SUCCESS);
    assert(i == INT_MIN);

    /* Leading and trailing space. */
    assert(str2int(&i, " 1", 10) == STR2INT_INCONVERTIBLE);
    assert(str2int(&i, "1 ", 10) == STR2INT_INCONVERTIBLE);

    /* Trash characters. */
    assert(str2int(&i, "a10", 10) == STR2INT_INCONVERTIBLE);
    assert(str2int(&i, "10a", 10) == STR2INT_INCONVERTIBLE);

    /*
    int overflow.

    `if` needed to avoid undefined behaviour
    on `INT_MAX + 1` if INT_MAX == LONG_MAX.
    */
    if (INT_MAX < LONG_MAX) {
        sprintf(s, "%ld", (long int)INT_MAX + 1L);
        assert(str2int(&i, s, 10) == STR2INT_OVERFLOW);
    }

    /* int underflow */
    if (LONG_MIN < INT_MIN) {
        sprintf(s, "%ld", (long int)INT_MIN - 1L);
        assert(str2int(&i, s, 10) == STR2INT_UNDERFLOW);
    }

    /* long overflow */
    sprintf(s, "%ld0", LONG_MAX);
    assert(str2int(&i, s, 10) == STR2INT_OVERFLOW);

    /* long underflow */
    sprintf(s, "%ld0", LONG_MIN);
    assert(str2int(&i, s, 10) == STR2INT_UNDERFLOW);

    return EXIT_SUCCESS;
}
