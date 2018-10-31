// https://stackoverflow.com/questions/1135841/c-multiline-string-literal

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    assert(std::string(R"(a)") == std::string("a"));
    assert(std::string(R"(a
b)") == std::string("a\nb"));
    assert(std::string(R"(
a)") == std::string("\na"));
    assert(std::string(R"asdf()")asdf") == std::string(")\""));
#endif
}
