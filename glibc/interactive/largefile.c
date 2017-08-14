/*
https://stackoverflow.com/questions/2888425/is-o-largefile-needed-just-to-write-a-large-file

If you compile with -m32, the program only works if _FILE_OFFSET_BITS is defined.

In 64-bit, it does not matter.

Ubuntu 16.04.

I think this passes O_LARGEFILE on the open of the 32-bit syscall.
*/
#define _FILE_OFFSET_BITS 64

#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char buf[BUFSIZ];

int main(int argc, char **argv) {
    int fd;
    off_t i, imax, pow;
    ssize_t ret;

    if (argc > 1) {
        pow = strtoumax(argv[1], NULL, 10);
    } else {
        pow = 32;
    }
    fd = open(__FILE__ ".tmp", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        assert(0);
    }
    imax = ((off_t)1 << pow) / BUFSIZ;
    for (i = 0; i < imax; ++i) {
        ret = write(fd, buf, BUFSIZ);
        if (ret == -1) {
            perror("write");
            assert(0);
        }
    }
    close(fd);
    return EXIT_SUCCESS;
}
