/*
# Dynamic memory

    C++ replaces C's malloc and free with new and delete.

    It is very rare to need explicit dynamic allocation. Always use:

        std::vector<int> is(n)

    instead of:

        int *is = new int[n];

    and `vector<int>(n)` is as efficient and much more flexible than `new int[N]`.

    Dynamic allocation is a dangerous, and it may lead to hard to debug memory leaks.

    Always encapsulate dynamic allocation inside class constructors,
    and free it the destructor, like `std::vector` does.

    Never use C style malloc on C++ code. `new` works better with classes.

# new

    Allocate dynamic memory.

    Throw `std::bad_alloc` in case of error.

# realloc

    There is no direct replacement to realloc or calloc as of C++11
    http://stackoverflow.com/questions/3482941/how-do-you-realloc-in-c
*/

#include "common.hpp"

int main() {
    /*
    Basic usage with proper error checking.
    */
    {
        int* ip;
        try {
            ip = new int[5];
        } catch(std::bad_alloc& ba) {
            assert(false);
        }
        ip[0] = 1;
        delete[] ip;
    }

    /*
    # delete

        Free memory allocatedby `new`.

        Just like C `free`:

        - deleting a `NULL` does nothing.
        - deleting any other pointer twice can lead to memory corruption
        - deleting a pointer which was not dynamically allocated can lead to memory curruption

        Destructor of object pointed to is called.

        A common technique is to set a pointer to `NULL` after it is deleted,
        to avoid deleting a pointer twice:
        <stackoverflow.com/questions/4190703/is-it-safe-to-delete-a-null-pointer>

        An even better techinque may be to use smart pointers and containers.
    */
    {
        delete (int*)NULL;
        delete[] (int*)NULL;

        //delete NULL;
        // WARN: cannot delete an integer type

        //delete (void*)NULL;
        // WARN: cannot delete a void pointer
    }

    // Allocate single object / base type.
    {
        int* ip = new int;
        *ip = 1;
        delete ip;
    }

    // Delete calls destructors of deleted objects.
    {
        callStack.clear();
        NoBaseNoMember* cp = new NoBaseNoMember;
        //NoBaseNoMember* cp = new NoBaseNoMember();
            //SAME
        assert(callStack.back() == "NoBaseNoMember::NoBaseNoMember()");

        cp->method();

        callStack.clear();
        delete cp;
        assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()");
            //calls destructor
    }

    {
        callStack.clear();
        NoBaseNoMember* cp = new NoBaseNoMember[2];
        assert(callStack.back() == "NoBaseNoMember::NoBaseNoMember()"); callStack.pop_back();
        assert(callStack.back() == "NoBaseNoMember::NoBaseNoMember()"); callStack.pop_back();

        cp[0].method();
        cp[1].method();

        callStack.clear();
        delete[] cp;
        assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()"); callStack.pop_back();
        assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()"); callStack.pop_back();
    }

    {
        //int* ip = new int;
        //delete ip;
            //BAD
            //undefined behavior, maybe crash
            //delete ip;
    }

    {
        //int* ip = new int;
        //ip = new int;
        //delete ip;
            //BAD
            //memory leak. memory is lost forever.
    }

    {
        //int* ip;
        //delete ip;
            //BAD
            //undefined behavior, maybe crash
            //ip was not allocated after delete!
    }

    /*
    # calloc

        An analogue effect to calloc can be attained with *value-initialization*.

        http://stackoverflow.com/questions/808464/c-new-call-that-behaves-like-calloc
    */
}
