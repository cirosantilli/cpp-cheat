/*
# bool

    in C++, unlike in C, bool is part of the language.
*/

#include "common.hpp"

int main() {
    bool b;

    b = true;
    b = 1;

    if (true)
    {
        assert(true);
    }
    if (false)
    {
        assert(false);
    }

    {
        std::stringstream oss;
        oss << true;
        assert(oss.str() == "1");
    }

    {
        std::stringstream oss;
        oss << false;
        assert(oss.str() == "0");
    }
}
