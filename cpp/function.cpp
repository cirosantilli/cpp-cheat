// # function

#include "common.hpp"

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
    /*
    In C++, unlike in C, definitions can omit argument names if they don't use those arguments!

    This probably exists for method overridding.
    */
    {
        assert(def_no_argname(0)    == 1);
        assert(def_no_argname(0, 0) == 2);
    }
}
