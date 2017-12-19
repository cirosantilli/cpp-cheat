/*
# unique_ptr

Sample use case:

- you want a dynamic array a dynmically allocated derived class
- thus you have to use pointers for polymorphism. Otherwise objects can have different sizes, and arrays can't be used.
- how to prevent memory leaks?

http://en.cppreference.com/w/cpp/memory/unique_ptr

unique_ptr may incur an extra dereferece cost, but it is usually well worth it.

In Java, everything can be though as a smart pointer (shared),
so using this is still more efficient than Java, since C++ can know the exact
lifetime of objects, and release them immediately when they are done.
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

// Create unique pointer dynamically,
// and transfers ownershipt to caller.
std::unique_ptr<Base> return_unique_ptr() {
    return std::unique_ptr<Base>(new Base(1));
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

    // ERROR: Convert to raw pointer.
    // Not possible, the cast operator is not defined.
    {
        std::unique_ptr<int> p(new int);
        //int *raw = p;
    }

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

    /*
    # reset

    Explicit destruction of pointer. Equivalent to `delete`.

    http://stackoverflow.com/questions/25609457/unique-ptr-explicit-delete
    */
    {
        Base::count = 0;
        std::unique_ptr<Base> p = std::unique_ptr<Base>(new Base(1));
        assert(Base::count == 1);
        p.reset();
        assert(Base::count == 0);
    }

    /*
    # unique_ptr function argments

    -   transfering ownership TODO
        -   use raw pointeres on the interface, and convert it to unique_ptr inside callee
            -   if you already have an unique_ptr, release() it
            -   this allows you to not tie down to a specific smart pointer on the function interface
        -   use unique_ptr on interface and move on caller.
            - Advantage: unique_ptr on interface documents ownership transfer,
                and prevents callee from passing non new pointer to it by mistake.
    - TODO for not transfering ownership:
        - `const & std::unique_ptr<T>`
        - `get()`. Simple and efficient. But how to use it for containers like `vector<std::unique_ptr>`?
        - `T&` on function, `*t` on caller. Looks good!

    - http://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-functionhttp://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
    - http://stackoverflow.com/questions/11277249/how-to-pass-stdunique-ptr-around
    */
    {
    }

    // Return unique_ptr from function.
    {
        {
            Base::count = 0;
            auto base = return_unique_ptr();
            assert(Base::count == 1);
            assert(base->i == 1);
        }
        assert(Base::count == 0);
    }

#if __cplusplus >= 201402L
    // # make_unique
    // Does new and puts it inside unique_ptr. Very convenient.
    {
        {
            Base::count = 0;
            auto base = std::make_unique<Base>(1);
            assert(Base::count == 1);
            assert(base->i == 1);
        }
        assert(Base::count == 0);
    }
#endif
}
