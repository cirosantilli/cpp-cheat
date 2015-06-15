/*
# preprocessor

    Almost the same as the C one:
    http://stackoverflow.com/questions/5085533/is-a-c-preprocessor-identical-to-a-c-preprocessor

    The major differences are the predefined macros.
*/

#include "common.hpp"

int main() {
    /*
    # Standard preprocessor macros
    */
    {
        /*
        # __cplusplus

            Defined only if using C++ compiler.

            Its value is the actual C++ version in use in a similar way to __STDC_VERSION__

            Values:

            - C++98: 199711L
            - C++11: 201103L

            C99 says that the C compiler must not define it.
        */
        {
#ifdef __cplusplus
        printf("__cplusplus = %li\n", __cplusplus);
#endif
        }
    }
}
