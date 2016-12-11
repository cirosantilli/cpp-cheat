/*
# typeid

    Get runtime type of variables.

    Can be done for both types and variables of the type.

    Returns objects of `type_info`

# type_info

    Type returned by `typeid`.
*/

#include "common.hpp"

int main() {
    /*
    typeid returns `type_info`.

    However copy and assign for type_info are private,
    so the following fail.
    */
    {
        //std::type_info t = typeid(int);
        //std::type_info t(typeid(int));
    }

    /*
    type_info implements `==` and `!=`.

    typeid's of different types are always different.
    */
    {
        int i, i1;
        int& ia = i;
        assert(typeid(i)  == typeid(int) );
        assert(typeid(ia) == typeid(int&));
        assert(typeid(i)  == typeid(i1)  );
    }

    // Works differently for virtual and non virtual classes!
    // http://stackoverflow.com/questions/11484010/c-typeid-used-on-derived-class-doesnt-return-correct-type
    {
        class C {};
        class D : public C {};
        C c;
        D d;
        C *dp = &d;
        assert(typeid(C)   == typeid(c)   );
        assert(typeid(*dp) == typeid(C)   );
        assert(typeid(*dp) != typeid(D)   );

        class PolyBase {
             void virtual f() {};
        };
        class PolyDerived : public PolyBase {
             void virtual f() {};
        };
        PolyDerived pd;
        PolyBase *pdp = &pd;
        assert(typeid(*pdp) == typeid(PolyDerived));
    }

    /*
    # name

        `name`: return a string representation of the type.

        The exact string is implementation defined.

        `name()` is implementation defined.

        On GCC, you can demangle with `__cxa_demangle`:
        http://stackoverflow.com/questions/4465872/why-typeid-name-returns-weird-characters-using-gcc
    */
    {
        std::cout << "typeid(int).name() = " << typeid(int).name() << std::endl;
    }

    /* The return value is calculated at runtime. */
    {
        class Base {
            public:
                virtual void f() {}
        };

        class Derived : public Base {
            public:
                virtual void f() {}
        };

        Derived d;
        Base *bp = &d;
        // The mangled Derived ID is output.
        assert(typeid(*bp).name() == typeid(Derived).name());
    }


    // before: http://stackoverflow.com/questions/8682582/what-is-type-infobefore-useful-for

    // hash_code: return a size_t hash of the type

    /*
    # type_index

        Wrapper around type_info that allows copy and assign.
    */
    {
        std::type_index t = typeid(int);
    }
}
