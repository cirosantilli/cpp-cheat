/*
# MAP_PRIVATE

    Creates a copy-on-write version of file in memory.

    Changes do not reflect on the file.

    TODO application? Vs reading everything to memory?
    Maybe pages are only put into memory when you try to read them instead of all at once.
*/

#include "common.h"

int main() {
    char *filepath = TMPFILE();
    int fd;
    int *map;
    const int data = 0;
    enum Constexpr { filesize = sizeof(int) };

    /* Create a file and write 0 to it. */
    {
        fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        write(fd, &data, filesize);
        close(fd);
    }

    /* Private write */
    {
        fd = open(filepath, O_RDONLY, 0);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        map = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
        if (map == MAP_FAILED) {
            close(fd);
            perror("mmap");
            exit(EXIT_FAILURE);
        }

        *map = data + 1;

        if (munmap(map, filesize) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        if (close(fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
    }

    /* Read */
    {
        fd = open(filepath, O_RDONLY, 0);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        map = mmap(0, filesize, PROT_READ, MAP_SHARED, fd, 0);
        if (map == MAP_FAILED) {
            close(fd);
            perror("mmap");
            exit(EXIT_FAILURE);
        }

        /* Did not change! */
        assert(*map == data);

        if (munmap(map, filesize) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        if (close(fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
