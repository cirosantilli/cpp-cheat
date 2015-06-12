/*
Some functions to play with profiling.

You likely want to do assembly analysis as well when profiling things.

-   turn off optimization if you want results to make evident sense

-   even without optimization, cache access speed is hard to predict
    so what you expect may be false
*/

#include "common.h"

static const int n_prof_runs = 100000000;

/* Only the loop. */
/* Discount this from every other profile run */
void loop_only_prof(int n) {
    int i;
    for(i=0; i<n; i++);
}

void while_only_prof(int n) {
    int i = 0;
    while(i < n)
        ++i;
}

void int_assign_prof(int n) {
    int i,j;
    for(i=0; i<n; i++)
        j=1;
}

void do_nothing(){}

void func_all_prof(int n) {
    int i;
    for(i=0; i<n; i++)
        do_nothing();
}

static inline void inline_do_nothing(){}

void inline_func_call_prof(int n) {
    int i;
    for(i=0; i<n; i++)
        inline_do_nothing();
}

void int_sum_prof(int n) {
    int i, j = 0;
    for(i=0; i<n; i++)
        j = j + 0;
}

void int_sub_prof(int n) {
    int i, j = 0;
    for(i=n; i>0; i--);
        j = j - 0;
}

void int_mult_prof(int n) {
    int i, j = 1;
    for(i=0; i<n; i++)
        j = j * 1;
}

void int_div_prof(int n) {
    int i, j = 1;
    for(i=0; i<n; i++)
        j = j / 1;
}

void float_sum_prof(int n) {
    float f;
    int i;
    for(i=0; i<n; i++)
        f = f + 0.0;
}

void float_sub_prof(int n) {
    float f;
    int i;
    for(i=0; i<n; i++)
        f = f - 0.0;
}

void float_mult_prof(int n) {
    int i;
    float j;
    for(i=0; i<n; i++)
        j = j * 1.0;
}

void float_div_prof(int n) {
    int i;
    float j;
    for(i=0; i<n; i++)
        j = j / 1.0;
}

void putsProf(int n) {
    int i;
    for(i = 0; i < n; ++i)
        puts("a");
}

void stack1b_prof(int n) {
    int is[1];
    int i;
    for(i = 0; i < n; ++i) {
        int is[1];
    }
}

void stack1kb_prof(int n) {
    int is[1];
    int i;
    for(i = 0; i < n; ++i) {
        int is[0x800];
    }
}

void stack1mb_prof(int n) {
    int is[1];
    int i;
    for(i = 0; i < n; ++i) {
        int is[0xF0000];
    }
}

void heap1b_prof(int n) {
    char *cp;
    int i;
    for(i = 0; i < n; ++i) {
        cp = (char*) malloc(sizeof(char) * 1);
        free(cp);
    }
}

void heap1kb_prof(int n) {
    char *cp;
    int i;
    for(i = 0; i < n; ++i) {
        cp = (char*) malloc(sizeof(char) * 0x800);
        free(cp);
    }
}

void heap1mbProf(int n) {
    char *cp;
    int i;
    for(i = 0; i < n; ++i) {
        cp = (char*) malloc(sizeof(char) * 0xF0000);
        free(cp);
    }
}

int main() {
    loop_only_prof(n_prof_runs);
    while_only_prof(n_prof_runs);

    int_assign_prof(n_prof_runs);
    int_sum_prof(n_prof_runs);
    int_sub_prof(n_prof_runs);
    int_mult_prof(n_prof_runs);
    int_div_prof(n_prof_runs);

    float_sum_prof(n_prof_runs);
    float_sub_prof(n_prof_runs);
    float_mult_prof(n_prof_runs);
    float_div_prof(n_prof_runs);

    func_all_prof(n_prof_runs);
    inline_func_call_prof(n_prof_runs);

    stack1b_prof(n_prof_runs);
    stack1kb_prof(n_prof_runs);
    stack1mb_prof(n_prof_runs);

    heap1b_prof(n_prof_runs);
    heap1kb_prof(n_prof_runs);

    /* By far the slowest. */
    /*heap1mbProf(n_prof_runs);*/

    /*
    BAD:
    Don't do stdout on profiling.
    System time is not counted anyways.
    */
    /*putsProf(n_prof_runs);*/

    return EXIT_SUCCESS;
}
