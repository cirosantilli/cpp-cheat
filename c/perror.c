/* # perror
 *
 * Print a description of errno to stderr with given prefix appended, `NULL` for no prefix.
 *
 * Sample output on glibc 2.23:
 *
 *     perror test EDOM: Numerical argument out of domain
 */

#include "common.h"

int main(void) {
    errno = EDOM;
    perror("perror test EDOM");
    return EXIT_SUCCESS;
}
