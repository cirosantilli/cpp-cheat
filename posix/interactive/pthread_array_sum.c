/* POSIX version of: https://github.com/cirosantilli/algorithm-cheat/blob/c8489f41c059971008337500013cd9cdf8e86a76/src/cpp/interactive/sum_array_parallel.cpp */

#define _XOPEN_SOURCE 700
#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef uint64_t DataType;

/* Single threaded array sum. */
DataType sum_array(
    DataType *begin,
    DataType *end
) {
    DataType sum = 0;
    while (begin != end) {
        sum += *begin;
        begin++;
    }
    return sum;
}

typedef struct {
   DataType *begin;
   DataType *end;
   DataType output;
} SumArrayThreadData;

/* Thread interface. */
void* sum_array_thread(void *arg) {
    SumArrayThreadData *thread_data = (SumArrayThreadData*)arg;
    DataType *begin = thread_data->begin;
    DataType *end = thread_data->end;
    thread_data->output = sum_array(begin, end);
    return NULL;
}

/* Parallel array sum. */
DataType sum_array_parallel(
    DataType *begin,
    DataType *end,
    long nthreads
) {
    size_t array_size = end - begin;
    if (array_size < (size_t)nthreads) {
        nthreads = array_size;
    }
    size_t delta = array_size / nthreads;
    pthread_t *threads = malloc(nthreads * sizeof(pthread_t));
    SumArrayThreadData *thread_datas = malloc(nthreads * sizeof(SumArrayThreadData));
    for (long i = 0; i < nthreads; ++i) {
        thread_datas[i].begin = begin;
        thread_datas[i].end = begin + delta;
        assert(!pthread_create(
            &threads[i],
            NULL,
            sum_array_thread,
            (void*)&thread_datas[i]
        ));
        begin += delta;
    }
    DataType sum = 0;
    for (long i = 0; i < nthreads; ++i) {
        assert(!pthread_join(threads[i], NULL));
        sum += thread_datas[i].output;
    }
    free(threads);
    free(thread_datas);
    return sum + sum_array(begin, end);
}

void print_result(
    unsigned int nthreads,
    struct timespec *tstart,
    struct timespec *tend
) {
    printf(
        "%d %.4f\n",
        nthreads,
        (
            ((double)tend->tv_sec + 1.0e-9 * tend->tv_nsec) -
            ((double)tstart->tv_sec + 1.0e-9 * tstart->tv_nsec)
        )
    );
}

int main(int argc, char **argv) {
    unsigned long long array_size;
    struct timespec tstart, tend;

    /* Handle CLI arguments. */
    if (argc > 1) {
        array_size = strtoll(argv[1], NULL, 10);
    } else {
        array_size = 10;
    }

    /* Initialize array with random numbers. */
    DataType *array = malloc(sizeof(DataType) * array_size);
    assert(array);
    srand(time(NULL));
    for (size_t i = 0; i < array_size; ++i) {
        array[i] = rand();
    }

    /* Output header. */
    printf("nthreads elapsed_time_seconds\n");

    /* Single threaded sanity check. */
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    DataType serial_result = sum_array(array, array + array_size);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    print_result(0, &tstart, &tend);

    /* Use different number of threads. */
    long max_nthreads = sysconf(_SC_NPROCESSORS_ONLN) * 2;
    for (long nthreads = 1; nthreads <= max_nthreads; ++nthreads) {
        clock_gettime(CLOCK_MONOTONIC, &tstart);
        DataType result = sum_array_parallel(array, array + array_size, nthreads);
        clock_gettime(CLOCK_MONOTONIC, &tend);
        print_result(nthreads, &tstart, &tend);
        /* Sanity check that our implementation is correct. */
        assert(result == serial_result);
    }

    /* Cleanup. */
    free(array);
    return EXIT_SUCCESS;
}
