/*
# types
*/

#include "common.h"

int main() {
    /*
    # Three major classes of types

    There are three major classes of types:

    - objects
    - function
    - incomplete
    */

    /*
    # Integer types

    # Integer literals

        Types that represent integer numbers are called integer types.

        This classification is explicitly used on the C specification,
        some operations or rule of the c language are only valid for integer types,
        while others work also for floating point types.

        `char` is also an integer type
    */
    {
        /* # char */
        {
            /* char has fixed size 1 byte: */
            assert(sizeof(char) == 1);

            /*
            6.4.4.4 Character constants
            */
            {
                /* char literals are specified by single quotes */
                char c = 'a';

                /*
                char literals are integers which happen to fit into char.

                This has been changed in C++.

                http://stackoverflow.com/questions/433895/why-are-c-character-literals-ints-instead-of-chars
                */
                assert(sizeof('a') == sizeof(int));

                /*
                TODO is ASCII guaranteed:

                - `assert('\0' == 0);`
                - for the soures?

                Seems not:
                http://stackoverflow.com/questions/15251049/does-the-underlying-character-set-depend-only-on-the-c-implementation

                > The value of an integer character constant containing more than one character (e.g.,
                'ab'), or containing a character or escape sequence that does not map to a single-byte
                execution character, is implementation-defined.
                */
                assert('\0' == 0);

                /*
                WARN: multi-character character literals are obscure valid code, but the
                byte ordering is undefined, so they are rarelly useful, and should be avoided. 

                gcc raises 4.8 warnings on -pedantic.
                */
                /* assert('ab' == 'ab'); */

                /* Can use the same backslash escapes as in strings. */
                assert('\'' == 0x27);
                assert('\n' == 0x0a);
            }
        }

        /*
        # short

            Short has no specific literals, the only way is to typecast.
        */
        {
            { short si = 1; }
            { short si = (short int)1; }
            { int i = 1; }
            /* Lower case possible but bad, since l looks more like 1 than `L`.*/
            { long li = (long)1l; }
            { long li = (long)1L; }
        }

#if __STDC_VERSION__ >= 199901L
        /* # long long int */
        {
            { long long lli = 8ll; }
            { long long lli = 8LL; }
        }
#endif

        /* ERROR: mixed cases not allowed */

            /*{ long long lli = 8Ll; }*/

        /* Short, long and long long are the same as the int versions: */

            assert(sizeof(short) == sizeof(short int));
            assert(sizeof(long) == sizeof(long int));
            assert(sizeof(long long) == sizeof(long long int));

        /*
        # unsigned

            C has unsigned versions of all built-in data types.

            These basically have more or less double the maximum size
            of the signed version, and are always positive.

            You should always use unsigned sizes for quantities which must be positive such as:

            - array indexes
            - memory sizes (size_t)

            As this will give clues to the compiler
            and humans about the positive quality of your number
        */
        {
            /* Literals. */
            {
                { unsigned char uc = (unsigned char)1; }
                { unsigned short usi = (unsigned short int)1u; }
                { unsigned int ui = 1u; }
                { unsigned int ui = 1U; }
                { unsigned long uli = 1lu; }
                { unsigned long uli = 1LU; }
                { unsigned long long ulli = 1llu; }
                { unsigned long long ulli = 1LLU; }

                /* The following are not recommended unless you are into code obfsucation: */
                { unsigned long uli = 1Lu; }
                { unsigned long uli = 1lU; }
                { unsigned long long ulli = 1LLu; }
                { unsigned long long ulli = 1llU; }

                /* ERROR: */
                /*{ unsigned long long ulli = 1Llu; }*/
            }

            /*
            # unsigned char

            # signed char

            # char vs unsigned char

                For all integer types, `signed X` is the same as `X`.

                `char` is the exception: there are *three* char types in C!

                - `char`: unspecified if signed or not
                - `signed char`
                - `unsigned char`

                http://stackoverflow.com/questions/2054939/is-char-signed-or-unsigned-by-default
            */

        }

        /* # Bases for integer literals */
        {
            /* # Hexadecimal */
            {
                assert(16 == 0x10   );
                assert(16 == 0x10   );
                assert(16 == 0x10l  );
                assert(16 == 0x10ll );
                assert(16 == 0x10u  );
                assert(16 == 0x10ul );
                assert(16 == 0x10ull);

                /* Case does not matter. */
                assert(0xaB == 0xAb );
            }

            /* Octal. */
            {
                assert(16 == 020);
            }

            /*
            # Binary literals

                No ANSI way, but exist as a GNU extension.
                <http://stackoverflow.com/questions/18244726/why-doesnt-c-have-binary-literals>
            */
        }

        /*
        # Integer representation

            C does not fix the binary representation for signed integers,
            it only states which properties represenations must have.

            As an example, the C standard explicitly mentions that the following
            representations (but there may be more) are compatible with the standard:

            - 2’s complement
            - 1’s complement
            - signed magnitude

            Unsigned representation however seems to be fixed at the canonical binary.
            This is what allows bitmasks to work.

            http://stackoverflow.com/questions/12125650/what-do-the-c-and-c-standards-say-about-bit-level-integer-representation-and-m
        */

        /*
        # Incomplete types

            Can have pointeres to them, but not variables.
        */
        {
            extern int is[];

            /* Undefined struct. */
            struct S *s;
        }
    }

    /* # Floating point types and literals */
    {
        /*
        # float

            Usually implemented as IEEE 754 32-bit float.
        */
        {
            float f1 = 1.23e-34f;
            assert(1. == 1.0f);
            assert(1.f == 1.0f);
            assert(1e0f == 1.0f);
            /* ERROR: there must be a dot without `e`. */
            /*float f = 1f;*/
        }

        /*
        # double

            Usually implemented as IEEE 754 32-bit float.
        */
        { double d = 1.23; }

        /*
        # long double

            Usually implemented as an 80-bit float, which is an extension allowed by IEEE.

            In, IEEE requires the exponent to have as many bits as the next larger defined size,
            which is 128-bit wth 15 bit exponent.

            This leaves 64-bits for the seignificand.

            sizeof usually says 128 because it is memory aligned.
        */
        {
            { long double ld = 1.23l; }
            { long double ld = 1.23L; }
        }

#if __STDC_VERSION__ >= 199901L
        /*
        # float hex literal

            E.g.:

                0xA.8p10

            Equals:

                1010.1000 * 2^3 = 10.5 x 2^10

            The exponent is given *in decimal*.
        */
        {
            assert(0xA.0p0  ==   10.0);
            assert(0xA.8p0  ==   10.5);
            assert(0x1.8p1  ==    3.0);
            assert(0x1.0p10 == 1024.0);
        }

        /* There is no octal float literal: */
        {
            /*float f = 01.2p3;*/
        }
#endif
    }

#if __STDC_VERSION__ >= 199901L
    /*
    # Boolean type

    # _Bool

        Aliased as `bool` in `stdbool.h`.
    */
    {
        _Bool b = 0;
    }
#endif

#if __STDC_VERSION__ >= 199901L
#ifndef __STDC_NO_COMPLEX__
    /*
    # Complex types

    # _Complex

        Possibly added to C99 to help replace FORTRAN once and for all.

    # Complex literals.

        Not part of the language: defined in the stdlib. For this reason,
        we have to cheat on complex literal together with the complex.h header.

    # STDC_NO_COMPLEX

        If defined the implementation may not have complex.h.

        Therefore, it is possible to be compliant without it.
    */
    {
        { float _Complex c; }
        { double _Complex c; }
        { long double _Complex c; }

        /*
        WARN: You must say `double _Complex` or `float _Complex`:
        just `_Complex is not standard.
        */
        {
            /* _Complex c */
        }

        /*
        # Complex integer types

            Complex integer types are not specified in C.

            GCC adds them as an extension.
        */
        {
            /*int complex zi = 1 + 1*I;*/
        }
    }
#endif
#endif

    return EXIT_SUCCESS;
}
