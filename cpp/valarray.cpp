/*
# valarray

    Array of values. Wors much like a mathematical vector.

    Container that overloads many mathematical operations in a similar way to what Fortran does,
    which may be more efficient and convenient.

    Very obscure, for several reasons:

    - other techniques achieve what it achieves
    - low compiler support

    Downsides compared to vectors:

    - not resizable, so no push_back

    <http://stackoverflow.com/questions/1602451/c-valarray-vs-vector>
*/

#include "common.hpp"

int main() {
    std::valarray<int> v;
    std::valarray<int> v0{0, 1, 2};
    std::valarray<int> v1{3, 4, 5};

    assert(v0.sum() == 3);
    assert(v0.min() == 0);
    assert(v0.max() == 2);

    /*
    v = v0;
    v.cshift(1);
    assert((v == std::valarray<int>{1, 2, 0}).min());
    */

    // == is elementwise equality.
    //
    // For equality of all elements, do `.min() == true`
    {
        std::valarray<int> v0{0, 1, 2};
        std::valarray<int> v1{0, 2, 2};
        assert(((v0 == v1) == std::valarray<bool>{true, false, true}).min());

    }

    // +, -, *, /, etc are overloaded elementwise.
    //
    // They are also overloaded for contained data type.
    {
        assert((v0 + v1 == std::valarray<int>{3, 5, 7}).min());
        assert((v0 +  1 == std::valarray<int>{1, 2, 3}).min());
    }

    // Basic cmath functions are overloaded for valarray elementwise.
    {
        assert((abs(std::valarray<int>{-1, 0, 1})    == std::valarray<int>{1, 0, 1}).min());
        assert((pow(std::valarray<int>{-2, 0, 2}, 2) == std::valarray<int>{4, 0, 4}).min());
    }
}
