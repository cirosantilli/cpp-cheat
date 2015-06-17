/*
# static_assert

    Make assertions at compile time.

    In this way you don't waste time compiling large programs,
    or do potentially dangerous runtime operations to test your program.

    Probably became possible on C++11 because of features such as `constexpr`,
    which allow to better manage compile time constantness.

    <http://stackoverflow.com/questions/1647895/what-does-static-assert-do-and-what-would-you-use-it-for>
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    static_assert(0 < 1, "msg");

    // ERROR: static assertion failed
    //static_assert(0 > 1, "msg");

    std::srand(time(NULL));
    // ERROR: needs to be a constexpr
    //static_assert(std::rand() >= 0);
#endif
}
