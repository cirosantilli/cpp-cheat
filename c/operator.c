/* # Operators */

#include "common.h"

int* int_ptr_func_int_ptr(int *ip) {
    (*ip)++;
    return ip;
}

int int_func_int(int i) {
    return i;
}

int main() {
    /*
    # Arithmetic operators

        Always be on the lookout for overflows. Rockets have fallen because of them.
    */
    {
        /*
        # Sum

        # +
        */
        {
            /* Basic example. */
            assert((1 + 2) == 3);

            /* On overflow, deterministic wrap for unsigned integer types. */
            {
                unsigned char i;
                /*i = UCHAR_MAX + (char)1;*/
                /*assert(i == 0);*/
            }

#ifdef UNDEFINED_BEHAVIOUR
            /*
            On overflow, undefined behaviour signed types.

            http://stackoverflow.com/questions/3948479/integer-overflow-and-undefined-behavior
            */
            {
                char i;
                i = CHAR_MAX + 1;
                printf("CHAR_MAX + 1 = %x\n", i);
            }
#endif

            /*
            Detect overflow:
            http://stackoverflow.com/questions/199333/best-way-to-detect-integer-overflow-in-c-c
            */
        }

        /*
        # Multiplication

        # *
        */
        {
            assert((2 * 3) == 6);

            /* Unsigned multiplication does modulo: */
            {
                unsigned char uc = 255;
                uc *= 2;
                assert(uc == 254);
            }

#ifdef UNDEFINED_BEHAVIOUR
            /* Undefined behaviour because signed. */
            {
                char c = CHAR_MAX;
                c *= 2;
                printf("CHAR_MAX * 2 = %x\n", c);
            }
#endif
            /*
            Detect overflow:
            http://stackoverflow.com/questions/1815367/multiplication-of-large-numbers-how-to-catch-overflow
            */

        }

        /*
        # Division

            Division is the most complex of the basic operations.

            Integer division and floating point division are different
            operations, which translate to different CPU instructions!

            Remember that if an operation involves a floating point and an integer,
            C first casts the integer type to a floating point type, then does
            the floating point operation.

            Division by `0` is undefined behaviour. On Linux it raises SIGFPE. 
            But note that handling the SIGFPE returns to just before the division. TODO check + example.

        # INT_MIN / -1

            `INT_MIN / -1` is undefined in 2's complement,
            and 2's complement is explicitly said to be compliant to the C
            integer representation standard.
        */
        {
            assert((4 / 2) == 2);

            /* integer division */
            assert((1 / 2) == 0);

            /* floating poitn division */
            assert((1.0 / 2.0) == 0.5);

            /*
            floating poitn division. `1` is cast to `double` point,
            according to the usual arithmetic conversions.
            */
            assert((1 / 2.0) == 0.5);

            /* Same as above. */
            assert((1 / (double)2) == 0.5);
        }

        /* # Unary minus */
        {
            /*
            Unary minus can overflow for the smallest negative number.

            TODO find quote.
            */
            {
#ifdef UNDEFINED_BEHAVIOUR
                printf("-INT_MIN = %x\n", -INT_MIN);
                /* Just to compare. */
                printf("INT_MIN = %x\n", INT_MIN);
#endif
            }

            /*
            Unary minus on unsigned is well defined and modulo wraps.

            http://stackoverflow.com/questions/8026694/c-unary-minus-operator-behavior-with-unsigned-operands

            6.2.5/9 says: A computation involving unsigned operands can never overflow,
            because a result that cannot be represented by the resulting unsigned integer type
            is reduced modulo the number that is one greater than the largest value
            that can be represented by the resulting type.
            */
            {
                assert(-1u == UINT_MAX);
            }
        }

        /*
        # Remainder

        # %

            a%b = a - (a/b)*b

        # Modulus

            It is *not* the mathematical modulus, as it gives different results for negative values.

            It is the mathematical remainder.

            http://stackoverflow.com/questions/11720656/modulo-operation-with-negative-numbers
        */
        {
            assert((-4 % 3) == -1);
            assert((-3 % 3) ==  0);
            assert((-2 % 3) == -2);
            assert((-1 % 3) == -1);
            assert(( 0 % 3) ==  0);
            assert(( 1 % 3) ==  1);
            assert(( 2 % 3) ==  2);
            assert(( 3 % 3) ==  0);
            assert(( 3 % 3) ==  0);
            assert(( 4 % 3) ==  1);
            assert(( 5 % 3) ==  2);
            assert(( 6 % 3) ==  0);

            assert((-3 % -3) ==  0);
            assert((-2 % -3) == -2);
            assert((-1 % -3) == -1);
            assert(( 0 % -3) ==  0);
            assert(( 1 % -3) ==  1);
            assert(( 2 % -3) ==  2);
            assert(( 3 % -3) ==  0);
            assert(( 4 % -3) ==  1);

#ifdef UNDEFINED_BEHAVIOUR
            /*assert((1 % 0) == 0);*/
#endif
        }

        /* # Comparison operators */
        {
            assert((1 == 1) == 1);
            assert((0 == 1) == 0);

            assert((0 >  1) == 0);
            assert((0 >  0) == 0);
            assert((0 > -1) == 1);
            assert((0 <  1) == 1);
            assert((0 <  0) == 0);
            assert((0 < -1) == 0);

            assert((0 >=  1) == 0);
            assert((0 >=  0) == 1);
            assert((0 >= -1) == 1);
            assert((0 <=  1) == 1);
            assert((0 <=  0) == 1);
            assert((0 <= -1) == 0);
        }
    }

    /*
    # Boolean operators

        The boolean operators treat all integers as:

        - 0: false
        - != 0: true

        The output of the boolean operators is always either 0 or 1.
    */
    {
        /*
        # !

        # Negation
        */
        {
            assert((!0) == 1);
            assert((!1) == 0);
            assert((!2) == 0);
            assert((!-1) == 0);

            /*
            `x == 0` is equivalent to `!x`.

            But its likely more readable to use `== 0` when doing comparisons,
            and to leave `!x` just for boolean operations.
            */
        }

        /*
        # ||

        # or
        */
        assert((0 || 0) == 0);
        assert((0 || 1) == 1);
        assert((1 || 0) == 1);
        assert((1 || 1) == 1);

        /*
        # &&

        # and
        */
        assert((0 && 0) == 0);
        assert((0 && 1) == 0);
        assert((1 && 0) == 0);
        assert((1 && 1) == 1);

        /*
        # Short circuit evaluation

            For operators `||`, `&&` and `?`, the second side is only evaluated if needed.

            On this example:

            - 1 is evaulated to true
            - || does not need to go any further, so i++ is not evaluated

            Those operators also define sequence points.
        */
        {
            int i = 0;
            1 || i++;
            assert(i == 0);
            1 && i++;
            assert(i == 1);
        }
    }

    /*
    # Bitwise operators

        On signed integers: implementation defined or UB:
        http://stackoverflow.com/questions/11644362/bitwise-operation-on-signed-integer
        so just never do it.
    */
    {
        /*
        # ~

        # NOT bitwise
        */
        assert((~(char)0x00) == (char)0xFF);
        assert((~(char)0xFF) == (char)0x00);

        /*
        # &

            AND bitwise

        # |

            OR bitwise
        */
        {
            assert(((char)0x00 & (char)0x00) == (char)0x00);
            assert(((char)0xFF & (char)0x00) == (char)0x00);
            assert(((char)0xFF & (char)0xFF) == (char)0xFF);

            /*
            `&` and `|` have lower precedence than `==`!

            Notorious design choice, since they are analogous to + and * ...

            GCC warns with -Wparentheses
            */
            {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
                assert(!(2 &  0  == 0 ));
#pragma GCC diagnostic pop
                assert(!(2 & (0  == 0)));
                assert( (2 &  0) == 0  );
            }

            /*
            # Even

            # Odd

            # Find if number is even or odd

                http://stackoverflow.com/questions/160930/how-do-i-check-if-an-integer-is-even-or-odd

                This is another "application" of `&`.

                But seems to be as fast as `%`, and is definitely less readable.
            */
            {
                assert((3 & 1) == 1);
                assert((4 & 1) == 0);
            }
        }

        /*
        # ||

        # OR bitwise
        */
        assert(((char)0x00 | (char)0x00) == (char)0x00);
        assert(((char)0xFF | (char)0x00) == (char)0xFF);
        assert(((char)0xFF | (char)0xFF) == (char)0xFF);

        /*
        # ^

        # XOR bitwise
        */
        assert(((char)0x00 ^ (char)0x00) == (char)0x00);
        assert(((char)0xFF ^ (char)0x00) == (char)0xFF);
        assert(((char)0xFF ^ (char)0xFF) == (char)0x00);

        /*
        # bitmask

            The major aplication of bitwise operators it making masks to:

            - set: MASK &
            - reset
            - toggle
            - retrieve

            bits from unsigned integer fields.

            These exist to allow to use one bit to store one bit,
            because the minimal addressable unit on computers is 8 bits.

            While such operators exist in almost all languages,
            they are much more common in low level languages like C
            where optimization is more present.

            Only work because C fixes the binary representation of unsigned integers.
        */

        /*
        # <<

        # >>

        # Shift operators

            Low level bit shifting.

            For the right input, the result would
            depend on which integer representation is being used,
            which is not fixed by the C standard.
        */
        {
            assert((1u << 0u) == 1u);
            assert((1u << 1u) == 2u);
            assert((1u << 2u) == 4u);
            assert((1u << 3u) == 8u);

            assert((8u >> 0) == 8u);
            assert((8u >> 1) == 4u);
            assert((8u >> 2) == 2u);
            assert((8u >> 3) == 1u);
            assert((8u >> 4) == 0u);
            assert((5u >> 1) == 2u);

            /* Negative operands */
            {
                /* TODO undefined or implementation defined? */
                printf("-1 << 1u = %d\n", -1 << 1u);
#ifdef UNDEFINED_BEHAVIOUR
                /* http://stackoverflow.com/questions/4945703/left-shifting-with-a-negative-shift-count */
                /*printf("2u << -1 = %d\n", 2u << -1);*/
#endif
            }

            /*
            # Binary operator on floating point numbers

                Fun, but not possible.

                http://stackoverflow.com/questions/1723575/how-to-perform-a-bitwise-operation-on-floating-point-numbers
            */
            {
                /*1.2 << 1;*/
            }
        }
    }

    /*
    # assign
    */
    {
        {
            int i = 0;
            i = 1;
            assert(i == 1);
        }

        /*
        = returns rvals
        */
        {
            int i;
            assert((i = 1) == 1);

            /*
            This is why this works (and probably why it is made behave like this.
            */
            {
                int i, j, k;
                i = j = k = 1;
                /*i = (j = (k = 1));*/
                assert(i == j && j == k && k == 1);
            }
        }

        /*
        # self assign initialization

            Good old undefined behaviour through innocent statements.

            <http://stackoverflow.com/questions/11186261/why-is-int-i-i-legal>
        */
        {
            int self_assign_init = self_assign_init;
            printf("self_assign_init = %d\n", self_assign_init);
        }

        /*
        # lvalue

            Something that can be on the left side of an assign, such as a variable.

            Every lvalue is a rvalue.

        # rvalue

            Something that can only be used on the right side of an assign,
            but not on the left side.
        */
        {
            /*
            In C, assign does not return lvalues.

            In C++ it does.
            */
            {
                int i = 0, j = 1, k = 2;
                /*(i = j) = k;*/
            }

            /*
            Function returns are rvalues.

            In C++, this has an exception: functions that return references return lvalues
            */
            {
                /*int_func_int(1) = 1;*/
                /*struct_func().i = 1;*/
            }

            /*
            A dereferenced pointer becomes an lvalue.
            */
            {
                int i = 0;
                (*int_ptr_func_int_ptr(&i)) = 2;
                assert(i == 2);
            }
        }
    }

    /*
    # Increment

        # Pre-increment vs post-increment

            <http://stackoverflow.com/questions/24886/is-there-a-performance-difference-between-i-and-i-in-c>

            Which is faster?

            - in c, equal
            - in c++, ++i potentially if i is a complex object

        # Why the increment operator exits

            Why it exists if equivalent to x=x+1?

            Because there is an x86 instruction for that

            Why?

            - because it takes less program memory `inc eax`, instead of `sum eax,1`
            - and is a *very* common instruction

            What about +=, -=, etc. ?

            Same thing: `ax = ax + bx` == `sum ax,bx`
    */
    {
        int i;

        i = 0;
        assert(i++ == 0);
        assert(i == 1);

        i = 0;
        assert(++i == 1);
        assert(i == 1);

        i = 1;
        assert(i-- == 1);
        assert(i == 0);

        i = 1;
        assert(--i == 0);
        assert(i == 0);

        /*
        Also works for floating point,
        although the usage is much less common.
        */
        double f = 0.5;
        assert(f++ == 0.5);
        assert(f == 1.5);
    }

    /*
    Composite operators

        Do an operation and an assign at the same time.

        Exist for many operators.

        Why do they exist? Assemby support probably,
        as many assembly operations overwrite one of the operands.
    */
    {
        int i;

        i = 0;
        assert((i += 1) == 1);
        assert(i == 1);

        i = 1;
        assert((i -= 1) == 0);
        assert(i == 0);

        i = 1;
        assert((i *= 2) == 2);
        assert(i == 2);

        i = 2;
        assert((i /= 2) == 1);
        assert(i == 1);

        i = 3;
        assert((i %= 2) == 1);
        assert(i == 1);

        i = 0xFF;
        assert((i &= (char)0x00) == (char)0x00);
        assert((char)i == (char)0x00);

        /* Same for others bitwise, except ~= which does not exist. */
        {
            unsigned char i = 0xFF;
            i = ~i;
            /* ? */
            /*i~=;*/
            assert((i & 0xFF) == 0);
        }
    }

    /*
    # Ternary operator

    # Question mark

    # ?

        Called ternary operator since it is the only operator that
        takes 3 inputs.

        Likely exists because of CMOV instructions. But with branch preditction CMOV can be slower than if / else:
        http://stackoverflow.com/questions/6754454/speed-difference-between-if-else-and-ternary-operator-in-c?lq=1#comment8007791_6754495

        - http://stackoverflow.com/questions/758849/the-ternary-conditional-operator-in-c
        - http://stackoverflow.com/questions/3565368/ternary-operator-vs-if-else
        - http://stackoverflow.com/questions/6754454/speed-difference-between-if-else-and-ternary-operator-in-c?lq=1
    */
    {
        assert((1 < 2 ? 3 : 4) == 3);
        assert((1 > 2 ? 3 : 4) == 4);

        /* The ternary operator can also yield lvalues. */
        {
            int x = 0, y = 1, *xp = &x, *yp = &y;
            *(1 ? xp : yp) = 10;
            assert(x == 10);
        }

        /* The possible to initialize consts with the ternary operator. */
        {
            const int i = 0 ? 1 : 2;
            char *s = 0 ? "a" : "b";
        }
    }

    /*
    # Comma operator

        Obscure and almost useless C operator.
    */
    {
        /*
        Commas here are part of the declarator sequence,
        just like in functions calls/defs. They are not
        comma operators!
        */

            int i=0, a=1, b=2, c=3;

        /*
        ignores values on left
        takes only last value on right

        BAD: operations on left has no effect
        */

            assert((i = 0, 1       ) == 1);
            assert((i = 0, i = 1, 2) == 2);

        /*
        assign has precedence over comma
        BAD: operation on right has no effect
        */
        {
            i = 2;
            (i = 0), 1;
            i = 0, 1;
            assert(i == 0);
        }

        /* ERROR */
        /* declaration int j does not return a value */
        /*int j=0, 1;*/

        /* operation on left comes first */
        {
            i=2;
            assert((i=0, i) == 0);
            i=2;
            assert((i=0, i++, i) == 1);
        }

        /* must be parenthesis protected when passesd as function argument */
        /* to differentiate from argument separtor comma */
        {
            int i = 0;
            assert(int_func_int((i++, i)) == 1);
        }
    }

    return EXIT_SUCCESS;
}
