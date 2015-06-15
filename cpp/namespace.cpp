/*
# namespace
*/

#include "common.hpp"

// ERROR: same naming rules as vars
//namespace 2D{}

// BAD: by convention, namespaces start with lower case
namespace D2{}

int i;

void f() {}

void prototype();

namespace namea {

    int in_namea_only = 0;

    class C {
        public:
            C() {}
    };

    namespace nameaa {
        int i;

        void f() {}

        class C {
            public:
                C() {}
        };
    }

    namespace nameab {
        int i;

        void f() {
            ::i = 0;
            // namea::nameab::i
            i = 0;
            // namea::nameaa::i
            nameaa::i = 0;

            // Only affects this function. see C::C() at the f() call.
            using namespace nameaa;
        }

        class C :
            public namea::C
            //public C
            // ERROR: refers to current incomplete C already
            //not existem namea::C
        {
            C() {
                // No ambiguity because using inside f() only afects the function.
                f();
            }
        };
    }

    int i;

    void f() {
        ::i = 0;
        i = 0;   //namea::i
        namea::i = 0;
        nameaa::i = 0; //namea::nameaa::i
    }
}

namespace namea {
    // Can add new members
    int j;
    void newFunc(){}
    class B{};

    // ERROR: redefinition
    //int i;

    // Implementation of namea::prototype.
    //void prototype(){}
}

// ERROR: must be declared/defined inside.
//namea::i = 0;
//void namea::prototype(){}
//int namea::j;
//void namea::g(){}
//class namea::B{};

// ERROR.
//template<class T> namespace t {}

// ADL

    namespace adl0 {

        struct s {};

        int adl(struct s s){
            return 0;
        }

        int i;

        int adlNoType(int i){
            return 0;
        }

        int adlMultiArg(int i, struct s s, int j){
            return 0;
        }
    }

    namespace adl1 {

        struct s {};

        int adl(struct s s){
            return 1;
        }

        int i;

        int adlNoType(int i){
            return 1;
        }

        int adl0FromAdl1(struct adl0::s s) {
            return 1;
        }

        int adl0And1FromAdl1(struct adl0::s s0, struct s s1) {
            return 1;
        }

        float adl01(struct adl0::s s, struct s s1){
            return 0.5;
        }
    }

    namespace adl0 {
        float adl01(struct s s, struct adl1::s s1){
            return 0.5;
        }
    }

int main() {
    // variables
    {
        int i;
        i = 0;          //inner  i
        ::i = 0;        //global i
        namea::i = 0;   //namea  i
        i++;
        assert(i        == 1);
        assert(::i      == 0);
        assert(namea::i == 0);

        f();
        namea::f();
        namea::nameaa::f();
    }

    /*
    # using

        Be very careful with `using`, because there is no way to unuse afterwards.

        In particuar, *never* use `using namespace X` on the toplevel a header file,
        or you shall confuse includers to tears.
    */
    {
        using namespace namea;

        // ERROR ambiguous
        //f();
        //::f
        //namea::f

        ::f();
        namea::f();
        namea::nameaa::f();

    }

    // Brackets limit the using namespace scope.
    // It is obligatory to specify unused namespaces.
    //in_namea_only = 1;

    // ERROR: no namespace inside funcs
    //namespace main{}

    // Namespace chaining
    {
        using namespace namea;
        using namespace nameaa;

        // ERROR ambiguous
        // ::f
        // namea::f
        // namea::nameaa:f
        //f();
        ::f();
        namea::f();
        namea::nameaa::f();
    }

    // Namespace alias
    namespace newNamea = namea;
    {
        using namespace newNamea;
        // ERROR: ambiguous.
        // ::f
        // namea::f
        //f();
    }

    // Subimport
    {
        // Imports only name::f.
        using namea::f;

        f();
            // OK: overwrides global f().
            //namea::f

        // ERROR: only f was imported.
        //C c;
    };

    /*
    # ADL

        Argument dependent name lookup.

        <http://en.wikipedia.org/wiki/Argument-dependent_name_lookup>

        Allows for functions without namespace qualification:

        - to be found
        - to haves ambiguities resolved

        based on the namespace in which the types of their arguments are defined.

        Explains why operator `<<` does not need the `std::` qualifier,
        even though *must* be implemented as a non-member function!!
        (see info on operator overload for why)

        ADL for operators is a major use case, because specifying namespaces
        for operators completely destroys their eyecandy appeal.
    */
    {
        // ADL allows both to be found and differentiated!
        {
            {
                struct adl0::s s;
                assert(adl(s) == 0);
            }

            {
                struct adl1::s s;
                assert(adl(s) == 1);
            }
        }

        // Only works if the type is defined on the same namespace as the function.
        {
            struct adl0::s s;
            // ERROR: not declared on this scope
            //assert(adl0FromAdl1(s) == 1);
        }

        // Works if at least one of the argument types is in the namespace.
        {
            struct adl0::s s;
            assert(adlMultiArg(0, s, 1) == 0);
        }

        // Lookup works even if types from both namespaces are used.
        {
            struct adl0::s s0;
            struct adl1::s s1;
            assert(adl0And1FromAdl1(s0, s1) == 1);
        }

        // Of course, calls can still be ambiguous.
        {
            struct adl0::s s0;
            struct adl1::s s1;
            // ERROR: ambiguous call
            //assert(adl01(s0, s1) == 0.5);
        }

        // Only works for *types* defined in the namespaces, not values.
        {
            //assert(adlNoType(adl0::i) == 0);
            // ERROR: adlNoType not found on this scope
            //assert(adlNoType(adl1::i) == 0);
        }
    }
}
