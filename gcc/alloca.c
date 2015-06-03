/*
https://gcc.gnu.org/onlinedocs/gcc-5.1.0/gcc/Variable-Length.html

Allocate on the stack frame.

    man alloca

Thus automatically deallocated when the function returns.

http://stackoverflow.com/questions/1018853/why-is-alloca-not-considered-good-practice
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <time.h> /* time() */

#include <alloca.h> /* alloca */

int f() {
    size_t size = 1 + (time(NULL) % 3);
    int *ip = alloca(size * sizeof(int));
    ip[0] = 1;
    return ip[0];
}

int main() {
    assert(f() == 1);
    return EXIT_SUCCESS;
}
