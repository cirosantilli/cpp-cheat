/*
# shared_ptr

    Introuced in C++11, before that as part of boost.

    Reference counts usages, deletes data when the last one is gone.
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    {
        callStack.clear();

        // First reference
        std::shared_ptr<NoBaseNoMember> sp1(new NoBaseNoMember(1));
        assert(sp1.use_count() == 1);
        assert(sp1->i == 1);

        // Create reference with copy constructor.
        std::shared_ptr<NoBaseNoMember> sp2(sp1);
        assert(sp1.use_count() == 2);
        assert(sp2->i == 1);

        // Create reference with assignment constructor.
        std::shared_ptr<NoBaseNoMember> sp3;
        sp3 = sp1;
        assert(sp1.use_count() == 3);
        assert(sp3->i == 1);

        // ERROR No converstion operator to pointer defined.
        //NoBaseNoMember *spp = sp1;

        // Replace one reference with a new pointer.
        sp1 = std::shared_ptr<NoBaseNoMember>(new NoBaseNoMember(2));
        // ERROR No constructor directly from pointers.
        //sp1 = new NoBaseNoMember(2);
        assert(sp1.use_count() == 1);
        assert(sp2.use_count() == 2);
        assert(sp1->i == 2);
        assert(sp2->i == 1);

        // Replace the remaining references and check that the destructor got called.
        sp2 = sp1;
        assert(callStack.back() != "NoBaseNoMember::~NoBaseNoMember()");
        sp3 = sp1;
        assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()");
    }
#endif
}
