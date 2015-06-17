/*
# struct

    Structs in C++ are very similar to classes: support access modifiers,
    inheritance, constructors, templates, etc.

    The major difference between them is that the default access modifier for structs
    is public, while for classes it is private.

    This is why structs are used on many simple short language examples:
    no public line is needed.

    The Google C++ style guide recommends using struct only if there is no constructors,
    and classes otherwise.

    <http://stackoverflow.com/questions/2750270/c-c-struct-vs-class>
*/

#include "common.hpp"

template<class T>
struct BaseStruct {
    T i;
    BaseStruct(T i) : i(i) {}

    protected:
        int iProtected;

    private:
        int iPrivate;
};

struct DerivedStruct : BaseStruct<int> {
    DerivedStruct(int i) : BaseStruct(i) {
        iProtected = i;
    }
};

int main() {
    struct DerivedStruct s(1);
    assert(s.i == 1);
}
