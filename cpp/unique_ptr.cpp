/* # unique_ptr
 *
 * Sample use case:
 *
 * - you want a dynamic array a dynamically allocated derived class
 * - thus you have to use pointers for polymorphism. Otherwise objects can have different sizes, and arrays can't be used.
 * - how to prevent memory leaks?
 *
 * http://en.cppreference.com/w/cpp/memory/unique_ptr
 *
 * unique_ptr may incur an extra dereferece cost, but it is usually well worth it.
 *
 * In Java, everything can be though as a smart pointer (shared),
 * so using this is still more efficient than Java, since C++ can know the exact
 * lifetime of objects, and release them immediately when they are done.
 */

#include "common.hpp"

class Base {
    public:
        static int count;
        Base() : Base(0) {}
        Base(int i) : i(i) {
            count++;
        }
        ~Base() {
            count--;
        }
        int i;
};
int Base::count = 0;

// Create unique pointer dynamically,
// and transfers ownership to caller.
std::unique_ptr<Base> return_unique_ptr() {
    return std::unique_ptr<Base>(new Base(1));
}

int main() {
    /* Basic examples. */
    {
        // This is the problem case that we are trying to solve: memory leaks
        {
            {
                Base *base = new Base(1);
                assert(base->i == 1);
                assert(Base::count == 1);
                // You will forget to do this one day.
                //delete base;
            }
            // Then base is lost forever: it went out of scope.
            // And the memory has leaked.
            assert(Base::count == 1);
            // Hack up the count for future tests.
            Base::count = 0;
        }

        // This is how unique_ptr solves it.
        {
            {
                std::unique_ptr<Base> base(new Base(1));
                assert(base->i == 1);
                assert(Base::count == 1);
            }
            // Destructor called automatically! No memory leaks!
            assert(Base::count == 0);
        }

    }

    /* More commonly, the pointers are inside another container.
     * When the parent goes out of scope, it just calls the
     * child constructors in the same way.
     */
    {
        {
            std::vector<std::unique_ptr<Base>> bases;
            bases.push_back(std::unique_ptr<Base>(new Base(0)));
            bases.push_back(std::unique_ptr<Base>(new Base(1)));
            assert(bases[0]->i == 0);
            assert(bases[1]->i == 1);
            assert(Base::count == 2);
        }
        assert(Base::count == 0);
    }

    // Convert to raw pointer.
    {
        std::unique_ptr<int> p(new int);
        int *raw;

        // Not possible, the cast operator is not defined.
        //raw = p;

        // But can be done explicitly with .get().
        raw = p.get();
    }

    // Copy constructor is deleted.
    // This imposes uniqueness of ownership.
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

    // # reset
    {
        /* With no arguments, explicitly destroy the pointer. Equivalent to `delete`.
         *
         * http://stackoverflow.com/questions/25609457/unique-ptr-explicit-delete
         */
        {
            std::unique_ptr<Base> p(new Base(1));
            assert(Base::count == 1);
            p.reset();
            assert(Base::count == 0);
        }

        // Reset with an argument
        // does what you would expect: release and replace,
        // just like assignment.
        {
            std::unique_ptr<Base> p(new Base(1));
            assert(p->i == 1);
            assert(Base::count == 1);

            /* Nope. TODO why?
             *
             * - https://stackoverflow.com/questions/48104034/why-cant-i-assign-to-unique-ptr-of-type-uint-8
             * - https://stackoverflow.com/questions/34882140/why-cant-a-pointer-be-automatically-converted-into-a-unique-ptr-when-returning
             */
            //p = new Base(2);

            // Yup.
            p = std::unique_ptr<Base>(new Base(2));
            assert(p->i == 2);
            assert(Base::count == 1);

            // Yup, same. Less verbose, I like it.
            p.reset(new Base(3));
            assert(p->i == 3);
            assert(Base::count == 1);
        }
        assert(Base::count == 0);
    }

    /* # unique_ptr function arguments
     *
     * -   transferring ownership TODO examples
     *     -   use raw pointers on the interface, and convert it to unique_ptr inside callee
     *         -   if you already have an unique_ptr, release() it
     *         -   this allows you to not tie down to a specific smart pointer on the function interface
     *     -   use unique_ptr on interface and move on caller.
     *         - Advantage: unique_ptr on interface documents ownership transfer,
     *             and prevents callee from passing non new pointer to it by mistake.
     * - TODO for not transferring ownership:
     *     - `const & std::unique_ptr<T>`
     *     - `get()`. Simple and efficient. But how to use it for containers like `vector<std::unique_ptr>`?
     *     - `T&` on function, `*t` on caller. Looks good!
     *
     * - http://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-functionhttp://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
     * - http://stackoverflow.com/questions/11277249/how-to-pass-stdunique-ptr-around
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

    /* Array inside unique_ptr
     * https://stackoverflow.com/questions/16711697/is-there-any-use-for-unique-ptr-with-array
     */
    {
        size_t n = 2;
        Base::count = 0;
        {
            std::unique_ptr<Base[]> array(new Base[n]);
            array[0].i = 1;
            array[0].i = 1;
            assert(Base::count == 2);
        }
        assert(Base::count == 0);
    }
}
