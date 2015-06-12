/*
# preprocessor

# macros

# cpp

    TODO being converted to cpp.sh clearly separate the C aspect from the cpp

    Does simple operations before compilation:
    it is a completely separate step that happens before compilation.

    Not Turing complete.

    Executable name: cpp. GCC for example is just a front-end to it.
*/

/*
# include

    Look in standard dirs directly:

        #include <file.h>

    Looks in current directory first:

        #include "file.h"
*/

#include "common.h"

int int_int_int_func(int m, int n) {
    return m + n;
}

int main() {
    /*
    # #define

        You can put preprocessor directives anywhere
        but putting on global scope is the more standard and simple approach

        Use defines with discretion: they make it much harder to debug!
    */
    {

        /*
        Syntax: the line must start with `#`,
        but there can be spaces after it to give indentation.
        */
        {
#           define SPACE_AFTER_HASH 1
            assert(SPACE_AFTER_HASH == 1);
        }

        /* Constants. */
        {
#define A B
#define B 1
            assert(A == 1);
        }

        /* Cannot redefine macros. */
        {
/* # define A 1 */
/* # define A 2 */
            /*assert(A == 2);*/
        }

        /* Undefined evaluate equal. */
        {
#if NOT_DEFINED == NOT_DEFINED2
#else
        assert(false);
#endif
        }

        /* # Functions (preprocessor) */
        {
            /*
            Generates:

                assert(1 + 1 == 2);

            Not:

                assert(2 == 2);
            */
            {
#define SUM(x, y) x + y
                assert(SUM(1, 1) == 2);
            }

            /*
            # macro comma protection

                The macro engine has to do some kind of parsing to determine that
                the comma of the function (1) is not the comma of the macro (2).

                What it seems to do is simply check if the comma is between pairs of:

                - parenthesis
                - double quotes

                and if yes ignore it.

                This does not however cover C++ template parameters, and `assert` + template is a common break case
                <http://stackoverflow.com/questions/4496842/pass-method-with-template-arguments-to-a-macro>

                Pure C also has cases in which it is necessary to use parenthesis, for exapmle when the comma operator is used.

                A more complicated case in which protecting parenthesis break:
                <http://stackoverflow.com/questions/9187614/how-do-i-have-a-comma-inside-braces-inside-a-macro-argument-when-parentheses-cau>
            */
            {
                assert(SUM(int_int_int_func(1, 1), 1) == 3);
                /*                           ^   ^ */
                /*                           1   2 */

                int i = 1;
                assert(SUM((i++, i), 1) == 3);
                /*                 ^ */
                /*                 comma operator */

                /* ERROR must protect the comma operator. */
                /*assert(SUM(i++, i, 1) == 3);*/

#define CAT(x, y) x y
                /* Strings are treated as a sigle token, so commas inside strings are fine. */
                assert(strcmp(CAT("1,", "2"), "1,2") == 0);
                /*                     ^ ^ */
                /*                     1 2 */
            }

            assert(SUM(int_int_int_func(1, 1), 1) == 3);

#if __STDC_VERSION__ >= 199901L

            /* # variadic macro functions */
            {
                char s[4];
#define SPRINTF(string, format, ...) sprintf(string, format, __VA_ARGS__)
                SPRINTF(s, "%c%c", 'a', 'b');
                assert(strcmp(s, "ab") == 0);
            }

            /*
            # Stringfication
            */
            {
            }
#endif
        }

        /*
        # #include

            It is possible, and very confusing, to include any type of file,
            not just header files.
        */
        {
            int i = 0;
#include "preprocessor.inc"
            assert(i == 1);
        }
    }

    /*
    # #undef

        Undo a previous define.
    */
    {
#define UNDEF_TEST 1
#undef UNDEF_TEST
#ifdef UNDEF_TEST
        assert(false);
#endif
    }

    /*
    # Concatenate

    # Double hash preprocessor operator

    # ##

        `##` allows to concatenate two preprocessor function arguments without spaces between them.
    */
    {
        /* Basic. */
        {
#define CAT_NO_SPACE(x, y) x ## y
            int CAT_NO_SPACE(c_, d) = 1;
            assert(c_d == 1);
        }

        /*
        Preprocessor variable gotcha:
        http://stackoverflow.com/questions/1489932/c-preprocessor-and-concatenation
        */
        {
            {
#define VAR 3
#define CAT_VAR_FAIL(x) x ## _ ## VAR
                int CAT_VAR_FAIL(b) = 1;
                assert(b_VAR == 1);
            }

            /* Solution. */
            {
#define VAR 3
#define PASTER(x,y) x ## _ ## y
#define EVALUATOR(x,y) PASTER(x,y)
#define CAT_VAR(x) EVALUATOR(x, VAR)
                int CAT_VAR(b) = 1;
                assert(b_3 == 1);
            }
        }
    }

    /*
    # ifdef

        Check if preprocessor variable is defined.

        # or and ifdef

            http://stackoverflow.com/questions/965700/c-preprocessor-testing-definedness-of-multiple-macros

            Almost the same as `#if defined()`,
            except you can use `#if defined()` with `|| on a single line as:

                #if defined(X) || defined(Y)

            while

                #ifdef(X) || ifdef(Y)
                #ifdef X || Y

            compiles but does not do what you expect:
            TODO legal?

            For `&&`, we could get away with:

                #ifdef(X)
                #ifdef(Y)

            but there is no alternative for `||`.

    # ifndef

        Negation of ifdef.

    # defined

        Like ifdef, but more flexible
        as you can use it inside `#if` with boolean operators.
    */
    {
#ifdef COMMANDLINE
        /* gcc -DCOMMANDLINE c.c */
        puts("C");
#else
        /* gcc c.c */
        puts("no C");
#endif
    }

/*
# #if

# #else

# #elif

    The preprocessor can do certain integer arithmetic operations such as: +, -, ==, <.
*/
{
#if 1 == 0
assert(false);
#elif 1 == 1
#else
assert(false);
#endif

#define INIF 1
#if INIF + 1 == 2
#else
        assert(false);
#endif

#if 16 == 0x10
#else
        assert(false);
#endif

/*
Cannot compare strings directly!
http://stackoverflow.com/questions/2335888/how-to-compare-string-in-c-conditional-preprocessor-directives
Always define to integers.
*/
#define STR1 1
#define STR2 2
#define STR STR1

#if STR == STR1
#elif STR == STR2
        assert(false);
#endif
}

    /*
    # && preprocessor

    # and preprocessor
    */
#define C 1
#if defined(C) && C > 0
#else
assert(false);
#endif

    /*
    # #error

        Print an error message to stderr and stop compilation.

        Useful to enforce preprocessor conditions.
    */
    {
/* # error "the error message" */
    }

    /*
    # null directive

        A `#` followed by newline is ignored.
    */
    {
#
    }

    /*
    # pragma

        C99 specifies that:

            # pragma X Y Z ...

        -   if `X != STDC`, does something implementation defined, and therefore not portable.

            Examples: `#pragma once`

        -   else, then the statement must take a form:

                # pragma STDC FP_CONTRACT on-off-switch
                # pragma STDC FENV_ACCESS on-off-switch
                # pragma STDC CX_LIMITED_RANGE on-off-switch

            all of which are portable.
    */

    /*
    # Prefined preprocessor macros

    # Standard preprocessor defines

        Some preprocessor vars are automatically defined by certain compilers
        although they are not c standards. Those are not discussed here.

        List of standard defines: http://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html

        List all them on GCC:

            gcc -dM -E - < /dev/null | sort

        Sample output:

            #define _LP64 1
            #define _STDC_PREDEF_H 1
            #define __ATOMIC_ACQUIRE 2
            #define __ATOMIC_ACQ_REL 4
            #define __ATOMIC_CONSUME 1
            #define __ATOMIC_HLE_ACQUIRE 65536
            #define __ATOMIC_HLE_RELEASE 131072
            #define __ATOMIC_RELAXED 0
            #define __ATOMIC_RELEASE 3
            #define __ATOMIC_SEQ_CST 5
    */
    {
        /*
        # STDC_VERSION__

        # __STDC_VERSION__

            String representing version of the c std lib. Format: yyyymm (base 10).

            Some values:

            - C11: 201112L
            - C99: 199901L

            http://sourceforge.net/p/predef/wiki/Standards/

            Apperas undefined in C99
        */
        {
            printf("__STDC_VERSION__ = %li\n", __STDC_VERSION__);
        }

        /*
        # __stdc__

        # stdc

            1 if the implementation is conforming, 0 otherwise.

            TODO check: on GCC, 1 with `-std=cXX`, 0 with `-std=gnuXX`.
        */
        {
            printf("__STDC__ = %d\n", __STDC__);
        }

        /*
        # __STDC__

        # STDC

            1 if the implementation is conforming, 0 otherwise.

            TODO check: on GCC, 1 with `-std=cXX`, 0 with `-std=gnuXX`.
        */
        {
            printf("__STDC__ = %d\n", __STDC__);
        }

        /*
        # __STDC_HOSTED__

        # STDC

            Indicate if the compilation is hosted or not.

        # Hosted

        # Freestanding

            Concept defined in ANSI C.

            Basically, a freestanding implementation does not need to provide an stdlib.

            In GCC, controlled by the `-ffreestainding` option.
        */
        {
            printf("__STDC_HOSTED__ = %d\n", __STDC_HOSTED__);
        }


        /*
        # __cplusplus

            Defined only if using C++ compiler.
        */
#ifdef __cplusplus
        printf("__cplusplus\n");
#endif

        /*
        # line

        # #line

            Set the line and optionally filename that is seen by `__FILE__` and `__LINE__`.
        */
/*#line 1*/


        /*
        # __FILE__

            Absolute or relative path of current file.
        */
        {
            printf("__FILE__ = %s\n", __FILE__);
        }

        /*
        # __LINE__

            Current source code line.

            Useful for debugging.

            If in a `.h`, position inside the `.h` before inclusion.
        */
        {
            printf("__LINE__ = %d\n", __LINE__);
        }

        printf("__DATE__ = %s\n", __DATE__);

        printf("__TIME__ = %s\n", __TIME__);

#ifdef __WIN32__
        /* Automatically defined by certain compilers on windows: */
        /* TODO gcc specific or not? if yes move out of here. */
        puts("__WIN32__");
#endif

#ifdef _LIBC
        /* TODO what is this */
        /* TODO gcc specific or not? if yes move out of here. */
        puts("_LIBC");
#endif

#ifdef __ILP32__
        /* TODO what is this */
        /* TODO gcc specific or not? if yes move out of here. */
        puts("__ILP32__");
#endif

#ifdef ___X32_SYSCALL_BIT
        /* TODO what is this */
        /* TODO gcc specific or not? if yes move out of here. */
        puts("___X32_SYSCALL_BIT");
#endif

    }

    return EXIT_SUCCESS;
}
