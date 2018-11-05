/*
http://stackoverflow.com/questions/8528979/how-to-determine-if-an-object-is-an-instance-of-certain-derived-c-class-from-a/37054214#37054214
https://stackoverflow.com/questions/28279395/printing-sub-class-members-in-gdb
*/

#include <iostream>

struct MyBase {
    MyBase(int i) : i(i) {}
    virtual int myMethod() = 0;
    int i;
};

struct MyDerived1 : MyBase {
    MyDerived1(int j) : MyBase(0), j(j) {}
    virtual int myMethod() { return 1; }
    int j;
};

struct MyDerived2 : MyBase {
    MyDerived2(int j) : MyBase(0), j(j) {}
    virtual int myMethod() { return 2; }
    int j;
};

int main() {
    MyBase *myBase;
    MyDerived1 myDerived1(1);
    MyDerived2 myDerived2(2);
    myBase = &myDerived1;
    std::cout << myBase->myMethod() << std::endl;
    myBase = &myDerived2;
    std::cout << myBase->myMethod() << std::endl;
}
