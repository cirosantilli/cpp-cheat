/*
# Attribute

    https://gcc.gnu.org/onlinedocs/gcc/Attribute-Syntax.html#Attribute-Syntax

    Specifies special attributes of functions or data.

    There are three types of attributes:

    - functions: http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
    - variables: http://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html#Variable-Attributes
    - types: http://gcc.gnu.org/onlinedocs/gcc/Type-Attributes.html#Type-Attributes

    Can be used to:

    -   do error checking at compile time that would not be possible otherwise:

        - format
        - noreturn

    -   control certain aspects of low level assembly code output.

        For example, `aligned` controls data alignment on the text section.

    -   help the compiler optimize by giving it extra information:

        - const
        - hot

    C++11 specifies a standard syntax for attributes:

        int [[attr1]] i [[attr2, attr3]];

        [[attr4(arg1, arg2)]] if (cond) {
            [[vendor::attr5]] return i;
        }

    and two attributes; `noreturn` and `carries_dependency`.

# Multiple attributes

    Two syntaxes:

        extern void die(const char *format, ...)
            __attribute__((noreturn))
            __attribute__((format(printf, 1, 2)));

    or:

        extern void die(const char *format, ...)
            __attribute__((noreturn, format(printf, 1, 2)));

# Reason for double parenthesis

# Eliminating __attribute__ on non-GNU projects

    http://stackoverflow.com/questions/7345346/why-does-gccs-attribute-syntax-use-double-parentheses

    This is really easy:

        #ifndef __GNUC__
        #  define  __attribute__(x)
        #endif

    This only work because attributes can only take a single argument: `(...)`.

# Alternative syntax

    Add prefix and suffix `__` to keywords and dispense `__attribute__`. Ex:

        __noreturn__
*/

#include <assert.h> /* assert */
#include <stdarg.h> /* ..., va_list, va_start, va_arg, va_end */
#include <stdio.h> /* puts, printf */
#include <stdlib.h> /* EXIT_SUCCESS */

char not_aligned16 = 0;
char aligned16 __attribute__ ((aligned (16))) = 0;

/* Format */

    int sprintf_wrapper(char *s, int useless, const char *fmt, int useless2, ...) {
        int ret;
        va_list args;
        va_start(args, useless2);
        ret = vsprintf(s, fmt, args);
        va_end(args);
        return ret;
    }

    /*
    3 says: the 3rd argument is the format string
    5 says: the va_list starts at the 5th argument

    Declaration and definition *must* be separated.
    */
    int sprintf_wrapper_attr(char *s, int useless, const char *fmt, int useless2, ...)
        __attribute__((format(printf, 3, 5)));

    int sprintf_wrapper_attr(char *s, int useless, const char *fmt, int useless2, ...) {
        int ret;
        va_list args;

        va_start(args, useless2);
        ret = vsprintf(s, fmt, args);
        va_end(args);
        return ret;
    }

/* Deprecated */

    void func_deprecated() __attribute__((deprecated));

    void func_deprecated(){}

/* Used */

    void func_used() __attribute__((used));

    void func_used(){}

    void func_not_used(){}

/* warn_unused_result */

    int func_warn_unused_result() __attribute__((warn_unused_result));
    int func_warn_unused_result(){ return 0; }
    int func_not_warn_unused_result(){ return 0; }

/*
# noreturn

    It is possible that the function makes the program exit and therefore does not return.

    Makes compiler ommit "possible no return" warnings.

    Used on glibc exit and abort:

        extern void exit(int)   __attribute__((noreturn));
        extern void abort(void) __attribute__((noreturn));
*/

    void exitnow() {
        exit(EXIT_SUCCESS);
    }

    /* WARNING: control reaches end of non void function */
    /*
    int noreturn_possible(int n) {
        if (n > 0)
            exitnow();
        else
            return 0;
    }
    */

    void exitnow_attr() __attribute__((noreturn));

    void exitnow_attr() {
        exit(EXIT_SUCCESS);
    }

    int noreturn_possible_attr(int n) {
        if (n > 0)
            exitnow_attr();
        else
            return 0;
    }

    /*
    Does not emmit a warning because the libc exit has the `noreturn` attribute.
    */
    int noreturn_possible_exit(int n) {
        if (n > 0)
            exit(EXIT_SUCCESS);
        else
            return 0;
    }

/* const */

    int next(int cur) {
        return cur + 1;
    }

    int next_const(int cur) __attribute__((const));

    int next_const(int cur) {
        return cur + 1;
    }

/* Always inline */

    /* Declaration must also be `inline`. */
    inline int incr_always_inline(int i) __attribute__((always_inline));
    inline int incr_always_inline(int i){ return i + 1; }

    int incr_inline(int i);
    inline int incr_inline(int i){ return i + 1; }

    int incr(int i){ return i + 1; }

/* alias */

    int func_alias_orig() { return 1; }
    int func_alias() __attribute__((alias("func_alias_orig")));

/*
# variable attributes

    Attributes that apply to individual variables.
*/

    /*
    # section

        Put *initilized* data on an arbitrary new section.

        Cannot be used for uninitialized data.

        Arbitrary sections may not be supported on all output formats. ELF at least supports them.

        Applications:

        -   Linux kernel `__initdata` puts declarations on a special section which is removed at the end of initialization,
            reclaiming otherwise wasted text space.

        Result on GCC 4.7 i386:

        -   generated gas contains `.section` directives:

            .section        newsection1,"aw",@progbits

        -   `readelf -a | grep newsec` shows that those two sections exist on the ELF:

            [25] newsection1       PROGBITS        0804a034 001034 000004 00  WA  0   0  4
            [26] newsection2       PROGBITS        0804a038 001038 000004 00  WA  0   0  4
    */

        int __attribute__((section("newsection1"))) newsection1_var = 1;
        int __attribute__((section("newsection2"))) newsection2_var = 2;


int main() {
    /*
    # Function attributes

        https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
    */
    {
        /*
        # format

            If this is used, gcc can check if printf format strings are correct because of the use of attributes,
            and emmit errors otherwise.
        */
        {
            char s[32];
            sprintf_wrapper(s, 0, "%c", 0, 'a');
            assert(s[0] == 'a');

            sprintf_wrapper_attr(s, 0, "%c", 0, 'b');
            assert(s[0] == 'b');

            /*
            With `__attribute__((format,X,Y))` the compile time error checking gets done.
            */
            {
                /* Compile error check not done. */
                /* Could segfault at runtime. */
                if (0) {
                    sprintf_wrapper(s, 0, "%s", 0);
                }

                /* Compile error check is done. */
                {
                    /*sprintf_wrapper_attr(s, 0, "%s", 0);*/
                }
            }
        }

        /*
        # deprecated

            Using a function marked as deprecated will emmit warnings.
        */
        {
            /*func_deprecated();*/
        }

        /*
        # used

            Useful when the function may be called from assembly code, in which case GCC
            may not be easily able to detect that it was called.

            TODO0 what is this for? If a func is not called, what does gcc do? Remove it from text?
        */
        {
        }

        /*
        # warn_unused_result

            Always emmit a warning if the return value is not used.

            Useful to enforce callers to do error checks when the return value signals the error.
        */
        {
            /* No warning. */
            func_not_warn_unused_result();

            assert(func_warn_unused_result() == 0);

            /* WARNING ignored return value */

                /*func_warn_unused_result();*/
        }

        /*
        # const

            A function marked const may be optimized in the sense that the compiler calculates its value at compile time,
            or chaches its result of each calculation.

            A function can only be marked const if:

            - its return value is only a function of its arguments, and not of any global or static function variable
            - the function has no desired side effect besides returning the value

            Marking a function which does one of the above const will lead to serious hard to find bugs.
        */
        {
            assert(next(0) == 1);
            assert(next(0) == 1);
            assert(next_const(0) == 1);
            assert(next_const(0) == 1);
        }

        /*
        # always_inline

            Always inline the function.

            ANSI C99 `inline` does not guarantee that, it only hints it to the compiler.

            Must see generated assembly code to notice this (except for the possible desired speedup effect).

            On `gcc -O0 4.7`, only the `incr_always_inline` was inlined.
        */
        {
            int i = 0;
            i = incr(i);
            i = incr_inline(i);
            i = incr_always_inline(i);
        }

        /*
        # alias

            GCC simply makes a copy of the function.

            This could be replicated with:

            - inline functions
            - macros

            to avoid a trivial forwarding call, but this solution is nicer.

            http://blog.omega-prime.co.uk/?p=121

            The most common applicaiton is to make weak aliases of type:

                int __func() { return 1; }
                int func() __attribute__((weak, alias("__func")));

            to allow overriding the symbol on the program that use the library,
            while still maintaining the original symbol visible.
        */
        {
            assert(func_alias() == 1);
            assert(func_alias_orig() == 1);
        }
    }

    /*
    # Variable attributes
    */
    {
        /*
        # aligned

            Aligns variables on X bit lines.

            This may be required for certain processor specific functions, in particular SIMD operations.

            The generated gas assembly code should mark this alignment with the `.align` directive.

            http://stackoverflow.com/questions/381244/purpose-of-memory-alignment

            C11 has aligned_alloc:

			- http://stackoverflow.com/questions/227897/how-to-allocate-aligned-memory-only-using-the-standard-library
			- http://stackoverflow.com/questions/3839922/aligned-malloc-in-gcc

			Assume that function argument pointer is aligned:
			http://stackoverflow.com/questions/9608171/how-to-tell-gcc-that-a-pointer-argument-is-always-double-word-aligned

			TODO does it work for stack variables?
			http://stackoverflow.com/questions/841433/are-stack-variables-aligned-by-the-gcc-attribute-alignedx
        */
        {
            assert(aligned16 == 0);
            assert(not_aligned16 == 0);
        }

        /*
        # packed

            Chars in structs are normally put on 32 bit lines to speed up retrieval.

            This however makes the struct larger than necessary, since a struct with
            2 chars then takes 8 bytes instead of 2.

            Packed prevents this and puts the chars side by side.
        */
        {
            struct not_packed {
                char c1;
                char c2;
            };
            struct not_packed not_packed = {0, 1};
            assert(sizeof(not_packed) >= 2 * sizeof(char));

            struct packed {
                char c1;
                char c2;
            } __attribute__((packed));
            struct packed packed = {0, 1};
            assert(sizeof(packed) == 2 * sizeof(char));
        }
    }

    /*
    # Type attributes

        Attribute that applies to all objects of a newly created user type.

        Syntax is as:

            struct S { int i } __attribute__((aligned (8)));
            typedef int more_aligned_int __attribute__((aligned (8)));
    */
    {
        /*
        # Vector extensions

            GCC built-ins for vectorized SIMD operations.

            http://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html

            Allowed operators: +, -, *, /, unary minus, ^, |, &, ~, %, ==, !=, <, <=, >, >=

        # vector_size
        */
        {
            typedef int v4si __attribute__ ((vector_size (16)));

            /* Create */
            {
                v4si v = {0, 1, 2, 3};
            }

            /* Access */
            {
                v4si v = {0, 1, 2, 3};
                assert(v[0] == 0);
                assert(v[1] == 1);
            }

            /* Operations */
            {
                v4si v = {0, 1, 2, 3};
                v4si v2 = {0, 1, 2, 3};
                v4si res;

                res = v + v2;
                assert(res[0] == 0);
                assert(res[1] == 2);
                assert(res[2] == 4);

                res = v * v2;
                assert(res[0] == 0);
                assert(res[1] == 1);
                assert(res[2] == 4);
            }
        }
    }

    return EXIT_SUCCESS;
}
