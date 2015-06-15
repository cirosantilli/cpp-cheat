#include "common.hpp"

// VisibleInnerIterable

    /*
    this is the best way I could find to make a member
    iterable object such as a container available outside

    design goal:

    - to change container type, you only change a single typedef

    difficulty:

    - there is no `Iterator` interface that iterates over anything in the stdlib
        for performance reasons.

        By iterable understand somtehing that has an `::iterator`,
        a `begin()` and an `end()` methods, like stl containers
    */
    class VisibleInnerIterable {
        public:

            VisibleInnerIterable();

            typedef std::vector<int> Iterable;

            const Iterable& getIterable();

        private:

            Iterable iterable;
    };

    VisibleInnerIterable::VisibleInnerIterable() : iterable{0,1,2} {}

    const VisibleInnerIterable::Iterable& VisibleInnerIterable::getIterable() {
        return iterable;
    }

int main() {
    // VisibleInnerIterable
    {
        VisibleInnerIterable c;
        VisibleInnerIterable::Iterable ita = c.getIterable();
        VisibleInnerIterable::Iterable::iterator it = ita.begin();

        int i;
        int is[]{0,1,2};
        for (
            it = ita.begin(), i=0;
            it != ita.end();
            ++it, ++i
        )
        {
            assert(*it == is[i]);
        }
    }

    /*
    # Dynamic multi-dimensional array

        Sources: <http://www.cplusplus.com/forum/articles/7459/>

        In addition to C malloc like techniques, C++ also offers the simpler possibility of using std::vectors
        which will automatically  manage the memory allocation / dellocation for us.

        The tradeoff is that this method will be potentially slower since it:

        -   requires constructor calls at non uniform initialization.

        -   may require function calls for the `[]` operator overload.

            It is however likely that the compiler will inline those.
    */
    {
        // Given width and height.
        {
            int width = 2, height = 3;
            std::vector<std::vector<int>> array_2d(height, std::vector<int>(width));
            array_2d[0][0] = 1;
            array_2d[2][1] = 5;
            assert(array_2d[0][0] == 1);
            assert(array_2d[0][1] == 0);
            assert(array_2d[2][1] == 5);
        }

        // Uniform initialized.
        {
            std::vector<std::vector<int>> array_2d{
                {0, 1},
                {2, 3},
                {4, 5},
            };
            assert(array_2d[0][0] == 0);
            assert(array_2d[2][1] == 5);
        }
    }
}
