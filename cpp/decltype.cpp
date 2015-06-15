/*
# decltype

    C++11 keyword

    Replace decltype with type of an expression at compile time.

    More powerful than `auto`.
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    int i = 1;
    float f = 2.0;
    decltype(i + f) f2 = 1.5;
    assert(f2 == 1.5);

    // Implies reference while auto does not.
    {
        int i = 0;
        int& ir = i;
        decltype(ir) ir2 = ir;
        ir2 = 1;
        assert(i == 1);
    }

    // Can be used basically anywhere.
    {
        int i = 0;
        std::vector<decltype(i)> v;
        v.push_back(0);
    }
#endif
}
