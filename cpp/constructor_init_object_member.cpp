/*
https://stackoverflow.com/questions/12927169/how-can-i-initialize-c-object-member-variables-in-the-constructor

Initializer lists are the only way to not call the extra default constructor + assignement apparently.
This is a major use case of initializer lists.

They are not very versatile however, as you can't easily have multiple statements.
*/

#include "common.hpp"

class MyMemberClass {
    public:
        int i;
        MyMemberClass() : i(0) {
            callStack.push_back("MyMemberClass()");
        }
        MyMemberClass(int i) : i(i) {
            callStack.push_back("MyMemberClass(int i)");
        }
        MyMemberClass& operator=(const MyMemberClass& rhs) {
            this->i = rhs.i;
            callStack.push_back("operator=");
            return *this;
        }
};

class MyClass {
    public:
        MyMemberClass myMemberClass;
        MyClass(int i) : myMemberClass(i) {}
};

class MyClassNoInitializer {
    public:
        MyMemberClass myMemberClass;
        MyClassNoInitializer(int i) {
            myMemberClass = MyMemberClass(i);
        }
};

int main() {
    // Good, less calls.
    {
        callStack.clear();
        MyClass myClass(1);
        assert(myClass.myMemberClass.i == 1);
        assert(callStack.size() == 1);
        assert(callStack.back() == "MyMemberClass(int i)");
    }

    // Bad, more calls.
    {
        callStack.clear();
        MyClassNoInitializer myClass(2);
        assert(myClass.myMemberClass.i == 2);
        assert(callStack.size() == 3);
    }
}
