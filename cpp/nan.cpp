// https://stackoverflow.com/questions/18118408/what-is-difference-between-quiet-nan-and-signaling-nan/55648118#55648118
//
// C++ has some NaN functionality that C does not have,
// we will illustrate those here.

#include <cassert>
#include <cmath> // isnan
#include <iostream>
#include <limits> // std::numeric_limits

#include "../c/float32.h"

#pragma STDC FENV_ACCESS ON

int main() {
    if (
        std::numeric_limits<float>::has_signaling_NaN &&
        std::numeric_limits<float>::has_quiet_NaN
    ) {
        float snan = std::numeric_limits<float>::signaling_NaN();
        float qnan = std::numeric_limits<float>::quiet_NaN();
        float f;

        std::cout << "snan" << std::endl;
        lkmc_float32_print(snan);
        std::cout << "qnan" << std::endl;
        lkmc_float32_print(qnan);

        // No exceptions.
        assert(std::fetestexcept(FE_ALL_EXCEPT) == 0);

        // Still no exceptions because qNaN.
        f = qnan + 1.0f;
        assert(std::isnan(f));
        assert(std::fetestexcept(FE_ALL_EXCEPT) == 0);

        // Now we get an exception because sNaN.
        f = snan + 1.0f;
        assert(std::isnan(f));
        assert(std::fetestexcept(FE_ALL_EXCEPT) == FE_INVALID);
        feclearexcept(FE_ALL_EXCEPT);

    }
}
