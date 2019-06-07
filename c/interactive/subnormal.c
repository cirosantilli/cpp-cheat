/* https://stackoverflow.com/questions/8341395/what-is-a-subnormal-floating-point-number/53203428#53203428
 * https://stackoverflow.com/questions/14001910/what-is-this-denormal-data-about-c/53203740#53203740
 *
 * Tested on Ubuntu 18.04 amd64.
 */

#if __STDC_VERSION__ < 201112L
#error C11 required
#endif

#ifndef __STDC_IEC_559__
#error IEEE 754 not implemented
#endif

#include <assert.h>
#include <float.h> /* FLT_HAS_SUBNORM */
#include <math.h> /* isnormal */
#include <stdlib.h>
#include <stdio.h>

#include "../float32.h"

#if FLT_HAS_SUBNORM != 1
#error float does not have subnormal numbers
#endif

int main(void) {
    /* Basic examples. */
    assert(lkmc_float32_equal(0.5f, 0, 126, 0));
    assert(lkmc_float32_equal(1.0f, 0, 127, 0));
    assert(lkmc_float32_equal(2.0f, 0, 128, 0));
    assert(isnormal(0.5f));
    assert(isnormal(1.0f));
    assert(isnormal(2.0f));

    /* Quick review of C hex floating point literals. */
    assert(0.5f == 0x1.0p-1f);
    assert(1.0f == 0x1.0p0f);
    assert(2.0f == 0x1.0p1f);

    /* Sign bit. */
    assert(lkmc_float32_equal(-0.5f, 1, 126, 0));
    assert(lkmc_float32_equal(-1.0f, 1, 127, 0));
    assert(lkmc_float32_equal(-2.0f, 1, 128, 0));
    assert(isnormal(-0.5f));
    assert(isnormal(-1.0f));
    assert(isnormal(-2.0f));

    /* The special case of 0.0 and -0.0. */
    assert(lkmc_float32_equal( 0.0f, 0, 0, 0));
    assert(lkmc_float32_equal(-0.0f, 1, 0, 0));
    assert(!isnormal( 0.0f));
    assert(!isnormal(-0.0f));
    assert(0.0f == -0.0f);

    /* ANSI C defines FLT_MIN as the smallest non-subnormal number. */
    assert(FLT_MIN == 0x1.0p-126f);
    assert(lkmc_float32_equal(FLT_MIN, 0, 1, 0));
    assert(isnormal(FLT_MIN));

    /* The largest subnormal number. */
    float largest_subnormal = lkmc_float32_from_bytes(0, 0, 0x7FFFFF);
    assert(largest_subnormal == 0x0.FFFFFEp-126f);
    assert(largest_subnormal < FLT_MIN);
    assert(!isnormal(largest_subnormal));

    /* The smallest non-zero subnormal number. */
    float smallest_subnormal = lkmc_float32_from_bytes(0, 0, 1);
    assert(smallest_subnormal == 0x0.000002p-126f);
    assert(0.0f < smallest_subnormal);
    assert(!isnormal(smallest_subnormal));

    /* Check that we can add two submormals. */
    float smallest_subnormal_2x = smallest_subnormal + smallest_subnormal;
    assert(lkmc_float32_equal(smallest_subnormal_2x, 0, 0, 2));

    return EXIT_SUCCESS;
}
