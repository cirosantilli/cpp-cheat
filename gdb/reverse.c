#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int f() {
    int i;
    i = 0;
    i = 1;
    i = 2;
    return i;
}

int where_return(int i) {
    if (i)
        return 0;
    else
        return 1;
}

void signal_handler(int sig) {
}

int main(void) {
    int i, *ip;
    FILE *fp;

    /* Variable changes. */
    i = 0;
    i = 1;
    i = 2;

    /* Local call. */
    f();

    /* Where it returns. */
    /* https://stackoverflow.com/questions/3649468/setting-breakpoint-in-gdb-where-the-function-returns */
    where_return(0);
    where_return(1);

    /* printf. Meh. How dare they ship this crap.
     * Use rr instead for now.
     * - https://stackoverflow.com/questions/40125154/target-record-full-in-gdb-makes-n-command-fail-on-printf-with-process-recor/46113357#46113357
     * - https://stackoverflow.com/questions/2528918/gdb-reverse-debugging-fails-with-process-record-does-not-support-instruction-0x/46113472#46113472
     * - https://stackoverflow.com/questions/42451492/disable-avx-optimized-functions-in-glibc-ld-hwcap-mask-etc-ld-so-nohwcap-for/44468494#44468494
     * - https://stackoverflow.com/questions/43750603/gdb-reverse-debugging-avx2
     * */
    printf("i = %d\n", i);

    /* Is randomness completely removed?
     * Recently fixed: https://github.com/mozilla/rr/issues/2088 */
    i = time(NULL);
    printf("time(NULL) = %d\n", i);

    /* Pointer address determinism.
     * echo 0 | sudo tee /proc/sys/kernel/randomize_va_space */
    ip = malloc(sizeof(*ip));
    printf("&i = %p\n", (void *)&i);
    printf("ip = %p\n", (void *)ip);
    printf("f = %p\n", (void *)(intptr_t)f);

    /* Remove the file across replays to see if such side effects are re-done.
     * Answer: no. So rr treats stdout and stderr magically, and side effects
     * are not re-done in general. */
    fp = fopen(__FILE__ ".tmp", "w");
    fputs("a", fp);
    fclose(fp);

    /* Check that we can reverse step this, found a problem in a closed setup,
     * but can't reproduce. */
    signal(SIGINT, signal_handler);

    return EXIT_SUCCESS;
}
