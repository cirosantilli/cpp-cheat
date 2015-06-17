/*
# functional

    Convenient simple functions.

    They implement `operator()`, which allows you to pass them to
    other stdlib functions that take functions as arguments.
*/

#include "common.hpp"

int main() {
    /*
    # bind2nd

        TODO Deprecated?

        Tranform a function that takes two arguments into a function that takes only the first.

        Useful with stdlib functions that must take functions that take a single argument,
        but you want to pass an extra parameter to that function.
    */
    {
        /*
        std::vector<int> v = {2, 0, 1};
        assert(std::find_if (
            v.begin(),
            v.end(),
            std::bind2nd([](int i, int param){return i == param + 1;}, 1)
        ) == v.begin());
        */
    }

    /*
    # plus
    */
    {
        assert(std::plus<int>()(1, 2) == 3);
    }

#if __cplusplus >= 201103L
    /*
    # hash

        http://www.cplusplus.com/reference/functional/hash/

        The stdlib furnishes overloaded hash functions for stdlib containers.

        Those functions are implemented as callable classes that implement `()`.

        For base types, those hashes are found under the `functional`.

        For std::vectors, only `std::vector<bool>` has a template.

        For other types, they are found in the same header that defines those types:
        ex: hash for std::vectors is under `<vector>`.

        Returns a `size_t` result.
    */
    {
        std::cout << "hash" << std::endl;
        std::cout << "  1 = " << std::hash<int>()(1) << std::endl;
        std::cout << "  string abc = " << std::hash<std::string>()("abc") << std::endl;
    }
#endif
}
