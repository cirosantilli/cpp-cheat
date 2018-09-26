/* # access
 *
 * Check if a file exists and its permissions.
 *
 * Just a convenient subset of stat().
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/access.html
 */

#include "common.h"

int main(void) {
    char *path;

    /* "." exists. */
    path = ".";
    if (access(path, F_OK) == -1) {
        perror("access");
        assert(false);
    }

    /* Cannot exist since /dev/null is specified to be a file by POSIX. */
    path = "/dev/null/asdf";
    if (access(path, F_OK) != -1) {
        assert(false);
    }

    return EXIT_SUCCESS;
}
