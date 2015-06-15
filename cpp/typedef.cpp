
#include "common.hpp"

int main() {
    // # typedef
    {
        // It is possible to call constructors with typedefs
        {
            class C {
                public:
                    int i;
                    C(int i) : i(i) {}
            };
            typedef C CTypedef;
            CTypedef b = CTypedef(1);
        }

        // Typdefs inside classes follow public / private scoping.
        {
            class ClassWithTypedef {
                public:
                    typedef int typedefPublic;
                private:
                    typedef int typedefPrivate;
            };
            ClassWithTypedef::typedefPublic i;
            // ERROR: not accessible from this context
            //ClassWithTypedef::typedefPrivate j;
        }
    }
}
