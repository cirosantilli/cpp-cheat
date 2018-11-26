// # new
//
// # delete
//
// malloc and free in C++.
//
// As of C++11, you should almost never use new and delete, only:
//
// - containers like std::vector
// - smart pointers like unique_ptr + make_unique
//
// # realloc
//
// There is no direct replacement to realloc or calloc as of C++11
// https://stackoverflow.com/questions/3482941/how-do-you-realloc-in-c

#include "common.hpp"

int main() {
    // Basic usage with proper error checking.
    {
        int *ip;
        try {
            ip = new int[5];
        } catch(std::bad_alloc& ba) {
            assert(false);
        }
        ip[0] = 1;
        delete[] ip;
    }

    // # delete
    //
    // Free memory allocated by `new`.
    //
    // Just like C `free`:
    //
    // - deleting a `NULL` does nothing.
    // - deleting any other pointer twice can lead to memory corruption
    // - deleting a pointer which was not dynamically allocated can lead to memory corruption
    //
    // Destructor of object pointed to is called.
    //
    // A common technique is to set a pointer to `NULL` after it is deleted,
    // to avoid deleting a pointer twice:
    // https://stackoverflow.com/questions/4190703/is-it-safe-to-delete-a-null-pointer
    //
    // An even better technique may be to use smart pointers and containers.
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
        // Same.
        //NoBaseNoMember* cp = new NoBaseNoMember();
        assert(callStack.back() == "NoBaseNoMember::NoBaseNoMember()");

        cp->method();

        callStack.clear();
        delete cp;
        // Calls destructor.
        assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()");
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

    // # calloc
    //
    // An analogue effect to calloc can be attained with *value-initialization*.
    //
    // http://stackoverflow.com/questions/808464/c-new-call-that-behaves-like-calloc
}
