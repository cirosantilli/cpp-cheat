/*
# complex.h

    Defines:

    - convenient typedefs like `_Complex` and `I`
    - common operations over complex types: creal, cimag, cabs, etc.

    The complex types themselves are a feature of the language and shall not be described here.

    There is no direct printf way to print complex numbers:
    http://stackoverflow.com/questions/4099433/c-complex-number-and-printf

    All functions provided by this header are prefixed by `c`.

    http://en.wikipedia.org/wiki/Tgmath.h#Complex_numbers

    # complex vs _Complex

        `complex` is a typedef to `_Complex` contained in this header.

        The actual type keyword is `_Complex`: the language could not add
        a `complex` keyword because it could conflict with older programs.

        Adding `_Complex` however is fine because it is a reserved identifier.

        Prefer using `complex`: in the future it may become an actual keyword.
        It is easier to read and write.

    # I vs _Complex_I

        TODO

    # _Imaginary

        Defined in non normative section of C11.

        TODO vs complex?
*/

#include "common.h"

int main() {
#if __STDC_VERSION__ >= 199901L
#ifndef __STDC_NO_COMPLEX__
    puts("!__STDC_NO_COMPLEX__");

    const double err = 10e-6;

    /* Typedef to literal. There is not explicit literal in the language. */
    assert(I == _Complex_I);

    const double complex zd =  1.0 + 2.0*I;
    const double complex zd2 = 1.0 + 1.0*I;

    assert(sizeof(float complex ) <= sizeof(double complex));
    assert(sizeof(double complex) <= sizeof(long double complex));

    /* Real and imaginary parts. */
    assert(creal(zd) == 1.0);
    assert(cimag(zd) == 2.0);

    /* Subtraction. */
    assert(creal(zd - zd2) == 0.0);
    assert(cimag(zd - zd2) == 1.0);

    /* Multiplication. */
    assert(creal(zd * zd) == -3.0);
    assert(cimag(zd * zd) ==  4.0);

    /* Division. */
    assert(creal(zd / zd) == 1.0);
    assert(cimag(zd / zd) == 0.0);

    /* Conjugation. */
    assert(creal(conj(zd)) ==  1.0);
    assert(cimag(conj(zd)) == -2.0);

    /* absolute value == norm == module */
    assert(abs(cabs(3.0 + 4.0 * I) - 5.0) < err);

    /*
    # csqrt

        Unlike sqrt, can return imaginary outputs and take imaginary inputs.
    */
    {
        assert(cabs(csqrt(-1.0) - I) < err);
    }

    /*
    # cproj

        TODO
    */

    /*
    # csin

        TODO
    */
    /*assert(cabs(csin(I) - ) < err);*/
#endif
#endif
    return EXIT_SUCCESS;
}
