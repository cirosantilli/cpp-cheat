#include "common.hpp"

int main() {
    typedef bg::model::point<int, 2, bg::cs::cartesian> Point;
    typedef bg::model::box<Point> Box;

    {
        // Get them.
        {
            Point p1(1, 2);
            Point p2(3, 4);
            Box b(p1, p2);
            assert(bg::equals(b.min_corner(), p1));
            assert(bg::equals(b.max_corner(), p2));
        }

        // TODO: does it make a difference which is which?
        {
            Point p1(3, 4);
            Point p2(1, 2);
            Box b(p1, p2);
            assert(bg::equals(b.min_corner(), p1));
            assert(bg::equals(b.max_corner(), p2));
        }
    }
}
