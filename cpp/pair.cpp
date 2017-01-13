/*
# pair

    Particular case of tuple for two elements (TODO inheritance based?).

    Methods which also exist for tuple will not be discussed.

    Specially important because of `map`.
*/

#include "common.hpp"

template<class T1, class T2>
std::pair<T1, T2> my_make_pair(T1 t1, T2 t2) {
    return std::pair<T1, T2>(t1, t2);
}

int main() {
    // Access: can also be done via `.first` and `.second` in addition to tuple `get`..
    {
        std::pair<int,std::string> p(0, "");
        assert(std::get<0>(p) == p.first);
        assert(std::get<1>(p) == p.second);
    }

    /*
    make_pair

        Saves re-typing the types on the constructor.

        http://stackoverflow.com/questions/9270563/what-is-the-purpose-of-stdmake-pair-vs-the-constructor-of-stdpair/41521422#41521422
    */
    {
        auto p = my_make_pair(1, std::string("one"));
        assert(p.first == 1);
        assert(p.second == "one");
        p = std::make_pair(1, "asdf");
    }

    /*
    # Relational operators

        Lexicographical.

        http://stackoverflow.com/questions/2819245/is-stdpairint-stdstring-ordering-well-defined
    */
    {
        assert(std::make_pair(1, 1) == std::make_pair(1, 1));
        assert(std::make_pair(1, 2) < std::make_pair(2, 1));
        assert(std::make_pair(2, 1) > std::make_pair(1, 2));
    }
}
