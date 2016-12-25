/*
# typecast

    Bibliography:

    - http://www.cplusplus.com/doc/tutorial/typecasting/
    - http://stackoverflow.com/questions/28002/regular-cast-vs-static-cast-vs-dynamic-cast
    - http://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-and-reinterpret-cast-be-used
*/

#include "common.hpp"

int main() {
    /*
    Implicit typecast.

    Works if types are convertible, either by the compiler or by a constructor that takes one single argument.
    */
    {
        //convertible basetypes
        //same as in C
        {
            int i = 0.25;
            assert(i == 0);
        }

        // Via constructor that takes a single argument and is not explicit
        // works becaues the constructor `C(int)` exists.
        {
            class C {
                public:
                    int i;
                    C(int i) : i(i) {}
            };
            C c = 1;
            assert(c.i == 1);
        }
    }

    /*
    # explicit typecast
    */
    {
        /*
        # c style typecast

            TODO what does it do in relation to the others? why should it not be used?
        */

        /*
        # dynamic_cast

            - done at runtime
            - only for pointers or references
            - can only be done from / to base derived

                - always works for derived to base

                - baes to derived:

                    - compiles only for polymorphic classes

                    - a runtime check is done to see if the cast is correct or an exception is thrown
        */
        {
        }

        /*
        # reinterpret_cast

            Converts anything to anything by copying bytes.

            Behaviour is not portable in general.
        */

        // Function pointer typecast.
        {
            // Required when a function is overloaded, and you want to use a function pointer.
            // TODO understand syntax.
            {
                std::string s = "a,bc. d";
                auto end = s.end();
                s.erase(std::remove_if(s.begin(), end, (int(*)(int))std::ispunct), end);
                std::cout << s << std::endl;
                assert(s == "abc d");
            }
        }
    }
}
