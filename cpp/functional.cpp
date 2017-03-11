/*
# functional

    Convenient simple functions.

    They implement `operator()`, which allows you to pass them to
    other stdlib functions that take functions as arguments.
*/

#include "common.hpp"

int overload(int i){ return i + 1; }
int overload(int i, int j){ return i + j; }

int default_(int i, int j = 1){ return i + j; }

int main() {
    // # function
    {
        // Disambiguate overload.
        // http://stackoverflow.com/questions/12500411/setting-a-stdfunction-variable-to-refer-to-the-stdsin-function
        {
            std::function<int(int)> f = (int(*)(int))&overload;
            assert(f(1) == 2);
            std::function<int(int, int)> g = (int(*)(int, int))&overload;
            assert(g(1, 2) == 3);
        }

        // Default vaues without bind.
        // TODO possible?
        {
            // Fails. j seems to contain trash.
            //std::function<int(int)> f = (int(*)(int))&default_;
            //assert(f(1) == 2);

            // Lambda workaround.
            std::function<int(int)> f = [](int i){ return default_(i); };
            assert(f(1) == 2);

            std::function<int(int, int)> g = (int(*)(int, int))&default_;
            assert(g(1, 2) == 3);
        }
    }

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

    // # plus
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
