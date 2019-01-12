#if __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_THREADS__)
#include <stdio.h>
#include <stdatomic.h>
#include <threads.h>

atomic_int acnt;
int cnt;

int f(void *thr_data) {
    (void)thr_data;
    for(int n = 0; n < 1000; ++n) {
        ++cnt;
        ++acnt;
    }
    return 0;
}
#endif

int main(void) {
#if __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_THREADS__)
    thrd_t thr[10];
    for(int n = 0; n < 10; ++n)
        thrd_create(&thr[n], f, NULL);
    for(int n = 0; n < 10; ++n)
        thrd_join(thr[n], NULL);
    printf("atomic %u\n", acnt);
    printf("non-atomic %u\n", cnt);
#endif
}
