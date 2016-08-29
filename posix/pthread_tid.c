/*
Print thread TID and other info for multiple threads.
*/

#include "common.h"

pthread_mutex_t main_thread_mutex = PTHREAD_MUTEX_INITIALIZER;

void* main_thread(void *arg) {
    int argument;
    argument = *((int*)arg);
    printf("tid = %d\n", argument);
    printf("  getpid() = %ju\n", (uintmax_t)getpid());
    printf("  pthread_self() = %ju\n", (uintmax_t)pthread_self());
    return NULL;
}

int main(void) {
    enum NUM_THREADS {NUM_THREADS = 5};
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int rc, i;

    /* Create all threads */
    for (i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        rc = pthread_create(&threads[i], NULL, main_thread, (void*)&thread_args[i]);
        assert(rc == 0);
        printf("tid: %ju\n", (uintmax_t)threads[i]);
    }

    /* Wait for all threads to complete */
    for (i = 0; i < NUM_THREADS; ++i) {
        rc = pthread_join(threads[i], NULL);
        if (rc != 0) {
            printf("%s\n", strerror(rc));
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
