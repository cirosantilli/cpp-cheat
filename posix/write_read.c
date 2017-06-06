/*
Write to a file, then read it back to memory.
*/

#include "common.h"

int main(void) {
    char buf[]  = { 'a', 'b', 'c', 'd' };
    char buf2[]  = { 'e', 'f', 'g', 'h' };
    int f, ret;
    size_t off;

    /* write */
    /* Could return less than the requested size if e.g. no more disk space.
     * and that is not considered an error. */
    f = open(__FILE__ ".tmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (f == -1) {
        perror("open");
        assert(0);
    }
    ret = write(f, buf, sizeof(buf));
    if (ret == -1) {
        perror("write");
        assert(0);
    }
    if ((size_t)ret < sizeof(buf)) {
        assert(0);
    }
    close(f);

    /* read
     * Could return less than requested, specially when reading from pipes.
     * So we need to keep reading. 0 means EOF. */
    off = 0;
    f = open(__FILE__ ".tmp", O_RDONLY);
    if (f == -1) {
        perror("open");
        assert(0);
    }
    while ((ret = read(f, buf2 + off, sizeof(buf) - off))) {
        off += ret;
        if (ret == -1) {
            perror("read");
            assert(0);
        }
    }
    close(f);
    assert(!memcmp(buf, buf2, sizeof(buf)));

    return EXIT_SUCCESS;
}
