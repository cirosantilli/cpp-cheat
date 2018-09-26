#define _XOPEN_SOURCE 700
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int dir_fd, file_fd;
    char fname[] = __FILE__ ".tmp";

    dir_fd = open(".", O_DIRECTORY);
    assert(dir_fd != -1);
    file_fd = openat(dir_fd, fname, O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    assert(file_fd != -1);
    assert(close(dir_fd) != -1);
    assert(close(file_fd) != -1);
    return EXIT_SUCCESS;
}
