/*
# lambda

    C++11

    Function without name.

    Specialy useful in conjunction with function that take functions as arguments such as `std::find_if`,
    when we only want to use the function passed once.

    Good explanation: <http://stackoverflow.com/a/7627218/895245>

    TODO: why square brackets? Why not pass by reference as in a regular function?
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    {
        int i = 0;
        int j = 0;
        auto f = [&i,&j](int k) -> int {i = 1; j = 1; return k + 1;};
        assert(f(0) == 1);
        assert(i == 1);
        assert(j == 1);
    }

    // Typical application with find_if.
    {
        std::vector<int> v = {2, 0, 1};
        assert(std::find_if(v.begin(), v.end(),
            [](int i) {return i % 2 == 1;}) == --v.end());
    }
#endif
}
