/*
# set

    - unique elements: inserting twice does nothing

    - always ordered: $O(log)$ find / insert

    - immutable elements: it is not possible to modify an object,
        one must first remove it and resinsert.

        This is so because modification may mean reordering.
*/

#include "common.hpp"

int main() {
    // C++11 initializer list
    {
        {
            std::set<int> s{1, 2, 0, 1};
            std::set<int> s2{0, 1, 2};
            assert(s == s2);
        }

        {
            std::set<std::string> s = {"a", "c", "b", "a"};
            std::set<std::string> s1 = {"a","b", "c"};
            assert(s == s1);
        }
    }

    // You can modify objects if you store pointers.
    {
        int i = 0;
        std::set<int*> s;
        s.insert(&i);
        std::set<int*>::iterator it = s.find(&i);
        *(*it) = 1;
        assert(i == 1);
    }

    /*
    # insert

        Like for std::vector, insert makes copies.

        Return is a pair conatining:

        - if the item was not present, an iterator to the item inserted and true
        - if the item was     present, an iterator to the existing item inserted and false
    */
    {
        std::pair<std::set<int,std::string>::iterator,bool> ret;
        std::set<int> s;

        ret = s.insert(1);
        assert(ret.first == s.find(1));
        assert(ret.second == true);

        ret = s.insert(2);
        assert(ret.first == s.find(2));
        assert(ret.second == true);

        ret = s.insert(0);
        assert(ret.first == s.find(0));
        assert(ret.second == true);

        //item already present:
        //nothing is done and returns false on the pair
        ret = s.insert(1);
        assert(ret.first == s.find(1));
        assert(ret.second == false);

        std::set<int> s1 = {0, 1, 2};
        assert(s == s1);
    }

    /*
    # erase

        Remove element from set.

        Returns number of elements removed.
    */
    {
        std::set<int> s = {0, 1, 2};

        assert(s.erase(1) == 1);
        std::set<int> s2 = {0, 2};
        assert(s == s2);

        assert(s.erase(1) == 0);
    }

    // ERROR no random access since it uses bidirection iterator.
    {
        //cout << s[0] << endl;
    }

    //size
    {
        std::set<int> s;
        assert(s.size() == 0);
        s.insert(0);
        assert(s.size() == 1);
    }

    /*
    iterate

        Biderectional iterator.

        Always sorted.
    */

    /*
    find

        If found, returns an iterator pointing to the element.
        Else, returns `map::end()`

        find is `log n` time since the container is ordered.

        log n time complexity since always sorted
    */
    {
        std::set<int> s = {0, 1, 2};
        std::set<int>::iterator it;

        it = s.find(1);
        assert(*it == 1);

        it = s.find(3);
        assert(it == s.end());
    }

    /*
    count

        Count how many times an item is in the set.

        Can only return 1 or 0.

        Equivalent to doing a find.
    */
    {
        std::set<int> s = {1, 2, 0, 1};
        assert(s.count(1) == 1);
        assert(s.count(3) == 0);
    }
}
