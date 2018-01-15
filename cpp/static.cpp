/*
# static

This is about static inside classes. Outside classes, it is just the same as in C.

In classes, they are just basically globals with a namespace.
*/

#include "common.hpp"

class OtherClass {
public:
    int i;
    // J cannot be set from constructor.
    int j;
    OtherClass(int i) : i(i), j(0) {}
};

class Class {
public:
    // Data.

        int i;

        static int iStatic;

        // Concflicts with static int.
        //int iStatic;

        // ERROR: cannot init a non-const like this.
        //static int iStaticInit = 0;
        static int iStaticInit;

        // OK: because const static integral type
        const static int iConstStatic = 0;

        // ERROR. Not initialized outside of the class.
        //static int iNoInit;

    // Object data

        static OtherClass otherClass;

        // https://stackoverflow.com/questions/1197106/static-constructors-in-c-i-need-to-initialize-private-static-objects
        static OtherClass otherClassWithJ;
private:
        static struct _StaticConstructor {
            _StaticConstructor() {
                otherClassWithJ.j = otherClassWithJ.i + 1;
            }
        } _staticConstructor;
public:

    // Static methods

        // Must be defined later.
        static int staticMethod();

        // Unlike data, we can define the methods here, just like for global functions.
        static int staticGet1() {
            return 1;
        };

        // ERROR: no this in static.
        //static int staticMethodThis() { return this->i; };

        // Can use static variables in static methods.
        static int doubleIStatic() {
            return iStatic + Class::iStatic;
        };

        // ERROR: static cannot be const. That would make no sense, since const is all about this.
        //static void staticMethodConst() const;

    // Non static methods

        // Access static variable and method from member method.
        int doubleIStaticPlus1NotStatic() {
            return iStatic + this->iStatic + staticGet1();
        }

        // Set static variable from member method.
        void setIStaticNotStatic(int i) {
            iStatic = i;
        }
};

// This is mandatory on some source file, just like for global variables. Related:
// https://stackoverflow.com/questions/20488579/why-we-declare-static-variable-in-a-class-the-definition-in-outside-of-the-cla
int Class::iStatic;

int Class::iStaticInit = 0;

int Class::staticMethod() { return 0; }

OtherClass Class::otherClass(1);
// ERROR
//Class::otherClass.inc();

OtherClass Class::otherClassWithJ(1);
// Must come after all statics.
Class::_StaticConstructor Class::_staticConstructor;

int main() {
    // Basic static field example.
    {
        Class c, c1;
        int i;
        c.iStatic = 0;
        assert(Class::iStatic == 0);
        c1.iStatic = 1;
        assert(Class::iStatic == 1);
        Class::iStatic = 2;
        assert(Class::iStatic == 2);
        c.setIStaticNotStatic(3);
        assert(Class::iStatic == 3);
        assert(Class::otherClass.i == 1);
        assert(Class::otherClassWithJ.i == 1);
        assert(Class::otherClassWithJ.j == 2);
        //assert(Class::iNoInit == 0);
    }

    // Basic static method example.
    {
        Class c;
        assert(c.staticMethod() == 0);
        assert(c.doubleIStaticPlus1NotStatic() == 2 * Class::iStatic + 1);
        assert(Class::staticMethod() == 0);
        assert(Class::staticGet1() == 1);
        assert(Class::doubleIStatic() == 2 * Class::iStatic);
    }
}
