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
            std::cout << "__cplusplus = " << __cplusplus << std::endl;

#if __cplusplus >= 201103L
            std::cout << "C++11 code" << std::endl;
#endif
        }

#ifdef __STDCPP_THREADS__
        // TODO why not defined even though I do have multithreading?
        std::cout << "__STDCPP_THREADS__" << __cplusplus << std::endl;
        assert(__STDCPP_THREADS__ == 1);
#endif
    }
}
