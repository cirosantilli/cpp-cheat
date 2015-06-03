#include <assert.h> /* assert */
#include <complex.h> /* Complex integer types. */
#include <inttypes.h> /* intmax_t */
#include <math.h>
#include <stdarg.h> /* ..., va_list, va_start, va_arg, va_end */
#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS */
#include <string.h>

int nested() {
    return 0;
}

/* Do some random operations to try and get the cache dirty. */
void get_cache_dirty() {
    int i;
    int is[1024];
    for (i = 0; i < 1024; i++)
        is[i] = 1;
    assert(is[0] == 1);
}

int main();

void builtin_return_address_test() {
    /*
    - 0 means for current function
    - 1 for the parent of current function
    - etc.
    */
    printf("main                        = %p\n", main);
    printf("__builtin_return_address(0) = %p\n", __builtin_return_address(0));
    return;
}

int main() {

    /* # Identifiers */
    {
        /*
        # $ is legal in identifiers

            In Java and JavaScript too.
        */
        {
            int $ = 0;
            assert($ == 0);
        }
    }

    /* # Literals */
    {
        /*
        # Binary int literals

            start with `0b`:
        */
        {
            assert(0b10000 == 16);
        }

        /*
        # D double specifier

            Java also allows it, but Java also allows 1D which is more useful.
        */
        {
            assert(1.2D == 1.2);
        }

        /*
        # String

        # \e

            Esc escape character. Useful for the ANSI escape sequences,
            and in particular terminal coloring.
        */
        {
            assert(((int)'\e') == 27);
        }
    }

    /* Types. */
    {
        /*
        # Complex integer.

            C99 has floating point complex numbers, but no integer complex numbers.
        */
        {
            int complex z = 1 + 1*I;
            int complex z2 = 1 - 1*I;
            assert(z + z2 == 2  );
        }

        /*
        # 128 bit integer

        # int128

        # __int128

            https://gcc.gnu.org/onlinedocs/gcc-5.1.0/gcc/_005f_005fint128.html

            Where it is supported:

            - http://stackoverflow.com/questions/3329541/does-gcc-support-128-bit-int-on-amd64
            - http://stackoverflow.com/questions/21886985/what-gcc-versions-support-the-int128-intrinsic-type
        */
        {
            unsigned __int128 i = (unsigned __int128)1 << 127;
            /* TODO: why does this fail? */
            /*assert(i + 1 == 0);*/
            printf("__int128 max + 1 = %ju\n", (uintmax_t)i + 1U);
            printf("sizeof(long long) = %zu\n", sizeof(long long));
            printf("sizeof(__int128) = %zu\n", sizeof(__int128));

            /*
            # __int128_t

                TODO vs __int128?
            */
            {
                __int128_t i;
            }

            /*
            How to printf __int128:

            http://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc

            `%ju` not possible because `intmax_t` does not currently consider `__int128`:

            - http://stackoverflow.com/a/11658831/895245
            - http://stackoverflow.com/questions/21265462/why-in-g-stdintmax-t-is-not-a-int128-t

            Seems that the answer is that it is not well implemented
            enough to replace the standard's `intmax_t`.
            */
            {
                printf("sizeof(intmax_t) = %zu\n", sizeof(intmax_t));
            }
        }

        /*
        # Zero length arrays

            TODO0 application?
        */
        {
            int is[0];
            int i;
            printf("&is[0] = %p\n", &is[0]);
            printf("&i     = %p\n", &i);
        }

        /* # Empty struct */
        {
            struct s {};
            struct s s0;
            assert(sizeof(s0) == 0);
        }
    }

    /*
    # Nested function

         Is a function defined inside another function (the outter function here is `main`)

         This is not a redefinition because it is inside a parenthesis block
         much like a variable definition inside a parenthesis block.
    */
    {
        int nested() {
            return 1;
        }

        {
            int nested() {
                return 2;
            }

            /* This would cause a redefinition error: */

                /*
                int nested() {
                    return 2;
                }
                */

            /* Like variable redefinitions, the nested version overrides all external version */
            /* which have become completelly innacessible */

            assert(nested() == 2);
        }
    }

    /*
    # local labels

    # __label__

        https://gcc.gnu.org/onlinedocs/gcc/Local-Labels.html
    */
    {
        /* TODO */
    }

    /*
    # Predefined macros

    # Preprocessor defines

        Full list: http://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros

        View all macros that would be automatically defined:

            cpp -dM /dev/null

        TODO there are some missing! where is `__i386__` documented for example?
    */

    /*
    # Version numbers

        `__GNUC__`           : major
        `__GNUC_MINOR__`     : minor
        `__GNUC_PATCHLEVEL__`: patch

        http://stackoverflow.com/questions/259248/how-do-i-test-the-current-version-of-gcc

        There is also:

            __GNUC_PREREQ(4,8)

        to test versions more conveniently than:

            #if defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 8

        in `<features.h>`.

    # Detect if in GCC

        #ifdef __GNUC__ is a good common way.
    */
    {
#ifdef __GNUC__
        printf("__GUNC__       = %d\n", __GNUC__);
        printf("__GUNC_MINOR__ = %d\n", __GNUC_MINOR__);
        printf("__GUNC_PATCH   = %d\n", __GNUC_PATCHLEVEL__);
#endif

        /*
        Automatically defined if the compiler is told to use strict ansi c features and no extensions
        this is triggered by options such as `-std=c99` or `-ansi`.

        Don't be surprised if this does not appear when compiling this file
        since strict ansi compliance would mean other features of this file would need
        to be broken such as nested functions.
        */

#ifdef __STRICT_ANSI__
        puts("__STRICT_ANSI__");
#endif

        /*
        # Architecture detection macro

            http://stackoverflow.com/questions/152016/detecting-cpu-architecture-compile-time

            GCC defines architecture macros TODO where?

            Seems to use the list: http://sourceforge.net/p/predef/wiki/Architectures/
        */

#ifdef __i386__
        puts("__i386__");
#elif __x86_64__
        puts("__x86_64__");
#endif

        /*
        # OS detection macro

            http://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive

            Same riddle as architecture detection.
        */

#ifdef __linux__
        puts("__linux__");
#endif
    }

    /*
    # Assembly

    # Inline assembly

    # asm

        Great intro: http://www.ibm.com/developerworks/library/l-ia/index.html

        Can be used if you really, really want to optimize at the cost of:

        - architecture dependance
        - tying you to gcc

        If you use this, do it like the linux kernel and separate different architecture
        code in different dirs.

        General syntax:

            asm (
                "movl %1, %%eax;"   //commands string
                "movl %%eax, %0;"
                : "=X" (y),   //outputs
                  "=X" (z)
                : "X" (x)    //inputs
                : "X" (x)
                : "%eax"     //clobbered registers
            );

        where:

        -   commands: actual gas code into a single c string. Remember: each command has to end in newline or `;`.

        -   outputs: start with `=`. gcc has to enforce is that at the end of the `asm` block that those values are set.

        -   inputs:

        -   clobbered registers:

            Registers that may be modified explicitly in the assembly code.

            Normally, users have no direct access to registers,
            so gcc is free to optimize by leaving values in those registers for later use.

            This tells gcc not to leave values in the listed since those may be modified.

            E.g.:

                mov $0, %eax

            Clearly clobbers eax, so you would need to list eax in the clobber list.

            Note that certain instructions clobber registers
            even if they are not explicitly written in the code.

        Both inputs and outputs are constrats. `X` will indicate the constraint type

        TODO: # __asm__ vs asm
        TODO: # asmlinkage
        TODO: # asm volatile
    */
    {
        /*
        Examples of inline assembly in i386

        This is the main place for contains more comments and explanations
        if other archs are also exemplified
        */

#if defined(__i386__) || defined(__x86_64__)
        /*
        # m constraint

            Instructs gcc to store keep value of given expressions into RAM.

            This is the most basic way to get/set values of c variables in assembly code.
        */
        {
            int in = 1;
            int out = 0;
            /*out = in*/
            asm volatile (
                "movl %1, %%eax;"
                "movl %%eax, %0"
                : "=m" (out)
                : "m" (in)
                : "%eax"      /* eax will be modified, so we have to list it in the clobber list */
            );
            assert(out == 1);
        }

        /* No input. */
        {
            int out = 0;
            /*out = 1*/
            asm volatile (
                "movl $1, %0"
                : "=m" (out)
            );
            assert(out == 1);
        }

        /* Simple example using floats */
        {
            float in = 1.0;
            float out = 0.0;
            /*out = -in*/
            asm volatile (
                "flds %1;"
                "fchs;"
                "fstps %0;"
                : "=m" (out)
                : "m" (in)
            );
            assert(out == -1.0);
        }

        /* Input and ouput can be the same memory location. */
        {
            float x = 1.0;
            /*x = -x*/
            asm (
                "flds %1;"
                "fchs;"
                "fstps %0;"
                : "=m" (x)
                : "m" (x)
            );
            assert(x == -1.0);
        }

        /*
        # register constraints

            tell gcc to automatically read memory into registers or write registers into memory

            this is more precise and complicated than using `m`

            - r: gcc chooses any free register
            - a: %eax
            - b: %ebx
            - c: %ecx
            - d: %edx
            - S: %esi
            - D: %edi
            - 0: matching register
        */

        /*
        # r register constraint

            gcc will automatically put the value of `in` from ram into a register for us
            and `out` from a register into ram at the end

            note how we can do an `inc` operation directly on `%1` and `%0`
            so they must both already be inside a registers as expected

            gcc just makes sure they are writen from/to memory before/after the operations
        */
        {
            int in = 0;
            int out = 0;
            /*out = in + 2*/
            asm (
                "incl %1;"
                "movl %1, %0;"
                "incl %0;"
                : "=r" (out)
                : "r" (in)
            );
            assert(out == 2);
        }

        /*
        # matching constraint

            Represented by digits.

            Specifies that an input/output has the same constraint as another one.

            Often used when we want a single variable to be both input and output
            and minimize the use of new registers.
        */
        {
            volatile int x = 0;
            asm (
                "incl %0"
                : "=r" (x)
                : "0" (x) /* x has the same constraint
                                as constraint 0 (`r`)*/
            );
            assert(x == 1);
        }

        /*
        # specific register constraints

            If you look at the generated assembly code,
            you will see that x was put into `eax`.
        */
        {
            volatile int x = 0;
            asm (
                "incl %0"
                : "=a" (x)
                : "0" (x)
            );
            assert(x == 1);
        }
#endif
    }

    /*
    # typeof

        Like C++11 decltype.

        Partially reproductible with C11 `_Generic`.
    */
    {
        typeof(1 + 0.5) j = 0.5;
        assert(j == 0.5);
    }

    /*
    # range notation
    */
    {
        /* case */
        {
            int i = 1;
            switch (i) {
                case 0 ... 2:
                    assert(1);
                break;

                case 3 ... 5:
                    assert(0);
                break;

                default:
                    assert(0);
                break;
            }
        }

        /* Intializations */
        {
            int is[] = { [0 ... 2] = 0, [3 ... 5 ] = 1  };
            assert(memcmp(is, &(int[6]){ 0, 0, 0, 1, 1, 1 }, sizeof(typeof(is))) == 0);
        }
    }

    /*
    # __builtin

    # builtin

        - https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
        - https://gcc.gnu.org/onlinedocs/gcc/Target-Builtins.html

        Many GCC special functions and macros are prefixed `__builtin_`.

        However, GCC also treats some ANSI C functions as built-ins
        with the same semantics as the original method: e.g. `memcmp`
        gets directly compiled to efficient platform specific instructions.

        Some built-ins are also implementation specific.
    */
    {
        /*
        # builtin_return_address

            Get address that function will return to after return.

            It seems that it is not possible to jump to a location without assemby:
            http://stackoverflow.com/questions/8158007/how-to-jump-the-program-execution-to-a-specific-address-in-c

            This is most useful for debugging.
        */
        {
            builtin_return_address_test();
        }

        /*
        # builtin_constant_p()

            Returns true iff GCC could determine that the given expression is constant,
            to decide if compile time optimizations may be done or not.

            Gcc is not smart enough to decide all cases correctly.

            TODO0 what is a compile time constant? How to use this?
        */
        {
            assert(__builtin_constant_p(1));
            assert(__builtin_constant_p(1 + 1));

            /*TODO0 why does thie fail?*/
            /*const int i = 0;*/
            /*assert(! __builtin_constant_p(i));*/
        }

        /*
        # builtin_expect

            Basis for the `likely` and `unlikely` macros used extensively on the Linux kernel to help with branch prediction:

                #define likely(x)	__builtin_expect(!!(x), 1)
                #define unlikely(x)	__builtin_expect(!!(x), 0)

            TODO0 why the double negation?

            Says that we expect the left side expression and the right side long value to be the same almost always.
        */
        {
            int x = 0;
            int y;
            if (__builtin_expect(x, 0))
                y = 1;
            if (x == 0)
                y = 1;
            assert(y == 1);
        }

        /*
        # builtin_prefetch

            Pulls data into cache shortly before it is needed.

            Signature:

                void __builtin_prefetch(const void *addr, ...);

            - addr: The address of the data
            - rw:

                Second optional argument.

                Indicates whether the data is being pulled in for Read or preparing for a Write operation

                - 0 = r (default)
                - 1 = w

            - locality:

                Degree of temporal locality of variable.

                Third optional argument.

                Integer in [0,3] range.

                - 0 means no temporal locality, so it can be removed from cache immediately after use.
                - 3 means very high temporal locality, should stay on the cache afterwards.

                3 is the default value.

            I could not manage to make GCC generate different assembly output in the two cases.
        */
        {
            int j = 1;

            get_cache_dirty();
            __builtin_prefetch(&j, 0, 0);
            assert(j == 1);

            get_cache_dirty();
            assert(j == 1);
        }
    }

    return EXIT_SUCCESS;
}
