/*
# varargs.h

    Header that contains helpers necessary
    to deal with the variadic function language feature.

# variadic functions

    Language feature that allows functions with variable number of arguments.

# va_start

        va_start(varname, last_argname)

    Initialize `va_list` variable varname. Indicates that varargs come after numargs.

# Get number of variadic arguments

    TODO I think it is impossible except from another argument.

    `printf` just deduces that form the format string, and reads the stack away.
*/

#include "common.h"

int variadic_add(int numargs, ...) {
    va_list args;
    va_start(args, numargs);
    int sum = 0;
    for(int i = 0 ; i < numargs; i++) {
        int arg = va_arg(args, int);
        sum += arg;
    }

    /* You MUST do this. TODO why? */
    va_end(args);

    return sum;
}

/*
This function illustrates how to va args from one function to another.

# vprintf

    This is the raison d'etre for the `vprintf` family, which takes a va_list argument.
*/
int sprintf_wrapper(char *s, const char *fmt, ...) {
    int ret;
    va_list args;
    va_start(args, fmt);
    ret = vsprintf(s, fmt, args);
    va_end(args);
    return ret;
}

int main() {
    assert(variadic_add(3, 1, 2, 3)       == 6);
    assert(variadic_add(5, 1, 2, 3, 4, 5) == 15);

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
        if (0) {
            sprintf_wrapper(s, "%s" /*missing arg*/);
            printf("sprintf_wrapper wrong = %s\n", s);
        }

        /* WARN type error checking is done for `sprintf`. */
        /*sprintf(s, "wrong %s");*/
    }

    return EXIT_SUCCESS;
}
