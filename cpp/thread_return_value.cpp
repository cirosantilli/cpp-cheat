/*
# thread return value

    An actual return value is impossible, you need to use other wrappers:

    - http://stackoverflow.com/questions/7686939/c-simple-return-value-from-stdthread

    Shared state will of course work.

    Passing reference arguments to be modified has weird results:

    - http://stackoverflow.com/questions/28950835/c-error-no-type-named-type-in-class-stdresult-ofvoid-stdunordered
    - http://stackoverflow.com/questions/21048906/stdthread-pass-by-reference-calls-copy-constructor
    - http://stackoverflow.com/questions/8299545/passing-arguments-to-thread-function
    - http://stackoverflow.com/questions/5116756/difference-between-pointer-and-reference-as-thread-parameter
*/

#include "common.hpp"

int main() {
    // TODO
}
