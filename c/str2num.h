#ifndef STRTONUM_H
#define STRTONUM_H

#include <ctype.h> /* isspace */
#include <errno.h>
#include <limits.h> /* INT_MAX, INT_MIN, LONG_MAX, LONG_MIN */
#include <math.h> /* HUGE_VALF */
#include <stdlib.h> /* strto* */

typedef enum {
    STR2NUM_SUCCESS,
    STR2NUM_OVERFLOW,
    STR2NUM_UNDERFLOW,
    STR2NUM_INCONVERTIBLE
} str2num_errno;

/** Convert string s to int out.
 *
 * @param[out] out The converted int. Cannot be NULL.
 *
 * @param[in] s Input string to be converted.
 *
 *     The format is the same as strtol,
 *     except that the following are inconvertible:
 *
 *     - empty string
 *     - leading whitespace
 *     - any trailing characters that are not part of the number
 *
 *     Cannot be NULL.
 *
 * @param[in] base Base to interpret string in. Same range as strtol (2 to 36).
 *
 * @return Indicates if the operation succeeded, or why it failed.
 */
str2num_errno str2int(int *out, char *s, int base) {
    char *end;
    long l;
    if (s[0] == '\0' || isspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    l = strtol(s, &end, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        return STR2NUM_OVERFLOW;
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        return STR2NUM_UNDERFLOW;
    if (*end != '\0')
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

/** @see str2int */
str2num_errno str2float(float *fout, char *s) {
    char *end;
    float f;
    if (s[0] == '\0' || isspace(s[0])) {
        return STR2NUM_INCONVERTIBLE;
    }
    errno = 0;
    f = strtof(s, &end);
    if ( errno == ERANGE && f == HUGE_VALF ) {
        return STR2NUM_OVERFLOW;
    }
    if ( errno == ERANGE && f == -HUGE_VALF ) {
        return STR2NUM_UNDERFLOW;
    }
    if (*s == '\0' || *end != '\0') {
        return STR2NUM_INCONVERTIBLE;
    }
    *fout = f;
    return STR2NUM_SUCCESS;
}

#endif
