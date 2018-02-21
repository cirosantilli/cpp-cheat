/*
# Headers

    C++ stdlib headers that are not C stdlib headers don't have the `.h` extension,
    and therefore are not included with the `.h` extension.

    Pre-standardized versions of C++ by Stroustrup used the `.h` extension, for example `iostream.h`,
    but this has been deprecated: <http://stackoverflow.com/questions/214230/iostream-vs-iostream-h-vs-iostream-h>
    It may still exits on certain systems, but never rely on it.

    When writting new libs, you can use either `.h` or `.hpp` as extensions.

    Prefer `.hpp` which indicates that the header is C++ specific, and not pure C.
*/

#include <atomic>
#include <algorithm> // copy, erase, lower_bound, remove_if, swap, transform
#include <bitset>
#include <exception> // bad_alloc, bad_cast, bad_exception, bad_typeid, exception, ios_base::failure
#include <fstream> // fstream, ifstream, ofstream
#include <functional> // bind2nd
#include <iostream> // cout, endl
#include <iterator> // advance, input_iterator_tag, iterator, iterator_traits, next
#include <list> // forward_list, list
#include <limits> //
#include <map> // map, multimap
#include <memory> // unique_ptr, shared_ptr
#include <new>
#include <numeric> // partial sums, differences on std::vectors of numbers
#include <ostream> // ostream
#include <ratio> // ratio, nano
#include <random>
#include <set> // multiset, set
#include <string> // getline, string
#include <sstream> // stringstream
#include <typeinfo> // typeid, bad_typeid, bad_typecast
#include <tuple> // tuple
#include <unordered_set>
#include <unordered_map> // unordered_map, unordered_multimap
#include <utility> // forward, get, pair, size_t, type_info, declval
#include <vector> // vector
#include <valarray>

#if __cplusplus >= 201103L
#include <array> // array
#include <chrono> // nanoseconds
#include <mutex> // mutex
#include <regex> // regex
#include <thread> // thread
#include <typeindex> // type_index
#endif

/*
# C headers

    The standard C++ library provides a `cNAME` version to every `NAME.h` for every C header.
    E.g.: `math.h` vs `cmath`.

    The difference is the following:

    -   cX puts things in std:: namespace. *always* use the CNAME version on new code,
        since this reduces the probability of a name conflicts, and is the standard c++ way of doing things.

        Macro expansion happens *before* namespaces are even compiled,
        so you still refer to macros like `EXIT_SUCCESS` and `assert` as in C,
        and *not* as `std::EXIT_SUCCESS`.

    -  `X.h` puts *all* in the global namespace, it is exactly the same as the c headers.
        *never* use it in new code.

        Those headers exist only for backwards compatibility.

    Avoid using C headers and functionality altogether if that functionality has an equivalent C++ version,
    since the C++ version will play more nicely with new language features and libraries.

    http://stackoverflow.com/questions/32606023/when-using-c-headers-in-c-should-we-use-functions-from-std-or-the-global-na
*/
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>

// Keeps a list of functions that called it for testing purposes.
std::vector<std::string> callStack;
void printCallStack() {
    std::cout << "callStack:" << std::endl;
    for (auto& s : callStack)
        std::cout << s << std::endl;
    std::cout << "END callStack" << std::endl;
}

// Global thread parameters.
const int NUM_THREADS = 1000;
const int NUM_ITERS = 1000;
const int NUM_OPS = NUM_THREADS * NUM_ITERS;

// Misc.
bool odd(int i){ return (i % 2) == 1; }

/**
 * Simple instrumented class for tests on constructor destructor order.
 *
 * This class has no members which are objects and no base classes.
 *
 * TODO break this class up.
 * */
class NoBaseNoMember {
    public:

        int i;

        /// Default constructor
        NoBaseNoMember() : i(0) {
            callStack.push_back("NoBaseNoMember::NoBaseNoMember()");
        }

        /// Copy constructor
        NoBaseNoMember(const NoBaseNoMember& other) : i(other.i) {
            callStack.push_back("NoBaseNoMember::NoBaseNoMember(NoBaseNoMember)");
        }

        NoBaseNoMember(int i) : i(i) {callStack.push_back("NoBaseNoMember::NoBaseNoMember(int)");}

        /// Assign
        NoBaseNoMember& operator= (const NoBaseNoMember& rhs) {
            this->i = rhs.i;
            callStack.push_back("NoBaseNoMember::operator=");
            return *this;
        }

        /// Destructor
        ~NoBaseNoMember() { callStack.push_back("NoBaseNoMember::~NoBaseNoMember()"); }

        void method() { callStack.push_back("NoBaseNoMember::method()"); }

        static NoBaseNoMember create() {
            return NoBaseNoMember();
        }

        static NoBaseNoMember createNrvo() {
            NoBaseNoMember c;
            return c;
        }

        /// It would be hard or impossible to do RVO for this function.
        static NoBaseNoMember createNrvoHard(bool b = false) {
            //2 int constructors
            NoBaseNoMember cf = NoBaseNoMember(0);
            NoBaseNoMember ct = NoBaseNoMember(1);
            return b ? ct : cf;
            //2 int destructors
        }

        static void temporaryReference(NoBaseNoMember& temp) {
            temp.i = 0;
        }

        static void temporaryReferenceConst(const NoBaseNoMember& temp) {}
};

class NoBaseNoMember0 {
    public:
        NoBaseNoMember0(){callStack.push_back("NoBaseNoMember0::NoBaseNoMember0()");}
        ~NoBaseNoMember0(){callStack.push_back("NoBaseNoMember0::~NoBaseNoMember0()");}
        void method(){callStack.push_back("NoBaseNoMember0::method()");}
};

class NoBaseNoMember1 {
    public:
        NoBaseNoMember1(){callStack.push_back("NoBaseNoMember1::NoBaseNoMember1()");}
        ~NoBaseNoMember1(){callStack.push_back("NoBaseNoMember1::~NoBaseNoMember1()");}
        void method(){callStack.push_back("NoBaseNoMember1::method()");}
};
