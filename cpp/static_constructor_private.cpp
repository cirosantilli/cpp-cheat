// https://stackoverflow.com/questions/185844/how-to-initialize-private-static-members-in-c/48337288#48337288
// https://stackoverflow.com/questions/1197106/static-constructors-in-c-i-need-to-initialize-private-static-objects

#include <cassert>
#include <vector>

// Normally on the .hpp file.
class MyClass {
public:
    static std::vector<int> v, v2;
    static struct _StaticConstructor {
        _StaticConstructor() {
            v.push_back(1);
            v.push_back(2);
            v2.push_back(3);
            v2.push_back(4);
        }
    } _staticConstructor;
};

// Normally on the .cpp file.
std::vector<int> MyClass::v;
std::vector<int> MyClass::v2;
// Must come after every static member.
MyClass::_StaticConstructor MyClass::_staticConstructor;

int main() {
    assert(MyClass::v[0] == 1);
    assert(MyClass::v[1] == 2);
    assert(MyClass::v2[0] == 3);
    assert(MyClass::v2[1] == 4);
}
