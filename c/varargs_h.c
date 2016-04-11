/*
# varargs.h

    Header that contains helpers necessary
    to deal with the variadic function language feature.

# Variadic functions

    Language feature that allows functions with variable number of arguments.

    They are the functions that contain three dots as an argument `...`

# va_start

        va_start(varname, last_argname)

    Initialize `va_list` variable varname. Indicates that varargs come after `last_argname`.

    `last_argment` is the last non-variadic argument. It's value is not important: only it's address.
    This is only possible because `va_list` is a macro, which enables it to the the address of `last_argname`.

    Mandatory.

    TODO: what does it really do in assembly?

# va_end

    Analogous to va_start after usage. Mandatory.

# Vs C99 array literal

    If all arguments are of a single type, use arrays, they are saner.
*/

#include "common.h"

int variadic_add(int numargs, ...) {
    va_list args;
    /* numargs is just the first argument, not necessarily the length! */
    va_start(args, numargs);
    int sum = 0;
    for (int i = 0 ; i < numargs; i++)
        sum += va_arg(args, int);
    va_end(args);
    return sum;
}

int variadic_add_null(int dummy, ...) {
    int arg;
    int sum;
    va_list args;
    va_start(args, dummy);
    sum = 0;
    while (1) {
        arg = va_arg(args, int);
        if (!arg)
            break;
        sum += arg;
    }
    va_end(args);
    return sum;
}


int sprintf_wrapper(char *s, const char *fmt, ...) {
    int ret;
    va_list args;
    va_start(args, fmt);
    ret = vsprintf(s, fmt, args);
    va_end(args);
    return ret;
}

int main() {

    /* Basic examples */
    assert(variadic_add(3, 1, 2, 3)       == 6);
    assert(variadic_add(5, 1, 2, 3, 4, 5) == 15);

    /*
    # Variadic function without non variadic arguments

        Not possible:
        http://stackoverflow.com/questions/2622147/is-it-possible-to-have-a-variadic-function-in-c-with-no-non-variadic-parameter

        `va_start` takes the first argument.
    */

    /*
    # Get number of variadic arguments

        It is impossible except from other arguments.

        http://stackoverflow.com/questions/5272703/how-do-vararg-functions-find-out-the-number-of-arguments-in-machine-code

        `printf` just deduces that form the format string, and reads the stack away
    */
    {
        /* Extra integer argument technique. */
        assert(variadic_add(3, 1, 2, 3) == 6);

        /*
        Trailing null pointer technique `(void *)NULL`.

        TODO: how to distinguish 0 and (void *)0?

        C standard says they should compare equal, so impossible?

        But then why not use `0` instead of `NULL`?
        */
        /*assert(variadic_add_null(3, 1, 2, 0, 3, (void *)0) == 6);*/
    }

    /*
    # vprintf

        This is the raison d'etre for the `vprintf` family, which takes a va_list argument.

        It allows you to forward `va_list` easily.
    */
    {
        char s[32];
        sprintf_wrapper(s, "%c", 'a');
        assert(s[0] == 'a');

        /*
        The only problem with the wrapper is that compile time error checking is not done.

        This could be achieved via the gcc `__attribute__((format,X,Y))` extension
        */
        {
            /* Error checking is not done for the wrapper. */
            /* Might segfault at runtime. */
            char s[32];
            if (0) {
                sprintf_wrapper(s, "%s" /*missing arg*/);
                printf("sprintf_wrapper wrong = %s\n", s);
            }

            /* WARN type error checking is done for `sprintf`. */
            /*sprintf(s, "wrong %s");*/
        }
    }

    /*
    # Array argument

    http://stackoverflow.com/questions/280940/calling-a-c-function-with-a-varargs-argument-dynamically
    http://stackoverflow.com/questions/14705920/passing-an-array-as-parameters-to-a-vararg-function
    */

    return EXIT_SUCCESS;
}
