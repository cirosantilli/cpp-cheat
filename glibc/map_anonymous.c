/* # MAP_ANONYMOUS
 *
 * `MAP_ANONYMOUS` allows us to use mmap without a backing disk file.
 *
 * Here we see how to share memory across two processes with it.
 *
 * It can therefore replace shm_open, with the advantage that you
 * don't need global names floating around.
 */

#include "common.h"

int main(void) {
    pid_t pid;
    int *addr;

    size_t size = sizeof(int);
    addr = (int *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
    assert(addr != MAP_FAILED);
    *addr = 0;
    pid = fork();
    assert(pid != -1);
    if (pid == 0) {
        *addr = 1;
        msync(addr, size, MS_SYNC);
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    /* Memory changed across processes! */
    assert(*addr == 1);
    /* Does get freed at program termination anyways:
     * https://stackoverflow.com/questions/26569217/do-i-have-to-munmap-a-mmap-file/52041305#52041305 */
    assert(munmap(addr, size) != -1);
    return EXIT_SUCCESS;
}
