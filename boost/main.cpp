/**
Boost is the most important C++ utilities library.

It has very widespread use, and some of its features have been included or are candidates for inclusion
on newer versions of the STL.

Full list of libs: <http://www.boost.org/doc/libs/>

Some of boost libraries may be in separate packages / shared objects than others.

The convention is: `-lboost_XXX` to include libs in gcc, for exapmle `-lboost_graph`
*/
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <boost/iterator/counting_iterator.hpp>

using namespace boost;

int main(int, char *[])
{
    //#counting_iterator
    {
        std::vector<int> v(boost::counting_iterator<int>(0), boost::counting_iterator<int>(3));
        assert((v == std::vector<int>{0, 1, 2}));
    }

    return EXIT_SUCCESS;
}
