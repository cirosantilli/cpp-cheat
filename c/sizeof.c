/*
# sizeof

    Language keyword and an operator like +.

    Gives the size of the RAM representation of types **in multiples of CHAR_BIT**,
    which is the size of `char`. *Not* necessarily in bytes.

    The return type is `size_t.

    Calculated at compile time except for VLA.
*/

#include "common.h"

int main() {
    /* Can only be applied to object types, not function or incomplete. */
    {
        sizeof(int);

        /* Function type void f(); GCC*/
        /* ERROR. GCC allows it with certain flags. */
        /*sizeof(void());*/

        struct Incomplete;
        /*sizeof(struct Incomplete);*/
    }

    /*
    # size_t

        Typedef `size_t` to the data type that specifies data sizes in libc.

        `size_t` is returned by malloc, so it should large enough to represent any array index.
        TODO check: http://stackoverflow.com/questions/3174850/type-for-array-index-in-c99

        Always use it in your code instead of `int` to have greater portability.

        Can be printed in `printf` with `%zu`.

    # zu

        Printf  format string for `size_t`.
    */
    {
        size_t size = sizeof(int);
    }

    /* You can also take the sizeof of variables. No need for parenthesis then. */
    {
        int i;
        assert(sizeof i == sizeof(int));
    }

    /*
    # Size of primitives

        Implementation-defined behaviour.

        Base types like int of float don't have fixed ANSI sizes.

        ANSI C only specifies:

        - absolute minimum
        - relative minimums between types

        so machines are free to take optimal values in terms of speed/storage

        For most modifier os similar types (ex: short int, int, long, long long)
        the ANSI also guarantees size inequalities (equality is possible)

        stdint.h in C99 offeres fixed size integers.
    */
    {
        /* Print the actual values. */
#if __STDC_VERSION__ >= 199901L
        puts("sizeof");
        printf("  int         = %zu\n", sizeof(int)        );
        printf("  long int    = %zu\n", sizeof(long int)   );
        printf("  long long   = %zu\n", sizeof(long long)  );
        printf("  float       = %zu\n", sizeof(float)      );
        printf("  double      = %zu\n", sizeof(double)     );
        printf("  long double = %zu\n", sizeof(long double));
        printf("  wchar_t     = %zu\n", sizeof(wchar_t)    );
        printf("  size_t      = %zu\n", sizeof(size_t)     );
#endif

        /*
        # sizeof char

            Fixed to 1.

            It does not mean however that it is one byte wide!

            > When applied to an operand that has type char, unsigned char, or signed char,
            (or a qualified version thereof) the result is 1. When applied to an operand that has array
            type, the result is the total number of bytes in the array.8

        # byte

            TODO byte is not 8 bits in C!!!!

            It is only whatever char can store.
        */
        assert(sizeof(char) == 1);

        /*
        Relative guarantees.

        - http://stackoverflow.com/questions/11438794/is-the-size-of-c-int-2-bytes-or-4-bytes
        - http://stackoverflow.com/questions/7279504/long-and-long-long-bit-length
        - http://stackoverflow.com/questions/18901080/why-is-the-sizeofint-sizeoflong
        - http://stackoverflow.com/questions/12279060/difference-between-short-int-and-int-in-c
        */
        assert(sizeof(short int) <= sizeof(int          ));
        assert(sizeof(int      ) <= sizeof(long int     ));
#if __STDC_VERSION__ >= 199901L
        assert(sizeof(long int ) <= sizeof(long long int));
#endif
        assert(sizeof(float    ) <= sizeof(double       ));
        assert(sizeof(double   ) <= sizeof(long double  ));

        /*
        Absolute lower bound guarantees:

        - http://stackoverflow.com/questions/1738568/any-guaranteed-minimum-sizes-for-types-in-c

        C99 5.2.4.2.1 "Size of integer types"
        */
        assert(sizeof(short int) >= 2);
        assert(sizeof(long int) >= 4);
#if __STDC_VERSION__ >= 199901L
        assert(sizeof(long long int) >= 8);
#endif

        /* Unsigned does not change sizeof: */
        assert(sizeof(unsigned int) == sizeof(int));
        assert(sizeof(unsigned long int) == sizeof(long int));

        /*
        Pointers: sizeof can vary between:

        - data types: http://stackoverflow.com/questions/916051/are-there-are-any-platforms-where-pointers-to-different-types-have-different-size
        - data and function types: http://stackoverflow.com/questions/1473935/can-the-size-of-pointers-vary-depending-on-whats-pointed-to
        */

        /*
        # sizeof vs number of values

                sizeof(unsigned int) == 32

            does not imply that it can store 2^32 values.
        */
    }

    return EXIT_SUCCESS;
}
