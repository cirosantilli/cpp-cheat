#include <iostream>

#include "notmain.hpp"

int main() {
    std::cout << MyClass<int>().f(1) << std::endl;
#if 0
    // error: undefined reference to `X<float>::f(float)'
    std::cout << X<float>().f(1.5) << std::endl;
#endif
}
