#include "common.hpp"

int main() {
    /*
    # cout

        stdout.

        `ostream` object.

        For tests, std::stringstream shall be used as the results can then be tested,
        and the behaviour is identical to cout.

        `<<` is very magic. You need to understand:

        - operator overload
        - function template argument deduction
        - namespaces adl

        before really understanding why it works.

    # cerr

        Cout for stderr

    # clog

        By default also points to stderr, but can be redirected with TODO.
    */
    {
        std::cout << "cout" << std::endl;
        std::cerr << "cerr" << std::endl;
        std::clog << "clog" << std::endl;
    }

    /*
    # cin

    # stdin

        `istream` object.

        Avoid using it for similar reasons as scanf:

        - hard to handle invalid inputs
        - difficult to predict behaviour

        getline is the best option.
    */
    {
        //std::cout << "Enter an integer:" << endl;
        //std::cin >> i;
        //std::cout << i << std::endl;
    }

    // This is how a very explicit usage of `<<` would look like
    {
        std::stringstream ss;

        //TODO0 how to get his working?
        //std::operator<<<std::ostream,std::string>(ss, "explicit");

        std::operator<<(std::operator<<(ss, "explicit "), "call");
    }

    /*
    # cout unsigned char

        Prints literal bytes.

        http://stackoverflow.com/questions/19562103/uint8-t-cant-be-printed-with-cout/19562163#19562163
    */
    {
        std::cout << (unsigned char)1 << std::endl;
        std::cout << (char)1 << std::endl;
        std::cout << (signed char)1 << std::endl;
        std::cout << (int)1 << std::endl;
        std::cout << (unsigned int)1 << std::endl;
    }
}
