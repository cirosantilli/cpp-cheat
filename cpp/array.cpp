/* https://stackoverflow.com/questions/4424579/stdvector-versus-stdarray-in-c */

#include "common.hpp"

int main() {
    std::array<int, 3> a{{0, 1, 2}};
    assert(a.size() == 3);
    // No implicit bounds checks.
    //std::cout << a[4] << std::endl;
}
