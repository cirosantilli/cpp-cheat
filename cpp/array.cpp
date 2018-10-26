/* # std::array
 *
 * https://stackoverflow.com/questions/4424579/stdvector-versus-stdarray-in-c
 *
 * Basically: never use raw arrays in C++, use this instead.
 * It is better in every sense.
 */

#include "common.hpp"

int main() {
    std::array<int, 3> a{{0, 1, 2}};

    assert(a.size() == 3);

    // No implicit bounds checks.
    //std::cout << a[4] << std::endl;

    // But does have some goodies, since it knows the array size,
    // e.g. operator== comparison.
    assert((std::array<int, 3>{1, 2, 3} == std::array<int, 3>{1, 2, 3}));

    // Nah, can't deduce size from initializer:
    // https://stackoverflow.com/questions/6114067/how-to-emulate-c-array-initialization-int-arr-e1-e2-e3-behaviou
    // std::array<int>{1, 2, 3}

    // But does not have any constructor goodies, e.g. fill constructor:
    //std::array<int, 3>(24);
    // Maybe this is to make it POD?
    static_assert(std::is_pod<std::array<int, 1>>());
}
