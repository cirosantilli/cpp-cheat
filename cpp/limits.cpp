/*
# limits

    C++ version of climits.

    Contains information on the built-in types, inclding largest and smallest of each type.

    TODO compare to climits which uses macros. Advantage of templates is the scoping?
*/

#include "common.hpp"

int main() {
    std::cout << "max() = "      << std::numeric_limits<int>::max()      << std::endl;
    std::cout << "min() = "      << std::numeric_limits<int>::min()      << std::endl;
    std::cout << "digits = "     << std::numeric_limits<int>::digits     << std::endl;
    std::cout << "is_signed = "  << std::numeric_limits<int>::is_signed  << std::endl;
    std::cout << "is_integer = " << std::numeric_limits<int>::is_integer << std::endl;
    std::cout << "<float>::is_iec559 = " << std::numeric_limits<float>::is_iec559 << std::endl;
    std::cout << "<double>::is_iec559 = " << std::numeric_limits<double>::is_iec559 << std::endl;
    std::cout << "<long double>::is_iec559 = " << std::numeric_limits<long double>::is_iec559 << std::endl;
}
