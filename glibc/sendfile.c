/* # sendfile TODO
 *
 *     man sendfile
 *
 * Transfers data from one FD to another, without passing through userspace as in a read write pair.
 *
 * This is therefore the most efficient way to copy one file into another.
 *
 * Comparison to other methods and implementation:
 *
 * - http://stackoverflow.com/questions/10195343/copy-a-file-in-an-sane-safe-and-efficient-way
 * - https://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
 */

#define _GNU_SOURCE
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int source, dest;
    struct stat stat_source;
    source = open("sendfile.in.tmp", O_RDONLY);
    assert(source != -1);
    dest = open("sendfile.out.tmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    assert(dest != -1);
    assert(fstat(source, &stat_source) != -1);
    assert(sendfile(dest, source, 0, stat_source.st_size) != -1);
    assert(close(source) != -1);
    assert(close(dest) != -1);
    return EXIT_SUCCESS;
}
