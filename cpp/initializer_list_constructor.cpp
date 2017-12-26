/*
# Brace enclosed initializer list

    See inializer list

# List initialization

    See initializer list constructor.

# Initializer list contructor

    Applications:

    -   you don't know beforehand how many arguments a constructor should receive

        For example, the stdlib std::vector class gets an initializer list constructor on C++11,
        which allows one to initialize it to any constant.

        TODO could this not be achieved via cstdarg?

    -   nice shorthand that omits typing types multiple times.
*/

#include "common.hpp"

#if __cplusplus >= 201103L
/**
 * This class has an `Initializer_list` constructor.
 */
class InitializerListCtor {
    public:

        std::vector<int> v;

        InitializerListCtor(std::initializer_list<int> list) {
            for (auto& i : list)
                v.push_back(i);
        }

        InitializerListCtor(int before, std::initializer_list<int> list, int after) {
            v.push_back(before + 1);
            for (auto& i : list)
                v.push_back(i);
            v.push_back(after - 1);
        }
};
#endif

int main() {
#if __cplusplus >= 201103L
    //STL std::vector usage example
    {
        std::vector<int> v{0, 1};
        // SAME.
        //std::vector<int> v = std::vector<int>({0, 1});
        assert(v[0] == 0);
        assert(v[1] == 1);
        assert(v == std::vector<int>({0, 1}));
        assert((v == std::vector<int>{0, 1}));

        // Assignment also works via implicit conversion.
        v = {1, 0};
        assert((v == std::vector<int>{1, 0}));

        // ERROR: TODO why no implicit conversion is made?
        //assert((v == {0, 1}));
    }

    // How to implemente one.
    {
        {
            InitializerListCtor o{0, 1};
            assert((o.v == std::vector<int>{0, 1}));
        }

        // Initializer list constructor is called
        {
            InitializerListCtor o{0, 0, 0, 0};
            assert((o.v == std::vector<int>{0, 0, 0, 0}));
        }

        // 3 param constructor is called
        {
            InitializerListCtor o(0, {0, 0,}, 0);
            assert((o.v == std::vector<int>{1, 0, 0, -1}));
        }
    }

    /*
    # auto and initializer lists

        auto rule: brace initializer can be bound to auto

        http://en.cppreference.com/w/cpp/utility/initializer_list
    */
    {
        {
            // TODO GCC 5.1 does not allow this, which conflicts with
            // http://en.cppreference.com/w/cpp/utility/initializer_list
            // Who is right?
            //auto l{0, 1, 2};
            // SAME:
            //initializer_list<int> l{0, 1, 2};
            //assert(l.size() == 3);
            //assert(*l.begin() == 0);
        }

        // The rule for auto makes this ranged for work.
        // TODO0 why here? I see an `int`, not an `auto`
        int i = 0;
        for (int x : {0, 1, 2}) {
            assert(x == i);
            i++;
        }
    }
#endif
}
