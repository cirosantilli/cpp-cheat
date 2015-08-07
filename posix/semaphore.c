/*
# Semaphore

# semget

# semctl

# semop

    Process synchronization.

    In this example, processes communicate through `mmap`.

    Implemented in Linux by equally named system calls.

    This example uses a semaphore to ensure that mmaped read / write
    is synchronized across two processes.
*/

#include "common.h"

int main() {
    /* Not defined in any header, we must define it ourselves! TODO why? */
    union semun mysemun;
    int fd;
    int *map;
    char *name = "/" TMPFILE();
    /* ID to a set of semaphores. */
    int semid;
    enum Constexpr { size = sizeof(int) };
    struct sembuf mysembuf;

    /* First semaphore in set. */
    mysembuf.sem_num = 0;
    /* No special options for operation */
    mysembuf.sem_flg = 0;
    /* Returns the ID to a new set of semaphores. */
    semid = semget(
        /* Create new semaphores, don't reuse existing ones. */
        IPC_PRIVATE,
        /* How many semaphores to create in the set. */
        1,
        /* Open-like permissions. */
        S_IRUSR | S_IWUSR
    );
    mysemun.val = 1;
    /* Set the semaphore values to 1. */
    semctl(semid, 0, SETVAL, mysemun);
    fd = shm_open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    ftruncate(fd, size);
    map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    *map = 0;
    if (fork() == 0) {
        *map = 1;
        msync(map, size, MS_SYNC);
        /* Subtract 1. */
        mysembuf.sem_op = -1;
        semop(
            semid,
            /* Array of operations to do. Here a single one. */
            &mysembuf,
            /* The length of the mysembuf array is 1: single element case. */
            1
        );
        exit(EXIT_SUCCESS);
    }
    /* Wait for 0. */
    mysembuf.sem_op = 0;
    semop(semid, &mysembuf, 1);
    assert(*map == 1);
    wait(NULL);
    assert(*map == 1);
    munmap(map, size);
    close(fd);
    shm_unlink(name);
    return EXIT_SUCCESS;
}
