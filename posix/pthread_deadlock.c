/*
If a CLI argument is passed, block forever.
*/

#include "common.h"

int main(int argc, char **argv) {
    pthread_mutex_t main_thread_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&main_thread_mutex);
    if (argc > 1)
        pthread_mutex_lock(&main_thread_mutex);
    return EXIT_SUCCESS;
}
