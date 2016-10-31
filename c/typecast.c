/*
# Conversions

# typecast

    C99 6.3 "conversions"

    Transformation of one datatype to another.

    Can be done either implicitly or explicitly via a typecast operator.

    Some convertions may are allowed by the standard implicitly,
    but generate compiler warnings when done implicitly because in practice
    they should almost never be used.

    Some convertions are not allowed by the standard
    and should always generate compilation errors.

    Typecasts only transform the data:
    it seems that it is not possible to change the type of a variable itself:
    http://stackoverflow.com/questions/2822795/how-i-change-a-variable-of-a-type-to-another-one-in-c
*/

#include "common.h"

int main() {
    /*
    # Implicit typecasts done on operations

        The standard specifies which operations generate which typecasts.
    */
    {
        /* On assignment, the value is cast to the type of the variable assigned to. */
        {
            int i;
            /* A typecast to int is done because `i` is `int`. */
            i = 0.1;
            /* SAME: */
            i = (int)0.1;
            assert(i == 0);
        }

        /*
        If an operation involves an integer type and a floating type,
        TODO the integer type is cast to the floating type.
        */
        {
            assert(1/2 == 0);
            assert(1/2.0 == 0.5);

            /* Typecasts happen on the same order that the operations are evaluated. */
            assert(2.0*(1/2) == 0.0);
            assert((2.0*1)/2 == 1.0);
        }

        /*
        If an operation involves a smaller integer type and a larger integer type
        TODO the smaller type is first cast to the larger type
        */
        {
            assert((char)CHAR_MAX + 1 == ((int)(char)CHAR_MAX + 1));
        }
    }

    /*
    # Negative literals

        There are none.

        The `-` sign is an unary minus operator and creates an expression.

        It works out in the end because `1` in `-1` is a signed type,
        so the unary minus works fine on int.
    */
    {
        assert(-1 == -(1));
    }

    /*
    # unsigned to signed

    # signed to unsigned

        6.3.1.3
    */
    {
        /* Signed to unsigned: always OK. */
        {
            /* OK: can be represented. */
            {
                assert(((unsigned char)127) == ((char)127));
            }

            /* OK: to unsigned that cannot be represented wraps around. */
            {
                assert(((unsigned char)-1) == UCHAR_MAX);
            }
        }

#ifdef IMPLEMENTATION_SIGNAL
        /*
        Unsigned to signed is implementation defined, or implementation-defined signal.

        GCC 4.8 x86 does 2's complement.
        */
        {
            printf("(char)UCHAR_MAX = %d\n", (char)UCHAR_MAX);
        }
#endif
    }

    /*
    # float to int

    # int to float

    # typecasts between integer and floating point types

        C99 6.3.1.4 Real floating and integer
    */
    {
        /* float to int rounds towards 0. */
        {
            assert((int)0.5 == 0);
            assert((int)-0.5 == 0);
        }

        /*
        int to float can cause loss of precision if the int does not fit 
        in the fp mantissa.

        Implementations define if they will round to the nearerst
        larger or smaller float.
        */

#ifdef UNDEFINED_BEHAVIOUR
        /*
        If the float does not fit in an int, undefined behavior.
        */
        {
            /* Integral part too large. */
            printf("(int)1e1023L = %d\n", (int)1e1023L);

            /*
            Negative integer part cannot be represented by unsigned types:
            http://stackoverflow.com/questions/10541200/is-the-behaviour-of-casting-a-double-to-unsigned-int-defined-in-the-c-standard

            Setting it to 0 is a common behavior.
            */
            printf("(unsigned int)-1.1 = %u\n", (unsigned int)-1.1);

            /*
            Infinities and NAN
            http://stackoverflow.com/questions/3986795/casting-float-inf-to-integer
            */
            printf("(int)NAN = %u\n", (int)NAN);
        }
#endif
    }

    /* Array to pointer of same type: */
    {
        int is[] = {0, 1, 2};
        int *is2 = is;
        assert(is2[0] == 0);
    }

    /*
    # Integer to pointer.

    Implementation defined.

    http://stackoverflow.com/questions/9372936/can-we-assign-a-value-to-a-given-memory-location
    */

    /*
    # Implicit operator typecasts

    # Usual arithmetic conversions

        C99 6.3.1.8 "Usual arithmetic conversions"

        Operators are like functions, but they have one extra piece of magic:

        - the types of their inptus are not specified
        - they can be "overloaded"

        So unlike functions, we need magic rules for how to convert incompatible types.
    */
    {
    }

    /*
    # void typecast

        It is however possible to cast any type to void.

        But that cannot have any effect since you cannot set the result to a variable.

        It can however be used to avoid unused variable warnings.
    */
    {
        /*
        # Unused function arguments

            - avoid compiler warnings
            - document intent to developpers

            <http://stackoverflow.com/questions/4647665/why-cast-an-unused-function-parameter-value-to-void>

            Why would a function not use a parameter in real life:

            -   callbacks with fixed signature for which you don't need some parameters

            -   macros that can be turned on or off. In particular, remember that `assert()` is a macro
                and can be toggled with `NDEBUG`.
        */
        {
            int i = 0;
            (void)i;
            i = 1;
        }

        /*
        # Unused return value

            - avoid compiler warnings
        */
    }

    /*  */
    {
    }

    /* # Impossible typecats */
    {

        /* Certain typecasts always generates compilation errors. */

        /* Implicit pointer to int is impossible: */

            /*
            {
                int* ip;
                int i;
                i = ip;
            }
            */

        /* Pointer to float is impossible even with explicit typecast: */

            /*
            {
                int* ip;
                float f;
                f = (float)ip;
            }
            */

        /* Pointers of different types, */
        /* even if types for which data can be converted like floats and doubles: */

            /*
            {
                float* fp;
                double* dp;
                dp = fp;
            }
            */

        /* Array to array of different size: */

            /*
            {
                int is1[1];
                int is2[2];
                is2 = (int[])is1;
            }
            */
    }

    /*
    # Typecast between two struct types

    - http://stackoverflow.com/questions/3766229/casting-one-struct-pointer-to-other-c
    - http://stackoverflow.com/questions/27127914/why-is-this-implicit-conversion-between-different-pointer-types-valid?lq=1
    - http://stackoverflow.com/questions/10998639/is-it-possible-to-cast-struct-to-another
    - http://stackoverflow.com/questions/8416417/nested-structs-and-strict-aliasing-in-c
    */

    return EXIT_SUCCESS;
}
