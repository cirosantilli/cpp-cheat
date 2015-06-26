/*
# nullptr

    C++11 keyword.

    Better alternative to `0` and `NULL` ugliness:

    http://stackoverflow.com/questions/1282295/what-exactly-is-nullptr

# nullptr_t

    Type of nullptr.
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    // No address can be nullptr
    {
        std::nullptr_t p = nullptr;
        int i;
        // g++ 4.7 warning: &i will never be null. Smart.
        //assert(&i != p);
    }

    // It is possible to convert NULL and 0 to nullptr_t.
    {
        std::nullptr_t p;
        p = NULL;
        p = 0;
    }

    /*
    It is not possible to convert nullptr_t to NULL and 0

    This allows to overload a function for both pointer and integer.

    In that case, passing it a `0` would always select the integer version.
    */
    {
        //int i = nullptr;
    }

    // Unlike in NULL, the size of nullptr_t is fixed.
    {
        assert(sizeof(std::nullptr_t) == sizeof(void*));
    }
#endif
}
