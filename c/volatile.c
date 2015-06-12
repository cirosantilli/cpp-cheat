/*
# volatile

    Compiler will not store this value in cpu registers or cache as speed optimization
    instead of in RAM.

    Applications:

    -   allow access to memory mapped devices

    -   allow uses of variables between setjmp and longjmp

    -   allow uses of sig_atomic_t variables in signal handlers.

    -   multithreading, where variable may to change value at any time on another thread.

        For example on global scope:

            int other_task_finished;

        And on some function which must wait for another thread to finish a task:

            other_task_finished = 0;
            while(other_task_finished == 0){
                yield();
            }

        If the value were stored in register, other threads in other processes may never see an update.

        Concurrent operations on volatile variables are not guaranteed to be atomic.

        Unfortunatelly, this cannot be demonstrated as of ANSI C99 since there is no multithread support.
*/

#include "common.h"

int main() {
    /* TODO: do something interesting with it. */
    volatile int vi;
    return EXIT_SUCCESS;
}
