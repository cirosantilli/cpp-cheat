#include "common.h"

int main(void) {
    char *path = __FILE__ TMPFILE_EXT;
    char in[] = "123\n";
    struct stat s;

    /* Create a test file. */
    int nbytes = strlen(in);
    int fd = open(path, O_WRONLY | O_CREAT, S_IRWXU);
    assert(fd != -1);
    assert(write(fd, in, nbytes) == nbytes);
    close(fd);

    /* Success implies that the file exists.
     * But this can also be done more conveniently access F_OK.
     */
    assert(stat(path, &s) == 0);

    /* Check the size of the file. */
    assert(s.st_size == nbytes);

    /* Check if a path is a file or directory.
     * https://stackoverflow.com/questions/3828192/checking-if-a-directory-exists-in-unix-system-call
     */
    assert(stat(path, &s) == 0 && S_ISREG(s.st_mode));
    assert(stat(".",  &s) == 0 && S_ISDIR(s.st_mode));
    return EXIT_SUCCESS;
}
