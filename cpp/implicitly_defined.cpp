// Implicitly defined functions
//
// https://stackoverflow.com/questions/12340257/default-vs-implicit-constructor-in-c
// https://blog.mozilla.org/nfroyd/2015/08/20/explicit-is-better-than-implicit-c-implicitly-defined-member-functions/
// https://stackoverflow.com/questions/3734247/what-are-all-the-member-functions-created-by-compiler-for-a-class-does-that-hap
// https://stackoverflow.com/questions/4943958/conditions-for-automatic-generation-of-default-copy-move-ctor-and-copy-move-assi
// https://en.cppreference.com/w/cpp/language/copy_constructor
// https://en.cppreference.com/w/cpp/language/move_constructor
// https://en.cppreference.com/w/cpp/language/copy_assignment
// https://en.cppreference.com/w/cpp/language/move_assignment

#include "common.hpp"

int main() {
    struct C {
        C() = default;
        C(const C&) = default;
        C& operator=(C&) = default;
        C& operator=(const C&) = default;
        C(C&&) = default;
        C& operator=(C&&) = default;
        ~C() = default;
    };
}
