/*
Method
*/

#include <iostream>

class MyClass {
    public:
        void myMethod() {
            std::cout << "My method" << std::endl;
        }
};

int main() {
    MyClass().myMethod();
}
