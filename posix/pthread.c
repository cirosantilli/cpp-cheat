/*
# pthread

# Threads

    Sources:

    - https://computing.llnl.gov/tutorials/pthreads/

    POSIX threads.

    Complex model with around 100 functions prefixed by `pthread`.

    c11 and C++11 introduced a standard threading model, so in time this may become less important

    Each thread has its own stack, but unlike process, global memory is shared.

    Quicker to start than a process because less resource copy is needed.

    In Linux they are based on the `clone` system call.

    In GCC you must compile with `-pthread`.

# Thread synchronization mechanisms

    - mutexes - Mutual exclusion lock: Block access to variables by other threads.
        This enforces exclusive access by a thread to a variable or set of variables.

    - joins - Make a thread wait till others are complete (terminated).

    - condition variables - data type pthread_cond_t

    Good tutorial: <http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html#SYNCHRONIZATION>

# pthread_create

    Create a new thread.

        int pthread_create(
            pthread_t *restrict thread,
            const pthread_attr_t *restrict attr,
            void *(*start_routine)(void*),
            void *restrict arg
        )

    -   `thread`

        Return value.

        Unique id of the created thread.

        Can be retreived from the thread with `pthread_self()`

        In POSIX all threads of a process have the same PID. TODO confirm with reference

    -   `attr`: set thread attributes. `NULL` for defaults.

    -   `start_routine`: function that runs the thread code

        If this function does `return x`, it is the same as calling `pthread_exit(x)`.

        This value can then be retreive from `pthread_join`.

    -   `arg`: argument to `start_routine`, `NULL` if none.

# pthread_join

    Wait for a given thread to terminate.

    If it has already terminated, does not wait.

# pthread_self

    Get thread id of current running thread.

    Same value that is returned through the `thread` argument of `pthread_create`.

    Vs Linux gettid:
    http://stackoverflow.com/questions/6372102/what-is-the-difference-between-pthread-self-and-gettid-which-one-should-i-u
*/

#include "common.h"

int global = 0;

pthread_mutex_t main_thread_mutex = PTHREAD_MUTEX_INITIALIZER;

void* main_thread(void *arg) {
    int argument;

    /* This is how arguments can be used*/
    argument = *((int*)arg);

    pthread_mutex_lock(&main_thread_mutex);
    global++;
    printf("tid = %d\n", argument);
    /* All threads of a process have the same PID. */
    printf("  getpid() = %ju\n", (uintmax_t)getpid());
    printf("  pthread_self() = %ju\n", (uintmax_t)pthread_self());
    pthread_mutex_unlock(&main_thread_mutex);

    return NULL;
}

int main() {
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

    /* All threads see the same memory. */
    assert(global == NUM_THREADS);

    return EXIT_SUCCESS;
}
