#include "common.h"

int main() {
    /*
    # system

        Executes command in a shell and waits for it to end before continuing current program.

        The shell is implementation dependant

        - linux: `/bin/sh`

        so in the end what you write with this is not very portable.

        the return value is also implementation defiend, but it is often the command exit status
        or an error reserved value.
    */
    {
        /* Linux test. */
        printf("system return = %d\n", system("date >/tmp/cpp-cheat"));
    }

    /*
    # String to int methods.
    */
    {
        /*
        # strtol

            Most robust ASCI C method.

            Can be made even more strict for untrusted input with:
            http://stackoverflow.com/a/12923949/895245
        */
        {
        }

        /*
        # atoi

        # atol

        # atoll

            Convert string to integer.

            `strtol` is better as it allows error checking, so use that instead.

            C99 explicitly says that errno does not need to be set.
        */
        {
            assert(atoi("123") == 123);

            enum N { N = 256 };
            char s[N];
            snprintf(s, N, "%d", INT_MAX);
            assert(atoi(s) == INT_MAX);
            snprintf(s, N, "%d", INT_MIN);
            assert(atoi(s) == INT_MIN);

#ifdef UNDEFINED_BEHAVIOUR
            /* Integer too large. */
            snprintf(s, N, "%ld", ((long)INT_MAX) + 1L);
            printf("INT_MAX + 1 = %s\n", s);
            printf("atoi(INT_MAX + 1) = %d\n", atoi(s));

            /* Not an integer. */
            printf("atoi(123abc) = %d\n", atoi("123abc"));
#endif

            /* No hex. use strtol */
            /*assert(atoi("0xA") == 10);*/
        }

        /*
        # itoa

        # ltoa

            Neither POSIX nor glibc?

            http://stackoverflow.com/questions/190229/where-is-the-itoa-function-in-linux

            The closes one gets is an internal `_itoa` in glibc.

            `sprintf` is the way.
        */
    }

    return EXIT_SUCCESS;
}
