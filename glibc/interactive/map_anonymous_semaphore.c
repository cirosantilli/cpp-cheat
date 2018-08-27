/* https://stackoverflow.com/questions/16400820/c-how-to-use-posix-semaphores-on-forked-processes/52042490#52042490 */

#define _GNU_SOURCE
#include <assert.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    pid_t pid;
    typedef struct {
        sem_t sem;
        int i;
    } Semint;

    Semint *semint;
    size_t size = sizeof(Semint);
    semint = (Semint *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
    assert(semint != MAP_FAILED);
    /* 1: shared across processes
     * 0: initial value, wait locked until one post happens (making it > 0)
     */
    sem_init(&semint->sem, 1, 0);
    semint->i = 0;
    pid = fork();
    assert(pid != -1);
    if (pid == 0) {
        sleep(1);
        semint->i = 1;
        msync(&semint->sem, size, MS_SYNC);
        sem_post(&semint->sem);
        exit(EXIT_SUCCESS);
    }
    if (argc == 1) {
        sem_wait(&semint->sem);
    }
    /* Was modified on the other process. */
    assert(semint->i == 1);
    wait(NULL);
    sem_destroy(&semint->sem);
    assert(munmap(semint, size) != -1);
    return EXIT_SUCCESS;
}
