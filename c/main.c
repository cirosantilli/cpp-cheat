/*ANSI C cheat.

This file is being split up into smaller parts to c/
*/

#include "common.h"

/* # global scope */

    /* This is a global variable: can be accessed and modified everywhere */
    int global = 1;

    /* OK! */
    int global2 = 1+1;

    int ret1() {
        int i;
        /* before main! */
        return 1;
    }

    int uninitializedGlobal;

    /* ERROR: only var declarations with const initialization allowed */

        /* Non-const. */
        /*int global2 = global+1;*/

        /* Funcion call. */
        /*puts("asdf");*/
        /*int global3 = ret1();*/

        /* Branching statement. */
        /*if(1){}*/

    /* ERROR */
    /* Cannot create scopes here like that */
    /* They'd be useless anyways. */

        /*{}*/

    int same_name_as_variable() { return 0; }

/* Pointer array */

    int* get_arr(int i) {
        /*int is[] = {i};*/
        /*return is;*/
            /* WARN */
            /* return adress of local var */
            /* data is destroyed on return! */

        int* ip = (int*) malloc(sizeof(int) * 1);
        return ip;
    }

/* Functions TODO remove */

    void func_array(int a[]){
        assert(a[0] == 1);
    }

    struct func_struct { int i; };
    void func_struct_1(struct func_struct s) {
        assert(s.i == 1);
    }

    const int* const_int_ptr_func_int_ptr(int *ip) {
        (*ip)++;
        return ip;
    }

/*
# main

    # Call main from the program

        Seems legal:
        http://stackoverflow.com/questions/13948562/recursion-using-main-function#comment19237980_13948579

        Illegal in C++ however.

    # main signature

        - http://stackoverflow.com/questions/204476/what-should-main-return-in-c-and-c
        - http://stackoverflow.com/questions/4207134/what-is-the-proper-declaration-of-main

        Valid signatures: either:

            int main()

    or:

            int main(int argc, char *argv[])

        Or equivalent ones to the above:

        TODO name of equivalend:

            int main(int argc, char **argv)

        Default return type `int` (C89 only):

            main()

        Explicit `void` prototype:

            int main(void)
*/
int main(int argc, char **argv) {

    /*
    Comments.
    */
    {
        /* Standard multi line comment. */
        /*
        assert(false);
        */

        /* A comment may contain `/ *`, but GCC warns with `-Wcomment`. */

#if __STDC_VERSION__ >= 199901L
        /* Double slash comment like in C++ were only introduced in C99. */
        /*assert(false);*/
#endif
    }

    /*
    # Basic types

        Types like `int`, `char`, `float` and `_Complex`.

    # Derived types

        Types which are not based, bur defined by users,
        e.g., arrays, structs and unions.
    */


    /* # variables */
    {
        {
            int i;
            i = 5;
        }

        {
            int i = 5;
            int j = 7;
        }

        /* 31 bit + 1 sign bit integer */
        {
            int i = 5, j = 7;
        }

        /* # Uninitialized variables. */
        {
#ifdef UNDEFINED_BEHAVIOUR
            /*
            Undefined behaviour for local variables:
            http://stackoverflow.com/questions/11962457/why-is-using-an-uninitialized-variable-undefined-behavior-in-c

            WARN -Wuninitialized
            */
            {
                int uninitializedLocal;
                printf("uninitializedLocal = %d\n", uninitializedLocal);
            }
#endif

            /* Fixed to 0 for global or static function variables. */
            {
                assert(uninitializedGlobal == 0);
            }
        }
    }

    /*
    # Literals

        *Literals* are values that can be expressed through a single
        language dedicated feature:

        - int:    `1`
        - long:   `1L`
        - float:  `1.0f`
        - double: `1.0`and their
        - char:   `'a'`
        - string: `"abc"`

        Some base types do not have specific literals: e.g. `short`.

        C99 introduces compound literals, which allow creation of literals for

        - arrays
        - structs
        - unions
    */
    {
#if __STDC_VERSION__ >= 199901L
        /*
        # compound literals

            Before C99 there were no literals for arrays, structs or unions,
            while literals existed for ints, chars and even strings (which are arrays of chars...)

            Compound literals are exactly that: literals for types that are made up of many smaller
            pieces, thus compounded.

            Great source: <www.drdobbs.com/the-new-c-compound-literals/184401404>
        */
        {
            /* Compound literals for arrays */
            {
                int *is;

                is = (int[2]){ 0, 1 };
                assert(is[0] == 0);
                assert(is[1] == 1);

                /* Reassign is to a new array. */
                /* Old memory becomes innacessible. */
                is = (int[2]){ 2, 3 };
                assert(is[0] == 2);
                assert(is[1] == 3);

                /* The effect is the same as `int is[] = { 1 }`, */
                /* that is: fill with zeroes. */
                is = (int[2]){ 1 };
                assert(is[0] == 1);
                assert(is[1] == 0);

                /* Major application: pass initialized arrays and structs to functions. */
                {
                    func_array((int[]){ 1 });
                    func_struct_1((struct func_struct){ .i = 1 });
                }
            }

            /*
            Compound literals yield lvalues.

            It is possible to take the address of compound literals.

            Unlike string literals, array literals can be modified.

            This means that the compound literal is an unnamed stack variable,
            and takes stack space.
            */
            {
                int *ip;
                ip = &(int){1};
                ip[0]++;
                assert(*ip == 2);
            }

            /* Int useless examples */
            {
                int i;

                i = (int){1};
                assert(i == 1);

                i = (int){1} + (int){1};
                assert(i == 2);

                /* Any expression is fine */
                {
                    i = 0;
                    i = (int){i + 1};
                    assert(i == 1);
                }
            }

            /*
            Scope of compound literals.

            Just like for normal variable declaration,
            compound literal memory can only be accessed in the scope in which it is declared.

            http://stackoverflow.com/questions/14955194/lifetime-of-referenced-compound-array-literals
            */
            {
                int *p;
                {
                    p = (int[]){1, 2};
                    assert(p[0] == 1);
                }
                /* BAD *p is undefined. */
                /*assert(p[0] == 1);*/
            }
        }
#endif
    }

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
    {
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
            /* OK: can be represented. */
            {
                assert(((unsigned char)127) == ((char)127));
            }

            /* OK: to unsigned that cannot be represented wraps around. */
            {
                assert(((unsigned char)-1) == UCHAR_MAX);
            }

#ifdef IMPLEMENTATION_SIGNAL
            /*
            To signed is implementation defined, or implementation-defined signal.

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
    }

    /*
    # Overflow

        Overflow has two meanings:

        -   mathemtaical definition: making an operation in which the result
            is larger than the maximum value or smaller than the minimum value.

            This is the more common meaning of the term *overflow* outside of this context.

            In this section this will be called *mathematical overflow*.

            There is no automatic overflow check on operations
            except at initialization and assignment by constants
            at compile time.

            Operations that can overflow mathematically but never overflow include:

            - unsigned integer sum or multiplication

        -   flag definition: raising the overflow FLAG on a x86 processor or analogous.

            This is the meaning of overflow in the ANSI C definition.

            Therefore, in this section this will be called simply *overflow*.

            Overflow always implies undefined behaviour. This could include a program crash!

            Operations that may overflow include:

            - signed integer sum or multiplication

            Since this kind of overflow modifies an observable processor state,
            it is possible for compilers to detect this situation.

        Flag overflow always implies mathematical overflow, but not the converse.

        For instance, unsigned integer overflow never raises the overflow flag of an x86
        processor: it just wraps around.

        Therefore, unsigned integer multiplication never overflows.

        # GCC overflow specifics

            gcc 4.8 is smart enough to warn in many cases with `-Woverflow`:
            which is part of `-Wall`. We have turned it off so it wont annoy us on our tests.

            `-ftrapv` causes gcc to detect an overflow and raise a `SIGABRT`,
            this making their behaviour defined.
    */
    {
        /*
        Initialize with literal that does not fit into type

        TODO what happens?
        */
        {
            if (0) {
                /*unsigned char uc = UCHAR_MAX + 1;*/
                /*char c = 1e1000;*/
            }

            /* Floating point */
            {
                assert(1.00000000000000000000000000000000000000000000001 == 1.0);
            }
        }
    }

    /* # Command line arguments */
    {
        printf("argv[0] = %s\n", argv[0]);
        int i = 0;
        if (argc > i) {
            i++;
            printf("argv[%d] = %s\n", i, argv[0]);
        }
        if (argc > i) {
            i++;
            printf("argv[%d] = %s\n", i, argv[0]);
        }
    }

    /*
    # main return

        Valid returns are:

        - `EXIT_SUCCESS` or `0` to indicate success
        - `EXIT_FAILURE`        to indicate failure

        C99: return is optional. If omited a `return 0` is added to the program.

        But just always return to be C89 compatible.
    */
    {
        return EXIT_SUCCESS;
        return EXIT_FAILURE;
    }
}
