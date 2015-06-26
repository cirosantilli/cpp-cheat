/*
Optional language feature, checked with `__STDC_NO_ATOMICS__`.

Modeled on C++ `std::atomic` and analogous to it, just without using C++ language features.

# _Atomic

    - http://stackoverflow.com/questions/24557728/does-any-c-library-implement-c11-threads-for-gnu-linux

# ATOMIC_VAR_INIT

    Required to initialize auto `_Atomic`, but not globals

    - http://stackoverflow.com/questions/15317666/how-to-initialize-and-use-a-c11-atomic-variable
*/

#ifndef __STDC_NO_ATOMICS__
#include <assert.h>
#include <pthread.h>
/* Not in GCC 5.1 yet. */
/*#include <threads.h>*/
#include <stdlib.h>

enum CONSTANTS {
    NUM_THREADS = 1000,
    NUM_ITERS = 1000
};

_Atomic int global = 0;

void* main_thread(void *arg) {
    int i;
    for (i = 0; i < NUM_ITERS; ++i) {
        /*
        Postrix ++ and compound assignment are atomic. TODO Other operators?

        Other operations need `stdatomic` functions.

        6.5.2.4/2 "Postfix increment and decrement operators"

        > Postfix ++ on an object with atomic type is a read-modify-write operation
        with memory_order_seq_cst memory order semantics.

        6.5.16.2/3 "Compound assignment":

        > If E1 has an atomic type, compound assignment is a read-modify-write operation
        with memory_order_seq_cst memory order semantics.
        */
        global++;
    }
    return NULL;
}
#endif

int main() {
#ifndef __STDC_NO_ATOMICS__
    int i;

    pthread_t threads[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, main_thread, NULL);
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);

    /* Not in GCC 5.1 yet. */
    /*
    thrd_t thr[NUM_THREADS];
    for(int i = 0; n < NUM_THREADS; ++n)
        thrd_create(&thr[i], main_thread, NULL);
    for(int n = 0; n < NUM_THREADS; ++n)
        thrd_join(thr[i], NULL);
    */

    /* Loads and stores are atomic. */
    assert(global == NUM_THREADS * NUM_ITERS);
#endif
    return EXIT_SUCCESS;
}
