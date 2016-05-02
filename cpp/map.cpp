/*
# map

    http://www.cplusplus.com/reference/map/map/

    Also comes in an unordered version `unordered_map`.

    Ordered.

    Also comes in an multiple value input version `multimap`.

    Does not require a hash function. Usually implemented as a self balancing tree such as a rb tree.

# unordered_map

    TODO complexity comparison to map.

# hashmap

    There seems to be no explicit hashmap container, only a generic map interface,

    See map.

    Nonstandard `hash_map` already provided with gcc and msvc++.
    It is placed in the `std::` namespace, but it is *not* ISO.
*/

#include "common.hpp"

template <class K, class V>
std::string map_to_str(std::map<K,V> map) {
    std::stringstream result;
    for (auto& pair : map) {
        result << pair.first << ":" << pair.second << ", ";
    }
    return result.str();
}

int main() {
    /*
    The initializer list constructor makes things very easy.
    */
    {
        std::map<int,std::string> m{
            {0, "zero"},
            {1, "one"},
            {2, "two"},
        };
    }

    /*
    emplace

        put a value pair into the map without creating the pair explicitly

        needs gcc 4.8: <http://stackoverflow.com/questions/15812276/stdset-has-no-member-emplace>
    */
    {
        //std::map<int,std::string> m;
        //m.emplace(0, "zero");
        //m.emplace(1, "one");
        //m.emplace(2, "two");
    }

    /*
    # insert

        Insert pair into map.

        The return value is similar to that of a set insertion with respec to the key.
    */
    {
        std::map<int,std::string> m;
        std::pair<std::map<int,std::string>::iterator,bool> ret;

        ret = m.insert(std::pair<int,std::string>(0, "zero"));
        assert(ret.first == m.find(0));
        assert(ret.second == true);

        ret = m.insert(std::pair<int,std::string>(1, "one"));
        assert(ret.first == m.find(1));
        assert(ret.second == true);

        //key already present
        ret = m.insert(std::pair<int,std::string>(1, "one2"));
        assert(m[1] == "one");
        assert(ret.first == m.find(1));
        assert(ret.second == false);
    }

    /*
    iterate

        Map is ordered.

        It is iterated in key `<` order.

        Iteration returns key value pairs.
    */
    {
        std::map<int,std::string> m{
            {1, "one"},
            {0, "zero"},
        };

        int i = 0;
        int is[] = {0, 1};
        for (auto& im : m) {
            assert(im.first == is[i]);
            //cout << im->second << endl;
            ++i;
        }
        assert(i == 2);
        assert(map_to_str(m) == "0:zero, 1:one, ");
    }

    /*
    [] operator

        get value from a given key

        WARNING: if the key does not exist, it is inserted with a value with default constructor.

        This can be avoided by using `find` instead of `[]`.
    */
    {
        std::map<int,std::string> m{
            {0, "zero"},
            {1, "one"},
        };

        assert(m[0] == "zero");
        assert(m[1] == "one");

        // Inserts `(2,"")` because `""` is the value for the default String constructor.
        assert(m[2] == "");
        assert(m.size() == 3);
    }

    /*
    # find

    # check if in map

        Similar to `std::set` find with respect to the keys:
        returns an iterator pointing to the pair which has given key, not the value.

        If not found, returns `map::end()`

        This is perferrable to `[]` since it does not insert non-existent elements.
    */
    {
        std::map<int,std::string> m{
            {0, "zero"},
            {1, "one"},
        };

        assert(m.find(0)->second == "zero");
        assert(m.find(1)->second == "one");

        assert(m.find(2) == m.end());
        assert(m.size() == 2);
    }

    /*
    erase

        Remove element from map.

        Returns number of elements removed.
    */
    {
        int ret;

        std::map<int,std::string> m{
            {0, "zero"},
            {1, "one"},
        };

        std::map<int,std::string> m2;
        m2.insert(std::pair<int,std::string>(0, "zero"));

        ret = m.erase(1);
        assert(ret = 1);

        assert(m == m2);

        ret = m.erase(1);
        assert(ret == 0);
    }
}
