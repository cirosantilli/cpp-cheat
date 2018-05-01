/*
- https://unix.stackexchange.com/questions/73/how-can-i-set-the-processor-affinity-of-a-process-on-linux/441098#441098
- https://stackoverflow.com/questions/10490756/how-to-use-sched-getaffinity2-and-sched-setaffinity2-please-give-code-samp
- https://stackoverflow.com/questions/766395/how-does-sched-setaffinity-work
- https://stackoverflow.com/questions/8336191/how-to-prevent-inheriting-cpu-affinity-by-child-forked-process

Also try to this program with something like:

    taskset -c 1-3 ./sched.out

# sched.h

    More scheduling policies are defined.

    Those constants have the same meaning as in the kernel code versions.
*/

#include "common.h"

void print_affinity() {
    cpu_set_t mask;
    long nproc, i;

    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        assert(false);
    } else {
        nproc = sysconf(_SC_NPROCESSORS_ONLN);
        printf("sched_getaffinity = ");
        for (i = 0; i < nproc; i++) {
            printf("%d ", CPU_ISSET(i, &mask));
        }
        printf("\n");
    }
}

int main(void) {
    printf("SCHED_BATCH = %d\n", SCHED_BATCH);
    printf("SCHED_IDLE  = %d\n", SCHED_IDLE );
    /* Called SCHED_NORMAL in the kernel: */
    printf("SCHED_OTHER = %d\n", SCHED_OTHER);

    /*
    # sched_getaffinity

        View in which cpu's the given process can run.

        Linux keeps track of this, and this can be set with appropriate premissions.

        0 means getpid().
    */
    {
        cpu_set_t mask;

        print_affinity();
        printf("sched_getcpu = %d\n", sched_getcpu());
        CPU_ZERO(&mask);
        CPU_SET(0, &mask);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
            perror("sched_setaffinity");
            assert(false);
        }
        print_affinity();
        /* TODO is it guaranteed to have taken effect already? Always worked on my tests. */
        printf("sched_getcpu = %d\n", sched_getcpu());
    }

    return EXIT_SUCCESS;
}
