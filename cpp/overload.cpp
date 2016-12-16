/*
# Overload
*/

#include "common.hpp"

// TODO factor those dummy classes.
class Class {};
class Base {};
class BaseProtected {};

std::string overload(int i) { return "i"; }
std::string overload(float i) { return "f"; }
std::string overload(int i, int j) { return "ii"; }
std::string overload(float i, float j, float k = 0.f) { return "iff"; }

// OK even if return type is different all is decided at compile time.
//int overload(int i, int j, int k){return 1;}

// ERROR: conflict with int.
//void overload(const int i){}

// ERROR: cannot differentiate by output since output is used to decide if other parts of code make sense.
//int overload(){return 0;}
//float overload(){return 0.f;}

// ERROR: conflict with int int
//void overload(int i, int j=0){cout << "int int=";}

// BAD: compiles, but is useless to give a default,
// since when calling, caller is *forced* to give a value for j
// or wil get `call is ambiguous` compile time error
// because compiler cannot decide between
// here the default arg can be usefull for a call of type float float.
//void overload(float i, float j=1){cout << "float float=";}

// TODO: why does this compile, that is, how not to make an ambiguous call with overload(int).

    void overloadValAddr(const int i) {}
    void overloadValAddr(const int& i) {}

void overloadBase(Base b) {}
void overloadBase(BaseProtected b) {}

int main() {
    assert(overload(1) == "i");

    //base type conversions
    {
        assert(overload(1.0f) == "f");

        /*
        ERROR: ambiguous overload(int) overload(float)

        Compiler does not know wether convert double to float or int.
        */
        //overload(1.0);
    }

    /*
    ERROR: ambiguous
    should compiler coverts to Base or BaseProtected? Both are possible via the default copy constructors.
    */
    {
        Class cOverload;
        //overloadBase(cOverload);
    }

    // ERROR: ambiguous
    //i=4;
    //overloadValAddr(i);

    /*
    # volatile overload

        Functions that differ by `volatile` can be overloaded:

        - http://stackoverflow.com/questions/10242578/volatile-overloading
    */
    {}

    /*
    Function pointer: decided by the typecast.

    http://stackoverflow.com/questions/2942426/how-to-specify-a-pointer-to-an-overloaded-function
    */
    {
        // Variable.
        {
            std::string (*fi)(int) = overload;
            std::string (*ff)(float) = overload;
        }
    }

    // # const function overload
    // http://stackoverflow.com/questions/251159/what-is-the-use-of-const-overloading-in-c
    {
        class C {
            public:
                int f() { return 1; }
                int f() const { return 2; }
        };
        C c;
        assert(c.f() == 1);
        const C& d = c;
        // No, I kid you not. const qualification is serious stuff.
        assert(d.f() == 2);
    }
}
