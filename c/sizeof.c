/*
# sizeof

    Language keyword.

    Gives the size of the RAM representation of types **in multiples of CHAR_BIT**,
    which is the size of `char`. *Not* necessarily in bytes.

    The return type is `size_t.

    Calculated at compile time.
*/

#include "common.h"

int main() {
    /*
    # size_t

        Typedef `size_t` to the data type that specifies data sizes in libc.

        `size_t` is large enough to represent any array index.

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
        printf("  char        = %zu\n", sizeof(char)       );
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
        char is an exception: we know it is always 1 since `sizeof`
        is defined in multiples of `sizeof(char)`.
        */
        assert(sizeof(char) == 1);

        /* Relative guarantees. */
        assert(sizeof(short int) <= sizeof(int          ));
        assert(sizeof(int      ) <= sizeof(long int     ));
#if __STDC_VERSION__ >= 199901L
        assert(sizeof(long int ) <= sizeof(long long int));
#endif
        assert(sizeof(float    ) <= sizeof(double       ));
        assert(sizeof(double   ) <= sizeof(long double  ));

        /*
        Absolute lower bound guarantees:
        http://stackoverflow.com/questions/1738568/any-guaranteed-minimum-sizes-for-types-in-c

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
    }

    return EXIT_SUCCESS;
}
