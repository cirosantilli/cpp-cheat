/*
# float.h

    Gives characteristics of floating point numbers and of base numerical operations
    for the current architecture

    All macros that start with FLT have versions starting with:

    - DBL   for `double`
    - LDBL  for `long double`
*/

#include "common.h"

int main() {
    /*
    # Rounding method

    # FLT_ROUNDS

        Rounding method of sums.

        Values:

        - -1: indeterminable
        - 0:  toward zero
        - 1:  to nearest
        - 2:  toward positive infinity
        - 3:  toward negative infinity

        TODO can it be changed?
    */
    {
        printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);
    }

    /*
    # FLT_MIN

        Smalles positive number closest to zero that can be represented in a normal float.

        Any number with absolute value smaller than this is subnormal,
        and support is optional.
    */
    {
        printf("FLT_MIN  = %a\n",  FLT_MIN);
        printf("DBL_MIN  = %a\n",  DBL_MIN);
        printf("LDBL_MIN = %La\n", LDBL_MIN);
    }

    /*
    # FLT_RADIX

        Radix of the mantissa.

        TODO wow, there are non radix 2 representation implementations?!
        IEEE 754 specifies the 2015-hardware-lowly-implemented radix 10,
        maybe that is the major motivation?

    # FLT_MANT_DIG

        Number of digits bits for the mantissa:

        - 24 on 32-bit float

    # FLT_MANT_DIG
    */
    {
        printf("FLT_RADIX = %d\n", FLT_RADIX);
        printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
    }


#if __STDC_VERSION__ >= 201112L
    /*
    # subnormal numbers

        C11

        Defined in IEC 60599.

        E.g.:

            0.01

        Is represented as:

            1 * 10^-2

        However the exponent has a fixed number of bits, so if the exponent is too small.

        A solution to incrase that exponent is to allow number that start with 0.

        So if for example -4 is the smallest possible exponent, 10^-5 could be represented as:

            0.1 * 10^-4

        Such a number that cannot be represented without trailling zeroes is a subnormal number.

        The tradeoff is that subnormal numbers have limited precision.

        C11 specifies that the implementation of this feature is optional,
        and oe can check if those are supported in the implementation via the `HAS_SUBNORM` macros.

        As of 2013 hardware support is low but starting to appear.
        Before this date, implementations are done on software, and are therefore slow.

        The smallest floating normal number is `FLT_MIN`.

        Values:

        - -1: undeterminable
        - 0: no
        - 1: yes
    */
    {
        printf("FLT_HAS_SUBNORM  = %d\n", FLT_HAS_SUBNORM);
        printf("DBL_HAS_SUBNORM  = %d\n", DBL_HAS_SUBNORM);
        printf("LDBL_HAS_SUBNORM = %d\n", LDBL_HAS_SUBNORM);

        assert(isnormal(LDBL_MIN));

        if (LDBL_HAS_SUBNORM) {
            long double ldbl_min_2 = LDBL_MIN / 2.0;
            printf("LDBL_MIN / 2.0 = %La\n", ldbl_min_2);
            assert(ldbl_min_2 != 0);
            assert(ldbl_min_2 != LDBL_MIN);
            assert(! isnormal(ldbl_min_2));
        }
    }
#endif
    return EXIT_SUCCESS;
}
