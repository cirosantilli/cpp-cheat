/* https://stackoverflow.com/questions/10108053/ranges-of-floating-point-datatype-in-c/53204544#53204544 */

#include <assert.h>
#include <float.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

float float_from_bytes(
    uint32_t sign,
    uint32_t exponent,
    uint32_t fraction
) {
    uint32_t bytes;
    bytes = 0;
    bytes |= sign;
    bytes <<= 8;
    bytes |= exponent;
    bytes <<= 23;
    bytes |= fraction;
    return *(float*)&bytes;
}

int main(void) {
    /* All 1 exponent and non-0 fraction means NaN.
     * There are of course many possible representations,
     * and some have special semantics such as signalling vs not.
     */
    assert(isnan(float_from_bytes(0, 0xFF, 1)));
    assert(isnan(NAN));
    printf("nan                  = %e\n", NAN);

    /* All 1 exponent and 0 fraction means infinity. */
    assert(INFINITY == float_from_bytes(0, 0xFF, 0));
    assert(isinf(INFINITY));
    printf("infinity             = %e\n", INFINITY);

    /* ANSI C defines FLT_MAX as the largest non-infinite number. */
    assert(FLT_MAX == 0x1.FFFFFEp127f);
    /* Not 0xFF because that is infinite. */
    assert(FLT_MAX == float_from_bytes(0, 0xFE, 0x7FFFFF));
    assert(!isinf(FLT_MAX));
    assert(FLT_MAX < INFINITY);
    printf("largest non infinite = %e\n", FLT_MAX);

    /* ANSI C defines FLT_MIN as the smallest non-subnormal number. */
    assert(FLT_MIN == 0x1.0p-126f);
    assert(FLT_MIN == float_from_bytes(0, 1, 0));
    assert(isnormal(FLT_MIN));
    printf("smallest normal      = %e\n", FLT_MIN);

    /* The smallest non-zero subnormal number. */
    float smallest_subnormal = float_from_bytes(0, 0, 1);
    assert(smallest_subnormal == 0x0.000002p-126f);
    assert(0.0f < smallest_subnormal);
    assert(!isnormal(smallest_subnormal));
    printf("smallest subnormal   = %e\n", smallest_subnormal);

    return EXIT_SUCCESS;
}
