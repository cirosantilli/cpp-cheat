/*
https://stackoverflow.com/questions/22798601/how-to-debug-c11-code-with-unique-ptr-in-ddd-or-gdb
*/

#include <memory> // unique_ptr

class MyClass {
    public:
        int myMethod() {
            return 1;
        }
};

int main() {
    std::unique_ptr<MyClass> p(new MyClass());
    p->myMethod();
}
