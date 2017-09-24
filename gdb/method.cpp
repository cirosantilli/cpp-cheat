/*
Method
*/

#include <iostream>

class MyClass {
    public:
        int myVar;
        int myMethod() {
            return myVar + 1;
        }
};

int main() {
    MyClass().myMethod();
}
