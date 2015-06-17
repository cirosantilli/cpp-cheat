/*
# regex

    Finally they are supported!

    Many types are supported: Javascript, grep, awk, ...

    It is probably saner and more powerful to stick to Javascript regexes.
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    // Js has `[:d:]` equivalent POSIX `[:digit:]`.
    std::regex r("a.(c|d)");
#endif
}
