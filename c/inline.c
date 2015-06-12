/*
# inline

    Signals the compiler that it may be worth to copy paste the function instead of calling it.

    The compiler is not obliged to inline.

    Effects:

    - avoids function call, thus potentially faster
    - code gets larger
    - function pointer comparisons may differ for the same function
    - instruction cache might be come less efficient making thigs slower

    Bibliography:

    -   <http://www.greenend.org.uk/rjk/tech/inline.html>

        Some warnings about inline and its usage.
*/

#include "common.h"

/*
This declaration is required!

- http://stackoverflow.com/questions/6312597/is-inline-without-static-or-extern-ever-useful-in-c99
- http://stackoverflow.com/questions/12747198/compiling-error-when-std-gnu99-and-inline-function-is-used
*/
int inline_func(int i);
inline int inline_func(int i) { return i + 1; }

int main () {
    assert(inline_func(0) == 1);
    return EXIT_SUCCESS;
}
