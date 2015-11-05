/*
To see if

    ./pthread_count.out &
    cat /proc/$!/status | grep -i thread
    kill $!

shows the right thread count.
*/

#include "common.h"

void* main_thread(void *arg) {
    sleep(1000000);
    return NULL;
}

int main() {
    int i;
    enum NUM_THREADS {NUM_THREADS = 4};
    pthread_t threads[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, main_thread, NULL);
        printf("tid: %ju\n", (uintmax_t)threads[i]);
    }
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
}
