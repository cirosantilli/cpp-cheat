/*
http://stackoverflow.com/questions/8528979/how-to-determine-if-an-object-is-an-instance-of-certain-derived-c-class-from-a/37054214#37054214
*/

#include <iostream>

class MyBase {
    public:
        virtual int myMethod() = 0;
};

class MyDerived1 : public MyBase {
    public:
        virtual int myMethod() { return 1; }
};

class MyDerived2 : public MyBase {
    public:
        virtual int myMethod() { return 2; }
};

int main() {
    MyBase *myBase;
    MyDerived1 myDerived1;
    MyDerived2 myDerived2;
    myBase = &myDerived1;
    std::cout << myBase->myMethod() << std::endl;
    myBase = &myDerived2;
    std::cout << myBase->myMethod() << std::endl;
}
