#include "common.hpp"

int main() {
    typedef bg::model::point<int, 2, bg::cs::cartesian> Point;

    // get
    {
        Point p(1, 2);
        assert(p.get<0>() == 1);
        assert(p.get<1>() == 2);
    }

    // set
    {
        Point p(1, 2);
        p.set<0>(3);
        assert(p.get<0>() == 3);
    }

    // ==
    {
        assert(bg::equals(Point(1, 2), Point(1, 2)));
    }

    // TODO exercise the cartesian thing.

    // Hash: nope in boost 1.61. Thus cannot put into unordered set.
    // https://github.com/boostorg/geometry/issues/374

    // < > relational operators: nope. Thus cannot put into ordered set.
    // But makes sense, since < > don't have a nice interpretation for 2D points.
    // https://github.com/boostorg/geometry/issues/374
}
