/*
Expected outcome:

- works with mutex
- fails without

# PTHREAD_MUTEX_INITIALIZER

    New pthread_mutex_t should be initialized to it.

# pthread_mutex_lock

    Acquire mutex: from now one no one else can enter.

    The mutex is required because:

        global++

    is not atomic.

    There are no non-locking atomic types in POSIX:
    http://stackoverflow.com/questions/1130018/unix-portable-atomic-operations

# pthread_mutex_unlock

    Release mutex: from now one others can enter.

# volatile

    We don't need:

        volatile global

    because `pthread_mutex_lock` and many other pthread functions
    already enforce cross thread memory synchronization:
    http://stackoverflow.com/questions/3208060/does-guarding-a-variable-with-a-pthread-mutex-guarantee-its-also-not-cached
*/

#include "common.h"

enum CONSTANTS {
    NUM_THREADS = 1000,
    NUM_ITERS = 1000
};

int global = 0;
pthread_mutex_t main_thread_mutex = PTHREAD_MUTEX_INITIALIZER;

void* main_thread(void *arg) {
    int i;
    for (i = 0; i < NUM_ITERS; ++i) {
#ifndef FAIL
        pthread_mutex_lock(&main_thread_mutex);
#endif
        global++;
#ifndef FAIL
        pthread_mutex_unlock(&main_thread_mutex);
#endif
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, main_thread, NULL);
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);
    assert(global == NUM_THREADS * NUM_ITERS);
    return EXIT_SUCCESS;
}
