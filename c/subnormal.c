/* # subnormal numbers
 *
 * Defined in IEC 60599.
 *
 * E.g.:
 *
 *     0.01
 *
 * Is represented as:
 *
 *     1 * 10^-2
 *
 * However the exponent has a fixed number of bits, so if the exponent is too small.
 *
 * A solution to incrase that exponent is to allow number that start with 0.
 *
 * So if for example -4 is the smallest possible exponent, 10^-5 could be represented as:
 *
 *     0.1 * 10^-4
 *
 * Such a number that cannot be represented without trailling zeroes is a subnormal number.
 *
 * The tradeoff is that subnormal numbers have limited precision.
 *
 * C11 specifies that the implementation of this feature is optional,
 * and oe can check if those are supported in the implementation via the `HAS_SUBNORM` macros.
 *
 * As of 2013 hardware support is low but starting to appear.
 * Before this date, implementations are done on software, and are therefore slow.
 *
 * The smallest floating normal number is `FLT_MIN`.
 *
 * Values:
 *
 * - -1: undeterminable
 * - 0: no
 * - 1: yes
 */
#include "common.h"

void print_bytes(char *p, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%zu %02hhx\n", i, p[i]);
    }
}

int main(void) {
#if __STDC_VERSION__ >= 201112L
    {
        printf("FLT_HAS_SUBNORM  = %d\n", FLT_HAS_SUBNORM);
        float min = FLT_MIN, min_2;
        assert(isnormal(min));
        if (FLT_HAS_SUBNORM) {
            min_2 = min / 2.0;
            printf("min / 2.0 = %a\n", min_2);
            assert(min_2 != 0.0);
            assert(min_2 < min);
            assert(!isnormal(min_2));
        }
        puts("bytes min");
        print_bytes((char *)&min, sizeof(min));
        puts("bytes min_2");
        print_bytes((char *)&min_2, sizeof(min_2));
        puts("");
    }
    {
        printf("DBL_HAS_SUBNORM = %d\n", DBL_HAS_SUBNORM);
        double min = DBL_MIN, min_2;
        assert(isnormal(min));
        if (DBL_HAS_SUBNORM) {
            min_2 = min / 2.0;
            printf("min / 2.0 = %a\n", min_2);
            assert(min_2 != 0.0);
            assert(min_2 < min);
            assert(!isnormal(min_2));
        }
        puts("bytes min");
        print_bytes((char *)&min, sizeof(min));
        puts("bytes min_2");
        print_bytes((char *)&min_2, sizeof(min_2));
        puts("");
    }
    {
        printf("LDBL_HAS_SUBNORM = %d\n", LDBL_HAS_SUBNORM);
        long double min = LDBL_MIN, min_2;
        assert(isnormal(min));
        if (LDBL_HAS_SUBNORM) {
            min_2 = min / 2.0;
            printf("min / 2.0 = %La\n", min_2);
            assert(min_2 != 0.0);
            assert(min_2 < min);
            assert(!isnormal(min_2));
        }
        puts("bytes min");
        print_bytes((char *)&min, sizeof(min));
        puts("bytes min_2");
        print_bytes((char *)&min_2, sizeof(min_2));
        puts("");
    }
#endif
    return EXIT_SUCCESS;
}
