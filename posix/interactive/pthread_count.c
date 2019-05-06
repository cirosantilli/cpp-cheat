/* Launch some very long running threads.
 *
 * Initial motivation: confirm that:
 *
 *     ./pthread_count.out &
 *     cat /proc/$!/status | grep -E '^Threads:'
 *     kill $!
 *
 * shows the right thread count:
 *
 *     Threads:        5
 *
 * which is 1 main thread + 4 we spawned.
 */

#include "common.h"

void* main_thread(void *arg) {
    (void)arg;
    sleep(1000000);
    return NULL;
}

int main(void) {
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
