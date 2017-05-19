#include "common.hpp"

int main() {
    // String init.
    {
        // Basic.
        {
            std::bitset<4> s("1010");
            std::cout << s << std::endl;
            assert(!s[0]);
        }

        // Missing bits: MSB filled with zeroes.
        {
            std::bitset<4> s("10");
            assert(s == std::bitset<4>("0010"));
        }
    }
}
