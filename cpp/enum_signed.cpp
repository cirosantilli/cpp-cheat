// https://stackoverflow.com/questions/159034/are-c-enums-signed-or-unsigned/54572423#54572423

#include <cassert>
#include <iostream>
#include <type_traits>

enum Unscoped {};
enum class ScopedDefault {};
enum class ScopedExplicit : long {};

int main() {
    std::cout << std::is_signed<std::underlying_type<Unscoped>>() << std::endl;
    assert((std::is_same<std::underlying_type<ScopedDefault>::type, int>()));
    assert((std::is_same<std::underlying_type<ScopedExplicit>::type, long>()));
}
