/*
# unique_ptr

Sample use case:

- you want a dynamic array a dynmically allocated derived class
- thus you have to use pointers for polymorphism. Otherwise objects can have different sizes, and arrays can't be used.
- how to prevent memory leaks?

http://en.cppreference.com/w/cpp/memory/unique_ptr
*/

#include "common.hpp"

class Base {
    public:
        static int count;
        Base(int i) : i(i) {
            count++;
        }
        ~Base() {
            count--;
        }
        int i;
};

int Base::count = 0;

/* No memory leaked. Destructors called. */
void unique_ptr_test() {
    std::vector<std::unique_ptr<Base>> bases;
    for (int i = 0; i < 10; ++i) {
        bases.push_back(std::unique_ptr<Base>(new Base(i)));
    }
}

/* Memory leak. Destructors never called. */
void raw_ptr_test() {
    std::vector<Base *> bases;
    for (int i = 0; i < 10; ++i) {
        bases.push_back(new Base(i));
    }
}

void manual_ptr_test() {
    std::vector<Base *> bases;
    for (int i = 0; i < 10; ++i) {
        bases.push_back(new Base(i));
    }
    for (auto base : bases) {
        delete base;
    }
}

int main() {
    /* Basic example. */
    assert(Base::count == 0);
    unique_ptr_test();
    assert(Base::count == 0);
    raw_ptr_test();
    assert(Base::count == 10);
    manual_ptr_test();
    assert(Base::count == 10);

    // Copy constructor is deleted.
    // This is what imposes uniqueness.
    {
        std::unique_ptr<int> p(new int);
        // ERROR.
        //std::unique_ptr<int> p2(p);

        // Consequence: for loops over vectors must use references &.
        // http://stackoverflow.com/questions/20292682/iterating-through-vectorunique-ptrmytype-using-c11-for-loops
        {
            std::vector<std::unique_ptr<int>> is;
            for (auto& i : is) {}
            // ERROR.
            //for (auto i : is) {}
        }

        // Must move glvalues.
        // http://stackoverflow.com/questions/3283778/why-can-i-not-push-back-a-unique-ptr-into-a-vector
        {
            std::vector<std::unique_ptr<int>> is;
            std::unique_ptr<int> i(new int(1));
            is.push_back(std::move(i));
            assert(*is.back() == 1);

            // Without intermediate variable, we don't need to move, because it is an rvalue,
            // and unique_ptr does have an move constructor.
            is.push_back(std::unique_ptr<int>(new int(2)));
            assert(*is.back() == 2);

            // Analogously, must move containers instead of copy.
            {
                std::vector<std::unique_ptr<int>> is;
                is.push_back(std::unique_ptr<int>(new int(1)));
                //std::vector<std::unique_ptr<int>> is2(is);
                std::vector<std::unique_ptr<int>> is2(std::move(is));
                assert(*(is2.front()) == 1);
            }
        }
    }
}
