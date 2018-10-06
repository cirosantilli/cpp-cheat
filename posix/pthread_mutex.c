/* # pthread_mutex
 *
 * Assert passes because of mutex:
 *
 *     ./pthread_mutex.out
 *
 * Disable mutex and watch assert fail with very high probability on Ubuntu 18.04:
 *
 *     ./pthread_mutex.out 0
 *
 * thus confirming that the mutex was necessary, otherwise `++` is not atomic,
 * and concurrent accesse mess up with it.
 *
 * There are no non-locking atomic types in POSIX:
 * http://stackoverflow.com/questions/1130018/unix-portable-atomic-operations
 *
 * ## pthread_mutex_lock
 *
 * ## pthread_mutex_unlock
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_lock.html
 *
 * ## volatile is not needed
 *
 * We don't need:
 *
 *     volatile global
 *
 * because `pthread_mutex_lock` and many other pthread functions
 * already enforce cross thread memory synchronization:
 * http://stackoverflow.com/questions/3208060/does-guarding-a-variable-with-a-pthread-mutex-guarantee-its-also-not-cached
*/

#include "common.h"

enum CONSTANTS {
    NUM_THREADS = 1000,
    NUM_ITERS = 1000
};

int global = 0;
int fail = 0;
pthread_mutex_t main_thread_mutex = PTHREAD_MUTEX_INITIALIZER;

void* main_thread(void *arg) {
    COMMON_UNUSED(arg);
    int i;
    for (i = 0; i < NUM_ITERS; ++i) {
        if (!fail)
            pthread_mutex_lock(&main_thread_mutex);
        global++;
        if (!fail)
            pthread_mutex_unlock(&main_thread_mutex);
    }
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t threads[NUM_THREADS];
    int i;
    COMMON_UNUSED(argv);
    fail = argc > 1;
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, main_thread, NULL);
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);
    assert(global == NUM_THREADS * NUM_ITERS);
    return EXIT_SUCCESS;
}
