/* https://stackoverflow.com/questions/556405/what-do-real-user-and-sys-mean-in-the-output-of-time1/53937376#53937376
 *
 * Launch N threads that do some useless CPU intensive work:
 *
 *     ./pthread_work.out [niters=1000000000 [nthreads=1]]
 */

#define _XOPEN_SOURCE 700
#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint64_t niters;

void* my_thread(void *arg) {
    uint64_t *argument, i, result;
    argument = (uint64_t *)arg;
    result = *argument;
    for (i = 0; i < niters; ++i) {
        result = (result * result) - (3 * result) + 1;
    }
    *argument = result;
    return NULL;
}

int main(int argc, char **argv) {
    size_t nthreads;
    pthread_t *threads;
    uint64_t rc, i, *thread_args;

    /* CLI args. */
    if (argc > 1) {
        niters = strtoll(argv[1], NULL, 0);
    } else {
        niters = 1000000000;
    }
    if (argc > 2) {
        nthreads = strtoll(argv[2], NULL, 0);
    } else {
        nthreads = 1;
    }
    threads = malloc(nthreads * sizeof(*threads));
    thread_args = malloc(nthreads * sizeof(*thread_args));

    /* Create all threads */
    for (i = 0; i < nthreads; ++i) {
        thread_args[i] = i;
        rc = pthread_create(
            &threads[i],
            NULL,
            my_thread,
            (void*)&thread_args[i]
        );
        assert(rc == 0);
    }

    /* Wait for all threads to complete */
    for (i = 0; i < nthreads; ++i) {
        rc = pthread_join(threads[i], NULL);
        assert(rc == 0);
        printf("%" PRIu64 " %" PRIu64 "\n", i, thread_args[i]);
    }

    free(threads);
    free(thread_args);
    return EXIT_SUCCESS;
}
