/* # openat
 *
 * Create a file with a path relative to a given directory.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html
 */

#include "common.h"

int main(void) {
    int dir_fd, file_fd;
    char *fname = __FILE__ ".tmp";

    /* Make sure the file does not exist. */
    if (access(fname, F_OK) == 0) {
        assert(unlink(fname) == 0);
    }

    /* Create the file. */
    dir_fd = open(".", O_DIRECTORY);
    assert(dir_fd != -1);
    file_fd = openat(dir_fd, fname, O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    assert(file_fd != -1);
    assert(close(dir_fd) != -1);
    assert(close(file_fd) != -1);

    /* Assert that the file now exists. */
    assert(access(fname, F_OK) == 0);

    return EXIT_SUCCESS;
}
