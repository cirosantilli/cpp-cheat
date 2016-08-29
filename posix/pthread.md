# pthread

## Threads

Sources:

- https://computing.llnl.gov/tutorials/pthreads/

POSIX threads.

Complex model with around 100 functions prefixed by `pthread`.

c11 and C++11 introduced a standard threading model, so in time this may become less important

Each thread has its own stack, but unlike process, global memory is shared.

Quicker to start than a process because less resource copy is needed.

In Linux they are based on the `clone` system call.

In GCC you must compile with `-pthread`.

## Thread synchronization mechanisms

- mutexes - Mutual exclusion lock: Block access to variables by other threads. This enforces exclusive access by a thread to a variable or set of variables.

- joins - Make a thread wait till others are complete (terminated).

- condition variables - data type pthread_cond_t

Good tutorial: <http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html#SYNCHRONIZATION>

## pthread_create

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

    Can be retrieved from the thread with `pthread_self()`

    In POSIX all threads of a process have the same PID. TODO confirm with reference

-   `attr`: set thread attributes. `NULL` for defaults.

-   `start_routine`: function that runs the thread code

    If this function does `return x`, it is the same as calling `pthread_exit(x)`.

    This value can then be retrieve from `pthread_join`.

-   `arg`: argument to `start_routine`, `NULL` if none.

## pthread_join

Wait for a given thread to terminate.

If it has already terminated, does not wait.

## pthread_self

Get thread id of current running thread.

Same value that is returned through the `thread` argument of `pthread_create`.

Vs Linux gettid:
http://stackoverflow.com/questions/6372102/what-is-the-difference-between-pthread-self-and-gettid-which-one-should-i-u
