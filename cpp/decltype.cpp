/*
# decltype

    C++11 keyword

    Replace decltype with type of an expression at compile time.

    More powerful than `auto`.
*/

#include "common.hpp"

int f() {
    return 1;
}

class C {
    public:
        int f() { return 2; }
};

int i;
decltype(i) g() {
    return 1;
}

int main() {
#if __cplusplus >= 201103L
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

    // Return value.
    {
        decltype(f()) i;
        assert(typeid(i) == typeid(int));

        C c;
        decltype(c.f()) j;
        assert(typeid(i) == typeid(int));

        // Return value without instance. Use declval.
        // http://stackoverflow.com/questions/9760358/decltype-requires-instantiated-object
        decltype(std::declval<C>().f()) k;
        assert(typeid(k) == typeid(int));
    }

    // Can be used to declare the return value of functions.
    assert(g() == 1);
#endif
}
