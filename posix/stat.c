#include "common.h"

int main(void) {
    char fname[] = __FILE__ TMPFILE_EXT;
    char in[] = "123\n";
    struct stat s;

    /* Create a test file. */
    int nbytes = strlen(in);
    int fd = open(fname, O_WRONLY | O_CREAT, S_IRWXU);
    assert(fd != -1);
    assert(write(fd, in, nbytes) == nbytes);
    close(fd);

    /* Success implies that the file exists.. */
    assert(stat(fname, &s) == 0);
    /* Check the size of the file. */
    assert(s.st_size == nbytes);
    return EXIT_SUCCESS;
}
