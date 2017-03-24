/*
# printf

    Write formated string to sdtout.

    Does not automaticaly append newlines.

    It is very useful to learn the format strings,
    since this has become a de facto standard and is also used
    for example in python format strings and bash `printf` command.

    html readable documentation on the c++11 printf format strings <http://www.cplusplus.com/reference/clibrary/cstdio/printf/>
    should be close to the latest C, and backwards compatible

    Since the formatting behaviour is identical to that of sprintf,
    sprintf tests may be used here if the output is predictable so that output can be asserted.

# Format string

    `printf` format strings will also be documented here.

    They are used by many other functions as well.

    C99 documents it with `fprintf`, but I figured newbs would look here first.
*/

#include "common.h"

char s[256];

int main() {

    /* char */
    {
        sprintf(s, "%c", 'a');
        assert(strcmp(s, "a") == 0);

        /*
        Repeat character n times.

        http://stackoverflow.com/questions/14678948/how-to-repeat-a-char-using-printfhttp://stackoverflow.com/questions/14678948/how-to-repeat-a-char-using-printf
        */
        {
            /* Only works for zeros '0'. */
            sprintf(s, "%0*d", 3, 0);
            printf("%s\n", s);
            assert(strcmp(s, "000") == 0);

            /* Only works for spaces ' '. */
            sprintf(s, "%*s", 3, "");
            printf("%s\n", s);
            assert(strcmp(s, "   ") == 0);
        }
    }

    /* int */
    printf("d INT_MAX = %d\n", INT_MAX);
    sprintf(s, "%d", 1);
    assert(strcmp(s, "1") == 0);

    /* long int: */
    printf("d LONG_MAX = %ld\n", LONG_MAX);
    sprintf(s, "%ld", 1L);
    assert(strcmp(s, "1") == 0);

    /* long long (int): */
    printf("lld LLONG_MAX = %lld\n", LLONG_MAX);
    sprintf(s, "%lld", 1LL);
    assert(strcmp(s, "1") == 0);

    /* # Floating point numbers */
    {
        /*
        float and double both use the the same char `f` char.

        This is likely because printf uses vararg, which automatically promotes float to double.
        */
        sprintf(s, "%f", 1.0f);
        assert(strcmp(s, "1.000000") == 0);
        sprintf(s, "%f", 1.0);
        assert(strcmp(s, "1.000000") == 0);

        sprintf(s, "%Lf", 1.0L);
        assert(strcmp(s, "1.000000") == 0);

        /* Control number of zeros after dot */
        {
            /* Fixed number. */
            {
                sprintf(s, "%.2f", 1.0f);
                assert(strcmp(s, "1.00") == 0);
            }

            /* Given by variable. */
            {
                sprintf(s, "%.*f", 2, 1.0f);
                assert(strcmp(s, "1.00") == 0);
            }
        }
    }

    /*
    typecasts in printf

        In most cases, gcc 4.8 can emmit warning for wrong types.

        Don't forget that printf takes vararg, which does some automatic type promotions,
        e.g.  float to double.

        TODO what happens when a wrong type is passed? Seems undefined?

        - http://stackoverflow.com/questions/8303673/why-cast-is-needed-in-printf
        - http://stackoverflow.com/questions/8559198/why-does-printf-implicit-float-to-int-conversion-not-work?lq=1
        - http://stackoverflow.com/questions/27495140/is-passing-a-float-to-printf-undefined-behavior
        - http://stackoverflow.com/questions/4664100/does-printfx-1-invoke-undefined-behavior
        - http://stackoverflow.com/questions/19444843/which-integral-promotions-do-take-place-when-printing-a-char?lq=1
        - http://stackoverflow.com/questions/4664100/does-printfx-1-invoke-undefined-behavior
        - http://stackoverflow.com/questions/15736497/how-to-print-an-unsigned-char-in-c
        - http://stackoverflow.com/questions/8303673/why-cast-is-needed-in-printf
    */
    {
        printf("u UINT_MAX = %u\n", UINT_MAX);

        sprintf(s, "%d", UINT_MAX);
        assert(strcmp(s, "-1") == 0);
    }

    /* # Control minimum number chars to output */
    {
        /*
        Pad with spaces, right align.

        Useful to output nicely formatted tables.

        Ugly:

            12345 1
            1 1

        Beautiful:

            12345 1
            1     1
        */
        {
            sprintf(s, "%6.2f", 1.0f);
            assert(strcmp(s, "  1.00") == 0);
        }

        /*
        Pad with zeros

        Useful for naming files: with `0`

        - "10" comes after  "09" ('1' > '0')
        - "10" comes before "9"  ('1' < '0')!
        */
        {
            sprintf(s, "%06.2f", 1.0f);
            assert(strcmp(s, "001.00") == 0);
        }

        /*
        Left align with `-`
        */
        {
            sprintf(s, "%-6s", "abc");
            assert(strcmp(s, "abc   ") == 0);

            /* Does not work with zeros. gcc 4.8.1 gives a warning. */

            /* sprintf(s, "%-06s", "abc"); */
            /* printf("%s\n", s); */
            /* assert(strcmp(s, "abc   ") == 0); */
        }
    }

    /* # Scientific */
    {
        sprintf(s, "%.3e", 1.0f);
        assert(strcmp(s, "1.000e+00") == 0);
    }

    /* # Strings */
    {
        sprintf(s, "%s", "abc");
        assert(strcmp(s, "abc") == 0);

        /*
        still not possible to print a null char with this
        substitution is done before
        */
        {
            char s[] = "000";
            sprintf(s, "%s", "a\0b");
            /* TODO why does this fail? */
            /*assert(memcmp(s, "a\00", 3) == 0);*/
        }
    }

    /*
    # Hexadecimal integer output (unsigned)

    # %x
    */
    {
        sprintf(s, "%x", 16);
        assert(strcmp(s, "10") == 0);

        /* Letter case control. */
        {
            sprintf(s, "%x", 10);
            assert(strcmp(s, "a") == 0);
            sprintf(s, "%X", 10);
            assert(strcmp(s, "A") == 0);
        }

        printf("-1 %%x = %x\n", -1);

        /* Long hex. */
        sprintf(s, "%lx", 16l);
        assert(strcmp(s, "10") == 0);
    }

#if __STDC_VERSION__ >= 199901L
    /*
    Hexadecimal scientific float output.

    Number of characters is automatically calculated.
    */
    {
        sprintf(s, "%a", 0x1.Ap11);
        assert(strcmp(s, "0x1.ap+11") == 0);

        sprintf(s, "%A", 0x1.Ap11);
        assert(strcmp(s, "0X1.AP+11") == 0);

        sprintf(s, "%a", 0x10.Ap11);
        assert(strcmp(s, "0x1.0ap+15") == 0);
    }
#endif
    /*
    # pointers printf format

        prints the hexadeciamal linear address.

        %p expects `void*`.

        To zero pad pointers representation, consider `PRIxPTR` from `inttypes.h`.
    */
    {
        /*
        Non null pointers are printed in a (bad?) notation starting with `0x`

        Also, trailling zeroes on the number are removed,
        so address 16 is represented as `0x10`
        */
        {
            sprintf(s, "%p", (void*)16);
            assert(strcmp(s, "0x10") == 0);
        }

        /* NULL pointer has a special representation as `(nil)` */
        {
            sprintf(s, "%p", NULL);
            assert(strcmp(s, "(nil)") == 0);
        }
    }

    /*
    # Escape percentage.

        Note that `%` is printf specific,
        not string literal specific,
        since percentages only have special meanings on strings passed to `printf`.
    */
    {
        sprintf(s, "%%");
        assert(strcmp(s, "%") == 0);
    }

    /* How to printf standard typedefs. */
    {
        /* For some of them, there are specific format strings. In those cases, just use them. */
        {
            printf("size_t    = %zu\n", (size_t)1);
            printf("intmax_t  = %jd\n", (intmax_t)1);
            printf("uintmax_t = %ju\n", (uintmax_t)1);
        }

        /* If there is no format string, but the type is assured to be an integer type, */
        /* typecast to the largest possible integer type and use `%jd` or `%ju`. */
        {

            /* Supppose that the API states that `integer_t` is a signed integer type. */
            /*typedef int integer_t;*/
            printf("integer_t = %jd\n", (intmax_t)1);
        }

        /*
        There are some cases in which there is no specific printf format,
        but there is a macro that expands to part of a format string that allows to print it correctly.
        */
        {
#if __STDC_VERSION__ >= 199901L
            printf("PRIxPTR uintptr_t = %" PRIxPTR "\n", (uintptr_t)16);
            printf("PRIdPTR uintptr_t = %" PRIdPTR "\n", (uintptr_t)16);

            /*
            sprintf has a different macro defined for it!
            */
            {
                sprintf(s, "%" SCNxPTR, (uintptr_t)1);
                printf("sprintf uintptr_t = %s\n", s);
            }
#endif
        }

        /*
        If a typedef is not guaranteed to be either an integer type or a floating point type,
        such as `clock_t`, there seems to be no decent solution as of C99
        http://stackoverflow.com/questions/1083142/whats-the-correct-way-to-use-printf-to-print-a-clock-t/17190680#17190680

        The best solution is to just cast it to the largest floating point type possible

        Unfortunatelly, as of c11 there is no way to get the largets floating point type
        as can be done for integers:
        http://stackoverflow.com/questions/17189423/how-to-get-the-largest-precision-floating-point-data-type-of-implemenation-and-i/17189562
        */
        {
            printf("clock_t = %Lf\n", (long double)(clock_t)1);
            printf("time_t  = %Lf\n", (long double)(clock_t)1);
        }
    }

    /*
    Return value: number of bytes written, negative if error.

    For string versions, excludes trailing '\0'.
    */
    {
        assert(sprintf(s, "%c", 'a') == 1);
    }

    return EXIT_SUCCESS;
}
