// # Implicitly defined functions
//
// - https://stackoverflow.com/questions/12340257/default-vs-implicit-constructor-in-c
// - https://blog.mozilla.org/nfroyd/2015/08/20/explicit-is-better-than-implicit-c-implicitly-defined-member-functions/
// - https://stackoverflow.com/questions/3734247/what-are-all-the-member-functions-created-by-compiler-for-a-class-does-that-hap
// - https://stackoverflow.com/questions/4943958/conditions-for-automatic-generation-of-default-copy-move-ctor-and-copy-move-assi
// - https://en.cppreference.com/w/cpp/language/copy_constructor
// - https://en.cppreference.com/w/cpp/language/move_constructor
// - https://en.cppreference.com/w/cpp/language/copy_assignment
// - https://en.cppreference.com/w/cpp/language/move_assignment

#include "common.hpp"

struct Default {
    int i;
    Default() = default;
    Default(const Default&) = default;
    Default& operator=(Default&) = default;
    Default& operator=(const Default&) = default;
    Default(Default&&) = default;
    Default& operator=(Default&&) = default;
    ~Default() = default;
};

struct Instrument {
    int i;
    static std::vector<std::string> calls;
    Instrument() { calls.push_back("ctor"); }
    Instrument(const Instrument&) { calls.push_back("copy ctor"); }
    Instrument& operator=(Instrument&) { calls.push_back("copy assign"); return *this; }
    Instrument& operator=(const Instrument&) { calls.push_back("copy assign const"); return *this; }
    Instrument(Instrument&&) { calls.push_back("move ctor");  }
    Instrument& operator=(Instrument&&) { calls.push_back("move assign"); return *this; }
    ~Instrument() { calls.push_back("dtor"); }
};
std::vector<std::string> Instrument::calls;

int main() {
    Instrument i;
    assert(Instrument::calls.back() == "ctor");
}
