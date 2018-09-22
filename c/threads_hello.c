#  ifndef __STDC_NO_THREADS__
#include <stdio.h>
#include <stdatomic.h>
#include <threads.h>

atomic_int acnt;
int cnt;

int f(void* thr_data) {
    for(int n = 0; n < 1000; ++n) {
        ++cnt;
        ++acnt;
        // for this example, relaxed memory order is sufficient, e.g.
        // atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed);
    }
    return 0;
}
#endif

int main(void) {
#  ifndef __STDC_NO_THREADS__
    thrd_t thr[10];
    for(int n = 0; n < 10; ++n)
        thrd_create(&thr[n], f, NULL);
    for(int n = 0; n < 10; ++n)
        thrd_join(thr[n], NULL);
    printf("The atomic counter is %u\n", acnt);
    printf("The non-atomic counter is %u\n", cnt);
#endif
}
