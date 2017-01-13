/**
General boost cheat. Libraries which are too large may be in different files.
*/

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>             // split
#include <boost/filesystem.hpp>                   // -lboost_filesystem -lsystem
#include <boost/iterator/counting_iterator.hpp>
#include <boost/range/algorithm/remove_if.hpp>

int main() {

    // #counting_iterator
    {
        std::vector<int> v(boost::counting_iterator<int>(0), boost::counting_iterator<int>(3));
        assert((v == std::vector<int>{0, 1, 2}));
    }

    //#string
    {
        // #split string into array of strings at a character.
        {
            std::vector<std::string> strs;
            boost::split(strs, "a  b\tcd", boost::is_any_of("\t "));
            assert((strs == std::vector<std::string>{"a", "", "b", "cd"}));
        }

        // # strip
        // #filter
        {
            // Single character, no single function in C++11.
            {
                std::string str = "a0bc00d";
                boost::erase_all(str, "0");
                assert((str == "abcd"));
            }

            // Any character from a string.
            {
                std::string str = "a_bc0_d";
                str.erase(boost::remove_if(str, boost::is_any_of("_0")), str.end());
                assert((str == "abcd"));

                std::vector<int> is{0, 1, 2, 0, 3};
                is.erase(boost::remove_if(is, boost::is_any_of(std::vector<int>{0, 2})), is.end());
                assert((is == std::vector<int>{1, 3}));
            }
        }
    }


    /*
    # filesystem

    # path

    # join

    Proposed for inclusion on TR2.
    */
    {
        std::cout << "filesystem /tmp + foo.txt = " <<
            boost::filesystem::path("/tmp") / boost::filesystem::path("foo.txt") << std::endl;
    }
}
