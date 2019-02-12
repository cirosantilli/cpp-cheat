// # preprocessor
//
// Almost the same as the C one:
// http://stackoverflow.com/questions/5085533/is-a-c-preprocessor-identical-to-a-c-preprocessor
//
// The major differences are the predefined macros.

#include "common.hpp"

int main() {
    // # __cplusplus
    //
    // Defined only if using C++ compiler.
    //
    // Its value is the actual C++ version in use
    // in a similar way to __STDC_VERSION__
    //
    // C99 says that the C compiler must not define it.
    //
    // GCC 6.4 has the -std=c++17 option early, even before
    // __cplusplus == 201703L was reached.
    {
        std::cout << "__cplusplus = " << __cplusplus << std::endl;
#if __cplusplus == 199711L
        std::cout << "C++98" << std::endl;
#endif
#if __cplusplus == 201103L
        std::cout << "C++11" << std::endl;
#endif
#if __cplusplus == 201402L
        std::cout << "C++14" << std::endl;
#endif
#if __cplusplus == 201703L
        std::cout << "C++17" << std::endl;
#endif
    }

#ifdef __STDCPP_THREADS__
    // TODO why not defined even though I do have multithreading?
    std::cout << "__STDCPP_THREADS__" << __cplusplus << std::endl;
    assert(__STDCPP_THREADS__ == 1);
#endif
}
