/*
 * # float.h
 *
 * Gives characteristics of floating point numbers and of base numerical operations
 * for the current architecture
 *
 * All macros that start with FLT have versions starting with:
 *
 * - DBL   for `double`
 * - LDBL  for `long double`
 */

#include "common.h"

int main(void) {
    /* # FLT_ROUNDS
     *
     * Rounding method of sums.
     *
     * Values:
     *
     * - -1: indeterminable
     * - 0:  toward zero
     * - 1:  to nearest
     * - 2:  toward positive infinity
     * - 3:  toward negative infinity
     *
     * TODO can it be changed?
     */
    {
        printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);
    }

    /* # FLT_MIN
     *
     *     Smalles positive number closest to zero that can be represented in a normal float.
     *
     *     Any number with absolute value smaller than this is subnormal,
     *     and support is optional.
     */
    {
        printf("FLT_MIN  = %a\n",  FLT_MIN);
        printf("DBL_MIN  = %a\n",  DBL_MIN);
        printf("LDBL_MIN = %La\n", LDBL_MIN);
    }

    /* # FLT_RADIX
     *
     * Radix of the mantissa.
     *
     * TODO wow, there are non radix 2 representation implementations?!
     * IEEE 754 specifies the 2015-hardware-lowly-implemented radix 10,
     * maybe that is the major motivation?
     *
     * # FLT_MANT_DIG
     *
     * Number of digits bits for the mantissa:
     *
     * - 24 on 32-bit float
    */
    {
        printf("FLT_RADIX = %d\n", FLT_RADIX);
        printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
    }

    return EXIT_SUCCESS;
}
