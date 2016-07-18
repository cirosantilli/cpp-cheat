#include "common.hpp"

int main() {
    /*
    # stringstream

    # basic_stringstream

        http://en.cppreference.com/w/cpp/io/basic_stringstream

        An iostream String backed implementation.

        The following is defined:

            typedef basic_stringstream<char> stringstream;

        Very useful to test streams without creating files / stdin.

    # ostringstream

        TODO vs stringstream.

        http://stackoverflow.com/questions/3292107/whats-the-difference-between-istringstream-ostringstream-and-stringstream-w
    */
    {
        // Initialize
        {
            {
                std::stringstream ss("");
                ss << "ab";
                ss << "cd";
                assert(ss.str() == "abcd");
            }

            // empty constructor: TODO everything fails to compile. Why?
            {
                std::stringstream ss();
                //ss << "ab";
                //ss << "cd";
                //assert(ss.str() == "abcd");
            }

            // Nope, works like a file that has come content.
            // http://stackoverflow.com/questions/3840531/what-is-the-purpose-of-ostringstreams-string-constructor
            {
                std::stringstream ss("ab");
                ss << "cd";
                assert(ss.str() == "cd");
            }

            // ostringstream + ate
            {
                std::ostringstream ss("ab", std::ios::ate);
                ss << "cd";
                assert(ss.str() == "abcd");
            }

            // stringstream + ate: TODO fails, why?
            {
                std::stringstream ss("ab", std::ios::ate);
                ss << "cd";
                assert(ss.str() == "ab");
            }
        }

        // Clear
        {
            std::stringstream ss("");
            // Clear stringstream
            // http://stackoverflow.com/questions/20731/in-c-how-do-you-clear-a-stringstream-variable
            ss.str("");
            // Clear flags. Very important, not only for error indicators but also for end of stream.
            ss.clear();
            assert(ss.str() == "");

            // ERROR: use of deleted function because the constructor is =delete.
            //ss = std::stringstream();
        }
    }

}
