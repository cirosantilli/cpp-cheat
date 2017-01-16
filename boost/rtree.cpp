/*
Contains either:

- Point, Box or Segment, or something adapted to them
- std::pair<Point, Data>
- std::tuple<Point, ..., ...>

Documented at: http://www.boost.org/doc/libs/1_62_0/libs/geometry/doc/html/geometry/spatial_indexes/creation_and_modification.html

TODO

-   randomized perf test vs linear search.

-   ellipses, infinite lines, other parametrized surfaces:
    http://boost-geometry.203548.n3.nabble.com/intersection-between-a-sphere-and-a-line-td4025167.html
*/

#include "common.hpp"

// TODO this must be included separately for BOOST_GEOMETRY_REGISTER_POINT_2D.
#include <boost/geometry/geometries/register/point.hpp>

// Copied from the docs, checking that it works.

    class MyPoint {
        public:
            int x;
            int y;
            int getX() const { return this->x; }
            int getY() const { return this->y; }
            int setX(int x) { this->x = x; }
            int setY(int y) { this->y = y; }
            MyPoint(){}
            MyPoint(int x, int y) : x(x), y(y) {}
    };

    // Magic, equivalent to the large namespace injection below.
    //BOOST_GEOMETRY_REGISTER_POINT_2D(MyPoint, int, bg::cs::cartesian, x, y)
    // Nope, must be able to assign directly to the fields.
    //BOOST_GEOMETRY_REGISTER_POINT_2D(MyPoint, int, bg::cs::cartesian, getX(), getY())

    namespace boost { namespace geometry { namespace traits {
        template<> struct tag<MyPoint>
        { typedef point_tag type; };

        template<> struct coordinate_type<MyPoint>
        { typedef int type; };

        template<> struct coordinate_system<MyPoint>
        { typedef cs::cartesian type; };

        template<> struct dimension<MyPoint> : boost::mpl::int_<2> {};

        template<>
        struct access<MyPoint, 0> {
            static int get(MyPoint const& p) {
                return p.getX();
            }
            static void set(MyPoint& p, int const& value) {
                p.setX(value);
            }
        };

        template<>
        struct access<MyPoint, 1> {
            static int get(MyPoint const& p) {
                return p.getY();
            }
            static void set(MyPoint& p, int const& value) {
                p.setY(value);
            }
        };
    } } }

// Our custom point class.
typedef MyPoint Point;
// Byilt-in point.
//typedef bg::model::point<int, 2, bg::cs::cartesian> Point;
typedef bg::model::box<Point> Box;
typedef std::pair<Point, int> Value;
typedef bgi::rtree<Value, bgi::linear<16>> Rtree;
typedef std::unordered_set<Value::second_type> ValueSet;
typedef std::vector<Value::second_type> ValueVector;

template<typename T>
class MyInsertIterator : public std::insert_iterator<T> {
    public:
        using std::insert_iterator<T>::insert_iterator;
        MyInsertIterator& operator=(const Value& rhs) {
            this->std::insert_iterator<T>::operator=(rhs.second);
        }
};

// Helper to write less for our tests.
// Go go, NRVO!
template<typename Predicates, typename Rtree>
ValueSet getValueSet(const Rtree& rtree, const Predicates& predicates) {
    ValueSet result;
    auto it = rtree.qbegin(predicates);
    auto end = rtree.qend();
    while (it != end) {
        result.insert(it->second);
        ++it;
    }
    return result;

    // TODO why not working
    // Remember that Point is neither hashable nor ordered < >,
    // so direct insertion into set or unordered won't work:
    // we need to get the value out somehow.
    //rtree.query(
        //bgi::intersects(Box(Point(0, 0), Point(4, 4))),
        //MyInsertIterator<decltype(result)>(result, result.end())
    //);
}

// Works, but sometimes hard to verify if correct since order not specified.
template<typename Predicates>
ValueVector getValueVector(const Rtree& rtree, const Predicates& predicates) {
    ValueVector result;
    auto it = rtree.qbegin(predicates);
    auto end = rtree.qend();
    while (it != end) {
        result.push_back(it->second);
        ++it;
    }
    return result;
}

// Adapt pointers to values.
namespace boost { namespace geometry { namespace index {
    template <typename Box>
    struct indexable<Box*>
    {
        typedef Box* V;
        typedef Box const& result_type;
        result_type operator()(V const& v) const { return *v; }
    };
}}}
typedef std::pair<Point*, int> Valuep;
typedef bgi::rtree<Valuep, bgi::linear<16>> Rtreep;

int main() {
    // Basic examples.
    {
        Rtree rtree;
        rtree.insert(Value(Point(1, 1), 1));
        rtree.insert(Value(Point(3, 3), 3));

        // Basic intersect queries.
        assert(
            getValueSet(rtree, bgi::intersects(Box(Point(0, 0), Point(4, 4))))
            == ValueSet({1, 3})
        );
        assert(
            getValueSet(rtree, bgi::intersects(Box(Point(0, 0), Point(2, 2))))
            == ValueSet({1})
        );
        assert(
            getValueSet(rtree, bgi::intersects(Box(Point(2, 2), Point(4, 4))))
            == ValueSet({3})
        );
        assert(
            getValueSet(rtree, bgi::intersects(Box(Point(4, 4), Point(5, 5))))
            == ValueSet({})
        );

        // Edges are counted in.
        assert(
            getValueSet(rtree, bgi::intersects(Box(Point(0, 0), Point(1, 1))))
            == ValueSet({1})
        );
        assert(
            getValueSet(rtree, bgi::intersects(Box(Point(1, 1), Point(2, 2))))
            == ValueSet({1})
        );

        // TODO is nearest first guaranteed?
        // http://stackoverflow.com/questions/41552048/do-boost-geometry-nearest-queries-always-sort-results-ordered-by-smallest-distan
        assert(
            getValueVector(rtree, bgi::nearest(Point(1, 1), 1))
            == ValueVector({1})
        );
        assert(
            getValueVector(rtree, bgi::nearest(Point(1, 1), 2))
            == ValueVector({1, 3})
        );
        assert(
            getValueVector(rtree, bgi::nearest(Point(3, 3), 1))
            == ValueVector({3})
        );
        assert(
            getValueVector(rtree, bgi::nearest(Point(3, 3), 2))
            == ValueVector({3, 1})
        );
        assert(
            getValueVector(rtree, bgi::nearest(Point(0, 0), 2))
            == ValueVector({1, 3})
        );
        assert(
            getValueVector(rtree, bgi::nearest(Point(4, 4), 2))
            == ValueVector({3, 1})
        );
    }

    // Duplicate points.
    {
        Rtree rtree;
        rtree.insert(Value(Point(1, 1), 1));
        rtree.insert(Value(Point(1, 1), 1));
        assert(
            getValueVector(rtree, bgi::intersects(Point(1, 1)))
            == ValueVector({1, 1})
        );

        // .remove() removes only one duplicate at a time.
        rtree.remove(Value(Point(1, 1), 1));
        assert(
            getValueVector(rtree, bgi::intersects(Point(1, 1)))
            == ValueVector({1})
        );
        rtree.remove(Value(Point(1, 1), 1));
        assert(
            getValueVector(rtree, bgi::intersects(Point(1, 1)))
            == ValueVector({})
        );
    }

    // remove
    {
        Rtree rtree;
        rtree.insert(Value(Point(1, 1), 1));
        rtree.insert(Value(Point(1, 1), 2));

        // Sanity check.
        assert(
            getValueSet(rtree, bgi::intersects(Point(1, 1)))
            == ValueSet({1, 2})
        );

        // The entire value must be given and compare == to be removed.
        assert(rtree.remove(std::make_pair(Point(1, 1), 1)) == 1);
        assert(
            getValueVector(rtree, bgi::intersects(Point(1, 1)))
            == ValueVector({2})
        );

        // Return 0 if no removal was done.
        assert(rtree.remove(std::make_pair(Point(1, 1), 1)) == 0);
        assert(
            getValueVector(rtree, bgi::intersects(Point(1, 1)))
            == ValueVector({2})
        );
    }

    // Adapt pointer values.
    // Only the indexable part is adapted in this example.
    // See value_shared_ptr.cpp example in the source tree, same for smart pointers.
    {
        Rtreep rtree;
        rtree.insert(Valuep(new Point(1, 1), 1));
        rtree.insert(Valuep(new Point(3, 3), 3));
        assert(
            getValueSet(rtree, bgi::intersects(Box(Point(0, 0), Point(2, 2))))
            == ValueSet({1})
        );
        // Leak. Smart pointers. Meh.
    }

    // Query by a different type than the key.
    // Like C++14 set comparable finds.
    {
        Rtree rtree;
        rtree.insert(Value(MyPoint(1, 1), 1));
        rtree.insert(Value(MyPoint(3, 3), 3));
        assert(
            getValueSet(rtree, bgi::intersects(bg::model::point<int, 2, bg::cs::cartesian>(1, 1)))
            == ValueSet({1})
        );
    }

    // update
    // TODO: any hint insertion iterator as in std::set? Seems not.

    {
        Rtree rtree;
        rtree.insert(Value(Point(1, 1), 1));
        rtree.insert(Value(Point(3, 3), 3));
        for (const auto& val : rtree) {
            std::cout << val.second << std::endl;
        }
    }
}
