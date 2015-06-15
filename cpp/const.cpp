/*
# const

    There are differences between the `const` keyword in C and C++.

    Also, in C++ const can be used to qualify methods.

    http://stackoverflow.com/questions/8908071/const-correctness-in-c-vs-c
*/

#include "common.hpp"

class Class {
    public:
        Class() {}
        int i;
        void constMethod() const {}
};

int main() {
    /*
    In C++, consts cannot be changed not even through pointers.

    C this is only a warning, and allows us to change ic.
    */
    {
        const int i = 2;
        //int* ip = i;
    }

    // unlike for constexpr, const does not need to have value define at compile time
    {
        const int i = std::time(NULL);
    }

    // consts must be initialized at declaration because they cannot be modified after.
    {
        // ERROR i not initialized
        //const int i;

        // ERROR uninitialized
        //int * const ipc;

        // OK: we can change which object it points to
        {
            int i = 0;
            int j = 0;
            int const * icp;
            icp = &i;
            icp = &j;
            // ERROR
            //*icp = 1;
        }

        // C is initialized by the constructor
        // so it is OK to do this unlike for base types
        const Class c;
    }

    // Const for classes.
    {
        const Class c;

        // Cannot reassign:

            //cc = Class();

        // Cannot assign members:

            //cc.i = 1;

        // Can create const refs to:

            const int& cia = c.i;

        // Cannot create non const refs:

            //int& ia = cc.i;

        /*
        Can only call const methods,
        because a non const method could change the object.

        Therefore, *BE CONST OBSESSIVE!* mark as const every method that does not change the object!
        */
        {
            //c.method();
            c.constMethod();
        }
    }
}
