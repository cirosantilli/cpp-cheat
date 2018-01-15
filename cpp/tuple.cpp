/*
# tuple

    Hold a ordered collection of elements.

    Each element can be of a different type.

    The length is always fixed.
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    // Create
    {
        // Constructor
        {
            std::tuple<int,char,std::string> t0(0, 'a', "a");
        }

        /*
        # make_tuple

            Analogous to make_pair, but with variable number of arguments. Pretty neat.
        */
        {
            std::tuple<int,char,std::string> t;

            //without make_tuple
            t = std::make_tuple(0, 'a', "a");
            t = std::tuple<int,char,std::string>(0, 'a', "a");

            //with make_tuple
        }

        // Tuple from pair.
        {
            std::tuple<int,char> t2(std::pair<int,char>(0, 'a'));
        }

        // Uniform initialization.
        {
            std::tuple<int,char,std::string> t{0, 'a', "a"};
        }

        // Fails because the tuple constructor are is `explicit`!
        // TODO Rationale? http://stackoverflow.com/questions/14961809/returning-a-tuple-from-a-function-using-uniform-initialization-syntax
        {
            //std::tuple<int, int> t = {0, 1};
            //std::tuple<int, int> t[]{{0, 1}};
        }
    }

    /*
    # get

        Get single element from tuple.

        Returns references, so it is possible to modify the tuples with them.

        Copies are made from input elements
    */
    {
        std::tuple<int,std::string> t(0, "abc");

        assert(std::get<0>(t) == 0);
        assert(std::get<1>(t) == "abc");

        // Can also be used to set tuple values.
        std::get<0>(t) = 1;
        assert(std::get<0>(t) == 1);

        // Or you can modify contained objects.
        std::get<1>(t)[0] = '0';
        assert(std::get<1>(t) == "0bc");

    }

    /*
    # tie

        Unpack a tuple.

        Unpack by reference seems not to be possible: <http://stackoverflow.com/questions/16571883/unpacking-a-std-tuple-into-pointers>

    # ignore

        Magic that exists only to ignore one of tie outputs.
    */
    {
        int i;
        std::string s;
        std::tuple<int,float,std::string> t(1, 1.5, "abc");
        std::tie(i, std::ignore, s) = t;
        assert(i == 1);
        assert(s == "abc");

        // Clearly copies are made.
        i = 2;
        assert(std::get<0>(t) == 1);

        // Tie and declare variables at the same time. Nope?
        // Tie saves assignments, but repeats types which we can get rid of with auto.
        // If only we could save both types and assignments...
        // http://stackoverflow.com/questions/29312154/how-to-create-a-new-variable-and-use-stdtie-at-the-same-time
        // http://codereview.stackexchange.com/questions/61499/a-tuple-unpacking-macro-that-approximates-python-elegance

        // Structured bindings
        // https://stackoverflow.com/questions/29312154/how-to-create-a-new-variable-and-use-stdtie-at-the-same-time
        {
#if __cplusplus >= 201703L
            auto tuple = std::make_tuple(1, 'a', 2.3);
            auto [i, c, d] = tuple;
            assert(i == 1);
            assert(c == 'a');
            assert(d == 2.3);
#endif
        }
    }

    /*
    Relational operators operations are implemented

    http://www.cplusplus.com/reference/tuple/tuple/operators/>

    `<` family is lexicographical.
    */
    {
        std::tuple<int,char> t0(0, 'a');
        std::tuple<int,char> t1(0, 'a');
        std::tuple<int,char> t2(1, 'b');
        std::tuple<int,char> t3(-1, 'b');
        std::tuple<int,char> t4(0, 'b');

        assert(t0 == t1);
        assert(t0 != t2);
        assert(t0 < t2);
        assert(t0 > t3); //-1 counts
        assert(t0 < t4); //0 ties, 'a' < 'b'
    }

    // Swap contents of two tuples of same type
    {
        std::tuple<int,char> t0(0, 'a');
        std::tuple<int,char> t1(1, 'b');

        std::tuple<int,char> old_t0 = t0;
        std::tuple<int,char> old_t1 = t1;

        t0.swap(t1);

        assert(t0 == old_t1);
        assert(t1 == old_t0);
    }
#endif
}
