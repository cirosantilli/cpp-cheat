/*
# Implicitly deleted constructor

    Some characteristics of classes delete default constructors
    that would otherwise be generated automatically.

    http://en.cppreference.com/w/cpp/language/copy_assignment
    Deleted implicitly-declared copy assignment operator
*/

#include "common.hpp"

int main() {
    // const non-class data member.
    {
        {
            //class C {
                // Warning GCC 5.2: non-static const member
                // in class without a constructor.
                //const int i;
            //};
            // ERROR use of deleted function C::C
            //C c;
        }
        {
            class C {
                int i;
            };
            C c;
        }
    }
}
