#include "common.hpp"

int main() {
    // # Aggregate initialization
    //
    // Aggregate is a form of initializer list constructor.
    //
    // That constructor gets defined automatically.
    //
    // It is only available for aggregate types.
    //
    // Having such a constructor seems to be the main property of aggregates.
    // https://en.cppreference.com/w/cpp/language/aggregate_initialization
    {
        struct C {
            int i;
            int j;
        };

        struct D {
            int i;
            int j;
            C c;
        };

#if __cplusplus >= 201703L
        static_assert(std::is_aggregate<C>());
        static_assert(std::is_aggregate<D>());
#endif

        // Works like C struct.
        {
            C c{1, 2};
            assert(c.i == 1);
            assert(c.j == 2);
        }

        // Like C struct again.
        {
            C c{1};
            assert(c.i == 1);
            assert(c.j == 0);
        }

        // Also like C when there are sub-structs..
        {
            D d{1, 2, {3, 4}};
            assert(d.i == 1);
            assert(d.j == 2);
            assert(d.c.i == 3);
            assert(d.c.j == 4);
        }

        // With private members, it is not an aggregate type.
        {
            struct E {
                private:
                    int i;
                    int j;
            };

#if __cplusplus >= 201703L
            static_assert(!std::is_aggregate<E>());
#endif

            // ERROR. No such constructor.
            //E e{1, 2};

            // Being POD does not imply being an aggregate.
            static_assert(std::is_pod<E>());
        }
    }

    // TODO full list of everything that makes something not aggregate.
    {
    }
}
