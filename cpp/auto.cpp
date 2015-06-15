/*
# auto

    C++11 keyword

    Completelly differs in meaning with the useless C `auto` keyword.

    Variable type is infered based on return value of initialization.

    Reduces code duplication, since it allows us to not write explicitly types everywhere.

    Major application: create an iterator without speficying container type.
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    // Basic usage.
    {
        //the compiler infers the type of i from the initialization.
        auto i = 1;
    }

    // Reference.
    {
        int i = 1;
        auto& ai = i;
        ai = 2;
        assert(i == 2);
    }

    // ERROR: must initialize immediately. How could the compiler deduce type otherwise?
    {
        //auto i;
        //i = 1;
    }

    // If initialized from reference, discards the reference, while decltype keeps it.
    {
        int i = 0;
        int& ir = i;
        auto ir2 = ir;
        ir2 = 1;
        assert(i == 0);
    }

    // Array. Seems not.
    {
        //auto is[]{1, 0};
    }

    {
        typedef int Type;
        std::vector<std::vector<Type>> is{{0}, {1, 2}};
        for (auto& i : is[1]) std::cout << i << std::endl;
    }
#endif
}
