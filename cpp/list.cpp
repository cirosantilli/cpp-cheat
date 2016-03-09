/*
# list

    Doubly linked list.

    Advantages over std::vector: fast inservion and removal from middle.

    Unless you really need those operations fast, don't use this data structure.

    No random access.

# forward_list

    Like list, but singly linked, and therefore not backwards interable.
*/

#include "common.hpp"

int main() {
    // Initializer list constructor
    {
        std::list<int> l{0, 1};
    }

    // # emplace
    {
        std::list<int> l{0, 1};
        l.emplace(++l.begin(), 2);
        assert(l == std::list<int>({0, 2, 1}));
    }

    // # remove: remove all elements with a given value from list
    {
        std::list<int> l{0, 1, 0, 2};
        l.remove(0);
        assert(l == std::list<int>({1, 2}));
    }

    // # splice: transfer elements from one list to another
    {
        std::list<int> l{0, 1};
        std::list<int> l2{2, 3};
        l.splice(++l.begin(), l2);
        assert(l == std::list<int>({0, 2, 3, 1}));
        assert(l2 == std::list<int>());
    }
}
