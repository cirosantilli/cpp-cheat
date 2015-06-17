// # function

#include "common.hpp"

// TODO factor those dummy classes.
class Class {};
class Base {};
class BaseProtected {};

// Default args. C++ only.
// Creates several name mungled functions on the assembly code.

    int DefaultArgs(int i, int j=0)      { return i + j; }

    // ERROR: Cannot use one argument as the default for the other.
    //int DefaultArgs(float f, float f2=f) { return f + f2; }

// ERROR: no compound literals in c++
//void foo (int bar[] = (int[2]){0 ,1});

// Function overloading

    void overload(int i){callStack.push_back("overload(int)");}
    void overload(int i, int j){callStack.push_back("overload(int,int)");}
    void overload(float i){callStack.push_back("overload(float)");}
    void overload(float i, float j, float k=0.f){callStack.push_back("overload(float,float,float=)");}

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

// Default arguments.

    void defaultArgProto(int i=0);
    void defaultArgProto(int i) {}

    // BAD: usually not what you want
    // since includers will not see the default version

        void defaultArgDef(int i);
        void defaultArgDef(int i=0) {}

// ERROR: default cannot go in declaration and definition

        //void defaultArgBoth(int i=0);
        //void defaultArgBoth(int i=0) {}

int def_no_argname(int) { return 1; }
int def_no_argname(int, int) { return 2; }

/*
# auto arguments
*/

        /*ERROR: no you can't*/
    /*
    int func_auto(auto a){
        ++a;
        return (int)a;
    }
    */

int main() {
    // # Overload
    {
        overload(1);
        assert(callStack.back() == "overload(int)");
        callStack.clear();

        //base type conversions
        {
            overload(1.0f);

            /*
            ERROR
            ambiguous overload(int) overload(float)
            compiler does not know wether convert double to float or int
            */
            //overload(1.0);
        }

        assert(callStack.back() == "overload(float)");
        callStack.clear();

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

        // # Default arguments
        {
            assert(DefaultArgs(1)    == 1);
            assert(DefaultArgs(1, 1) == 2);
        }

        /*
        # default arguments for references

            There seems to be no standard way of doing that without using extra memory / verbosity.

            <http://stackoverflow.com/questions/2816293/passing-optional-parameter-by-reference-in-c>
        */

        /*
        # volatile overload

            Functions that differ by `volatile` can be overloaded:

            - http://stackoverflow.com/questions/10242578/volatile-overloading
        */
        {}
    }

    /*
    In C++, unlike in C, definitions can ommit argument names if they don't use those arguments!

    This probably exists for method overridding.
    */
    {
        assert(def_no_argname(0)    == 1);
        assert(def_no_argname(0, 0) == 2);
    }
}
