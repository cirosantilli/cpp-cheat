/* https://stackoverflow.com/questions/18118408/what-is-difference-between-quiet-nan-and-signaling-nan/55648118#55648118 */

#include <assert.h>
#include <math.h> /* NAN, isnan */
#include <stdio.h>
#include <stdlib.h>

#include "float32.h"

int main(void) {
    float nanf0 = nanf("0");
    float nanf1 = nanf("1");
    float nanf2 = nanf("2");

    /* Let's view the actual bytes for several NaNs. */
    puts("nanf0");
    lkmc_float32_print(nanf0);
    puts("nanf1");
    lkmc_float32_print(nanf1);
    puts("nanf2");
    lkmc_float32_print(nanf2);
    puts("-nanf0");
    lkmc_float32_print(-nanf0);
    puts("-nanf1");
    lkmc_float32_print(-nanf1);
    puts("-nanf2");
    lkmc_float32_print(-nanf2);
    puts("NAN");
    lkmc_float32_print(NAN);
    puts("-NAN");
    lkmc_float32_print(-NAN);
    puts("0.0f / 0.0f");
    lkmc_float32_print(0.0f / 0.0f);
    puts("1.0f / 0.0f");
    lkmc_float32_print(1.0f / 0.0f);
    puts("");

    /* The exact printf representation is implementation defined.
     * glibc 2.23 only prints [+-]nan for all nans, so it is not
     * helpful to distinguish between them.
     */
    printf("printf nanf(\"0\") = %f\n", nanf0);
    printf("printf nanf(\"1\") = %f\n", nanf1);
    printf("printf nanf(\"2\") = %f\n", nanf2);
    printf("printf -nanf(\"0\") = %f\n", -nanf0);

    /* NANs are not ordered. any compairison to it yields false! */
    {
        assert(!(0.0 < NAN));
        assert(!(0.0 > NAN));
        assert(!(0.0 == NAN));
        assert( (0.0 != NAN));
    }

    /* isnan determines if the results is a nan or not.
     *
     * All / almost all operations that take NaN as input give NaN as output.
     */
    assert(isnan(0.0f / 0.0f));
    assert(isnan(NAN));
    assert(isnan(NAN + 1.0));
    assert(isnan(NAN + INFINITY));
    assert(isnan(NAN + NAN));
    assert(isnan(NAN - NAN));
    assert(isnan(NAN - 1.0));
    assert(isnan(NAN * 2.0));
    assert(isnan(NAN / 1.0));
    assert(isnan(INFINITY - INFINITY));
    assert(isnan(INFINITY * 0.0));
    assert(isnan(INFINITY / INFINITY));
    assert(!isinf(NAN));
    assert(isnan(sqrt(-1.0f)));

    return EXIT_SUCCESS;
}
