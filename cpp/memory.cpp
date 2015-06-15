/*
# memory
*/

#include "common.hpp"
#include "no_base_no_member.hpp"

int main() {
#if __cplusplus >= 201103L
    /*
    # shared_ptr

        Introuced in C++11, before that as part of boost.
    */
    {
        callStack.clear();
        std::shared_ptr<NoBaseNoMember> spi1(new NoBaseNoMember);
        std::shared_ptr<NoBaseNoMember> spi2(spi1);
        spi1->method();
        spi1 = std::shared_ptr<NoBaseNoMember>(new NoBaseNoMember);
        spi2 = std::shared_ptr<NoBaseNoMember>(spi1);
        assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()");
    }
#endif
}
