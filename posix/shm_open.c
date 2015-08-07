/*
# shm_open

# shm_unlink

    Like open, but creates a fake file that can be passed to mmap.

    The file is never written to disk.

    Application: let two processes share memory.

    Requires `-lrt` for Linux.

    There is also the Linux specific `MAP_ANONYMOUS` `mmap` flag which seems
    to reach a similar effect, but with an unamed `shm_mem`. TODO check.
*/

#include "common.h"

int main() {
    int fd;
    int *map;
    char *name = "/" TMPFILE();
    enum Constexpr { size = sizeof(int) };

    /*
    The name creates a virtual file under `/dev/shm` in Linux.

    Ther seems to be no POSIX way to list the obejcts. E.g. in FreeBDS there isn't:
    http://stackoverflow.com/questions/12430351/how-to-get-list-of-open-posix-shared-memory-segments-in-freebsd
    */
    fd = shm_open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    /* Without ftruncate Linux gives SIGBUS. */
    ftruncate(fd, size);
    map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    *map = 0;
    if (fork() == 0) {
        *map = 1;
        /*
        `man msync` says that only other thing that guarantees write is munmap.

        So I think `wait` is not enough for memory synchronization.
        */
        msync(map, size, MS_SYNC);
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    /* Memory changed across processes! */
    assert(*map == 1);
    /* You *must* do this! If you do not, the object survive (under /dev/shm in Linux). */
    munmap(map, size);
    close(fd);
    shm_unlink(name);
    return EXIT_SUCCESS;
}
