/* Exit immediately in success:
 *
 *     ./pthread_deadlock.out
 *
 * Hand forever in a deadlock:
 *
 *     ./pthread_deadlock.out 0
 */

#include "common.h"

int main(int argc, char **argv) {
    pthread_mutex_t main_thread_mutex = PTHREAD_MUTEX_INITIALIZER;
    COMMON_UNUSED(argv);
    pthread_mutex_lock(&main_thread_mutex);
    if (argc > 1)
        pthread_mutex_lock(&main_thread_mutex);
    return EXIT_SUCCESS;
}
