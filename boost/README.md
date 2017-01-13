# Boost

1.  [main](main.cpp)
1.  [graph](graph.cpp)
1.  [Geometry](geometry.md)
    1. [point](point.cpp)
    1. [box](box.cpp)
    1. [rtree](rtree.cpp)

Boost is the most important C++ utilities library.

It has very widespread use, and some of its features have been included or are candidates for inclusion on newer versions of the stdlib.

Full list of libs: <http://www.boost.org/doc/libs/>

Some of Boost libraries may be in separate packages / shared objects than others.

The library naming convention is: `-lboost_XXX`, e.g. `-lboost_graph`. Whenever you add a new Boost header don't forget to check if you linked to the required dependencies.
