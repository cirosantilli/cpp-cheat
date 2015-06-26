/*
# cpp

    GNU cpp extensions to the ANSI C preprocessor.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    /*
    # Predefined macros

    # Preprocessor defines

        Full list: http://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros

        View all macros that would be automatically defined:

            cpp -dM /dev/null

        TODO there are some missing! where is `__i386__` documented for example?
    */
    {
        /*
        # __COUNTER__

            Increments each time it gets used.

            Can be used to generate unique numbers.
        */
        {
            assert(__COUNTER__ == 0);
            assert(__COUNTER__ == 1);
            assert(__COUNTER__ == 2);
        }

        /*
        # __TIMESTAMP__
        */
        {
            printf("__TIMESTAMP__ = %s\n", __TIMESTAMP__);
        }

        /*
        # GCC version numbers

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

#ifdef __i386__
            /*
            # Architecture detection macro

                http://stackoverflow.com/questions/152016/detecting-cpu-architecture-compile-time

                GCC defines architecture macros TODO where?

                Seems to use the list: http://sourceforge.net/p/predef/wiki/Architectures/
            */
            puts("__i386__");
#elif __x86_64__
            puts("__x86_64__");
#endif

#ifdef __linux__
            /*
            # OS detection macro

                http://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive

                Same riddle as architecture detection.
            */
            puts("__linux__");
#endif
        }
    }

    return EXIT_SUCCESS;
}
