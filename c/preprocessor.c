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
# #include

    Look in standard dirs directly:

        #include <file.h>

    Looks in current directory first:

        #include "file.h"
*/
#include "common.h"

int int_int_int_func(int m, int n) {
    return m + n;
}

int main(void) {

    /*
    # Comments are replaced by spaces.
    */
    {
        int/* */a = 1;
        assert(a == 1);
    }

    /*
    # Newline in macro

    # Multiline macro

        Impossible:

        - http://stackoverflow.com/questions/10419530/multi-line-preprocessor-macros
        - http://stackoverflow.com/questions/98944/how-to-generate-a-newline-in-a-cpp-macro
    */

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
#define SPACE_AFTER_HASH 1
            assert(SPACE_AFTER_HASH == 1);
        }

        /*
        # Constants

            Use sparingly.

            - constants have scope
            - produce meaningful error messages
        */
        {
            {
#define CTE 1
                assert(CTE == 1);
            }

            /*
            Don't forget to protect arithmetic operations
            or associativity may get you.
            */
            {
/* Use parenthesis or order of operation might destroy you: */
#define PROTECT_FAIL 1 + 1
                assert(PROTECT_FAIL * 2 == 3);
#define PROTECT (1 + 1)
                assert(PROTECT * 2 == 4);
            }

            /*
            Expansion is lazy: macros do not expand in `#define`
            but only when the macro is used.
            */
            {
#define LAZY0 LAZY1
#define LAZY1 LAZY2
#define LAZY2 2
                assert(LAZY2 == 2);
            }
        }

        /* # Redefine macros */
        {
            /* Cannot redefine macros directly. */
            {
#define REDEFINE_FAIL 1
                /* ERROR */
/*#define REDEFINE_FAIL 2*/
            }

            /* Must first undef. */
            {
#define REDEFINE 1
#undef REDEFINE
#define REDEFINE 2
                assert(REDEFINE == 2);
            }
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
            # Comma protection

                The macro engine has to do some kind of parsing to determine that
                the comma of the function (1) is not the comma of the macro (2).

                What it seems to do is simply check if the comma is between pairs of:

                - parenthesis
                - double quotes

                and if yes ignore it.

                This does not however cover C++ template parameters, and `assert` + template is a common break case
                http://stackoverflow.com/questions/4496842/pass-method-with-template-arguments-to-a-macro

                Pure C also has cases in which it is necessary to use parenthesis,
                for example when the comma operator is used.

                A more complicated case in which protecting parenthesis break:
                http://stackoverflow.com/questions/9187614/how-do-i-have-a-comma-inside-braces-inside-a-macro-argument-when-parentheses-cau
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
                /* Strings are treated as a single token, so commas inside strings are fine. */
                assert(strcmp(CAT("1,", "2"), "1,2") == 0);
            }

            /*
            # Function inside argument

                - http://stackoverflow.com/questions/163365/how-do-i-make-a-c-macro-behave-like-a-function
                - http://stackoverflow.com/questions/154136/do-while-and-if-else-statements-in-c-c-macros
            */
            {
                /* TODO */
            }

            /*
            # Argument inside string

            # #
            */
            {
                /* Strings are treated as single tokens, so arguments don't expand by default. */
#define ARG_IN_STRING_BAD(x) "x"
                assert(strcmp(ARG_IN_STRING_BAD("a"), "x") == 0);

                /*
                Solution: use # stringification.

                It simply adds "" around the argument and expands it.
                */
#define STRINGIFY(x) #x
                assert(strcmp(STRINGIFY(a), "a") == 0);
                assert(strcmp(STRINGIFY(""), "\"\"") == 0);
                /* ERROR: parsing fails because of unbalanced `"`. */
                /*assert(strcmp(STRINGIFY("), "\"") == 0);*/

#define STRINGIFY_CAT(x) "a" STRINGIFY(x) "c"
                assert(strcmp(STRINGIFY_CAT(b), "abc") == 0);

                /*
                This fails however for macro arguments, which don't expand when `# arg` is used!

                Solution Use a two step expansion process...

                - http://stackoverflow.com/questions/8283596/whats-the-difference-between-these-two-macros?lq=1
                - http://stackoverflow.com/questions/6742501/whats-the-exact-step-of-macro-expanding

                TODO what is the rationale for that exception of not expanding upon `#`?
                */
#define STRINGIFY_ARG a
                assert(strcmp(STRINGIFY(STRINGIFY_ARG), "STRINGIFY_ARG") == 0);
            }

            /* # variadic macro functions */
            {
                char s[4];
#define SPRINTF(string, format, ...) sprintf(string, format, __VA_ARGS__)
                SPRINTF(s, "%c%c", 'a', 'b');
                assert(strcmp(s, "ab") == 0);
            }

#if __STDC_VERSION__ >= 199901L
            /*
            # Empty macro arguments

                http://stackoverflow.com/questions/7666344/are-empty-macro-arguments-legal-in-c11
            */
            {
#define EMPTY(x) x ## 2 ==
                assert(EMPTY(1) 12);

                /*
                TODO if the argument is empty,
                does it still count for concatenation?
                */
                assert(EMPTY() 2);
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
# error
#endif
    }

    /*
    # Concatenate

    # Double hash preprocessor operator

    # ##

        `##` allows to concatenate a preprocessor function arguments without spaces between them.
    */
    {
        /* Basic. */
        {
#define CAT_NO_SPACE(x) x ## d
            int CAT_NO_SPACE(c_) = 1;
            assert(c_d == 1);
        }

        /*
        Multiple concatenation insanity:
        http://stackoverflow.com/questions/1489932/c-preprocessor-and-concatenation
        */
        {
            {
#define CAT_FAIL_VAR 0
#define CAT_FAIL x ## CAT_FAIL_VAR
                int CAT_FAIL = 1;
                assert(xCAT_FAIL_VAR == 1);
            }

            /* Solution. */
            {
#define CAT_VAR 0
#define PASTER(x,y) x ## y
#define EVALUATOR(x,y) PASTER(x,y)
#define CAT_OK EVALUATOR(x, CAT_VAR)
                int CAT_OK = 1;
                assert(x0 == 1);
            }
        }
    }

    /*
    # #ifdef

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

    # #ifndef

        Negation of ifdef.

    # #defined

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
# error
#elif 1 == 1
#else
# error
#endif

#define INIF 1
#if INIF + 1 == 2
#else
# error
#endif

#if 16 == 0x10
#else
# error
#endif

        /* Undefined evaluate equal. */
        {
#if NOT_DEFINED == NOT_DEFINED2
#else
# error
#endif
        }

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
# error
#endif
    }

    /*
    # && preprocessor

    # and preprocessor
    */
#define C 1
#if defined(C) && C > 0
#else
# error
#endif

    /*
    # #error

        Print an error message to stderr and stop compilation.

        Useful to enforce preprocessor conditions.
    */
    {
/* #error "the error message" */
    }

    /*
    # null directive

        A `#` followed by newline is ignored.
    */
    {
#
    }

    /*
    # #pragma

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
    # #line

        Set the line and optionally filename that is seen by `__FILE__` and `__LINE__`.
    */
    {
/*#line 1*/
    }

    /*
    # Predefined preprocessor macros

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
        # STDC_VERSION

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

            C99 says that C must not define it.
        */
#ifdef __cplusplus
        printf("__cplusplus\n");
#endif

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

    /*
    # IEEE-754

        IEC 60559 has the same contents as the IEEE 754-2008,
        Outside of the C standard it is commonly known by the IEEE name, or simply as IEEE floating point.

        IEEE dates from 1985.

    # __STDC_IEC_559__

    # IEC 60599

        Standard on which floating point formats and operations should be available
        on an implementation, and how they should work.

        Good overview wiki article: <http://en.wikipedia.org/wiki/IEEE_floating_point>

        Many CUPs implement large parts of IEC 60599, which C implementations can use if available.

        The C standard specifies that implementing the IEC 60599 is not mandatory.

        If the macro `__STDC_IEC_559__` is defined this means that the implementation is compliant
        to the interface specified in Annex F of the C11 standard.

        C99 introduced many features which allow greater conformance to IEC 60599.
    */
        {
#ifdef __STDC_IEC_559__
            puts("__STDC_IEC_559__");

            /*
            I think it guaranteed by the standard on annex F:

            - The float type matches the IEC 60559 single format.
            - The double type matches the IEC 60559 double format.
            - The long double type matches an IEC 60559 extended format,307) else a
              non-IEC 60559 extended format, else the IEC 60559 double format.
            */
            assert(sizeof(float) == 4);
            assert(sizeof(double) == 8);
#endif
        }

        /*
        # Expand macro to another macro

            Nope:
            http://stackoverflow.com/questions/1262063/preprocessor-macro-expansion-to-another-preprocessor-directive
        */

#ifndef __STDC_NO_ATOMICS__
        /* Indicates no C11 support for `_Atomic` and `<stdatomic.h>`. */
        puts("__STDC_NO_ATOMICS__");
#else
#include <stdatomic.h>
        _Atomic int i;
#endif
    }

    return EXIT_SUCCESS;
}
