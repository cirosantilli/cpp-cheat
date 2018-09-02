#define _GNU_SOURCE
#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void* thread_0(void *arg) {
    int i;
    i = 0;
    while (true) {
        printf("t0 %d\n", i);
        sleep(1);
        i++;
    }
    return NULL;
}

void* thread_1(void *arg) {
    int i;
    i = 0;
    while (true) {
        printf("t1 %d\n", i);
        sleep(1);
        i++;
    }
    return NULL;
}

int main(void) {
    enum NUM_THREADS {NUM_THREADS = 2};
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    pthread_create(&threads[0], NULL, thread_0, (void*)&thread_args[0]);
    pthread_create(&threads[1], NULL, thread_1, (void*)&thread_args[1]);
    pthread_setname_np(threads[1], "myname1");
    while (true) {
        printf("main %d\n", i);
        sleep(1);
        i++;
    }
    return EXIT_SUCCESS;
}
