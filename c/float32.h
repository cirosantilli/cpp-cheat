#ifndef LKMC_FLOAT32_H
#define LKMC_FLOAT32_H

#include <fenv.h> /* fetestexcept */
#include <inttypes.h>
#include <stdio.h>

/* Explicit byte array representation and printing of 32-bit float types. */

typedef struct {
    uint32_t sign, exponent, fraction;
} LkmcFloat32;

LkmcFloat32 lkmc_float32_from_float(float f) {
    uint32_t bytes;
    LkmcFloat32 lkmc_float32;
    bytes = *(uint32_t*)&f;
    lkmc_float32.fraction = bytes & 0x007FFFFF;
    bytes >>= 23;
    lkmc_float32.exponent = bytes & 0x000000FF;
    bytes >>= 8;
    lkmc_float32.sign = bytes & 0x000000001;
    bytes >>= 1;
    return lkmc_float32;
}

float lkmc_float32_from_bytes(
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

float lkmc_float32_snan(uint32_t i) {
    return lkmc_float32_from_bytes(0, 0xFF, 0x200000 + i);
}

int lkmc_float32_equal(
    float f,
    uint32_t sign,
    uint32_t exponent,
    uint32_t fraction
) {
    LkmcFloat32 lkmc_float32;
    lkmc_float32 = lkmc_float32_from_float(f);
    return
        (lkmc_float32.sign     == sign) &&
        (lkmc_float32.exponent == exponent) &&
        (lkmc_float32.fraction == fraction)
    ;
}

void lkmc_float32_print(float f) {
    LkmcFloat32 lkmc_float32 = lkmc_float32_from_float(f);
    printf(
        "0x%" PRIx32 " 0x%" PRIx32 " 0x%" PRIx32 "\n",
        lkmc_float32.sign, lkmc_float32.exponent, lkmc_float32.fraction
    );
}

void lkmc_float32_print_exceptions_and_clear(void) {
    int n = fetestexcept(FE_ALL_EXCEPT);
    if (n) {
        if (n & FE_INVALID  ) puts("FE_INVALID");
        if (n & FE_DIVBYZERO) puts("FE_DIVBYZERO");
        if (n & FE_INEXACT  ) puts("FE_INEXACT");
        if (n & FE_INVALID  ) puts("FE_INVALID");
        if (n & FE_OVERFLOW ) puts("FE_OVERFLOW");
        if (n & FE_UNDERFLOW) puts("FE_UNDERFLOW");
    }
    feclearexcept(FE_ALL_EXCEPT);
}

#endif
