// # std::move
//
// https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used
//
// TODO find a good motivating example. c++17 return multiple is fine to not have,
// but why not just have an init() function here right?

#include <cassert>
#include <string>
#include <vector>

struct MyClass {
    int *ip;
    static std::vector<std::string> calls;
    MyClass() {
        ip = new int;
        calls.push_back("ctor");
    }
    MyClass(const MyClass&)            { calls.push_back("copy ctor"); }
    MyClass& operator=(MyClass&)       { calls.push_back("copy assign"); return *this; }
    MyClass& operator=(const MyClass&) { calls.push_back("copy assign const"); return *this; }
    MyClass(MyClass&&)                 { calls.push_back("move ctor");  }
    MyClass& operator=(MyClass&&)      { calls.push_back("move assign"); return *this; }
    ~MyClass()                         {
        delete ip;
        calls.push_back("dtor");
    }
};
std::vector<std::string> MyClass::calls;

void make_objects(MyClass& o1, MyClass& o2, int i) {
    *(o1.ip) = i + 1;
    *(o2.ip) = i - 1;
}

int main() {
}
