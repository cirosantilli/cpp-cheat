/*
Matrix multiplication.

Based on the amazing:
https://github.com/HandsOnOpenCL/Exercises-Solutions/tree/a908ac3f0fadede29f2735eb1264b0db7f4311a0/Solutions/Exercise08

The most basic / useful application where OpenCL might be faster than CPU.

TODO: make a SERIOUS matrix implementation. Also compare with existing SERIOUS CPU and GPU implementations:

- http://stackoverflow.com/questions/1907557/optimized-matrix-multiplication-in-c
- http://stackoverflow.com/questions/12289235/simple-and-fast-matrix-vector-multiplication-in-c-c
- https://www.quora.com/What-is-the-best-way-to-multiply-two-matrices-in-C++
- http://stackoverflow.com/questions/25900312/optimizing-batched-matrix-multiplication-opencl-code

Serious CPU implementation means it considers:

- caching
- SIMD

Articles:

- http://www.netlib.org/utk/papers/autoblock/node2.html
- http://codereview.stackexchange.com/questions/101144/simd-matrix-multiplication
*/

#include "common.h"

#include <cblas.h>
#include <clBLAS.h>

#define NELEMS(a) sizeof(a)/sizeof(a[0])
#define UNUSED(x) (void)(x)

/* TODO how to auto tune this?
 * GCC 6 was not smart enough to use widest type automatically:
 * anything larger than the widest type just dropped perf drastically. */
#define VECTOR_NELEMS 4
#define VECTOR_SIZEOF (VECTOR_NELEMS * sizeof(F))

typedef cl_float F;
typedef F Vec __attribute__ ((vector_size(VECTOR_SIZEOF)));
/* Stuff reused across OpenCL calls.
 * It would not be fair to consider their alocation time for each call,
 * as the functions will be called millions of times.
 *
 * TODO: also factor out the kernel compile time.
 * Currently recompiled every time.
 * Implementations already cache compiled kernels, but we would need
 * to call each function multiple times.
 * */
typedef struct {
    Common common;
    /* We only factor out the allocation of those buffers.
     * Data transfer time with clEnqueueWriteBuffer must still be considered. */
    cl_mem buf_a, buf_b, buf_c;
} Cache;
typedef void (*MatMul)(const F *A, const F *B, F *C, size_t n, Cache *cache);

void cl_buf_init(Cache *cache, size_t mat_sizeof) {
    cache->buf_a = clCreateBuffer(cache->common.context, CL_MEM_READ_ONLY, mat_sizeof, NULL, NULL);
    cache->buf_b = clCreateBuffer(cache->common.context, CL_MEM_READ_ONLY, mat_sizeof, NULL, NULL);
    cache->buf_c = clCreateBuffer(cache->common.context, CL_MEM_WRITE_ONLY, mat_sizeof, NULL, NULL);
}

void cl_buf_deinit(Cache *cache) {
    clReleaseMemObject(cache->buf_a);
    clReleaseMemObject(cache->buf_b);
    clReleaseMemObject(cache->buf_c);
}

/* No, this was not created for debugging, my code is flawless from the first try. */
void mat_print(const F *A, size_t n) {
    size_t i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%f ", A[i*n+j]);
        }
        puts("");
    }
}

/* Zero a matrix. */
void mat_zero(F *A, size_t n) {
    size_t i, n2;
    n2 = n*n;
    for (i = 0; i < n2; ++i) {
        A[i] = 0.0;
    }
}

/* Initialize a random matrix. */
void mat_rand(F *A, size_t n) {
    size_t i, n2;
    n2 = n*n;
    for (i = 0; i < n2; ++i) {
        A[i] = ((float)rand()) / ((float)RAND_MAX);
    }
}

/* Initialize a random matrix. */
void mat_trans(F *A, size_t n) {
    size_t i, j, i1, i2;
    F tmp;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < i; ++j) {
            i1 = i*n+j;
            i2 = j*n+i;
            tmp = A[i1];
            A[i1] = A[i2];
            A[i2] = tmp;
        }
    }
}

/* Check if two matrices are equal with given mean squared err_maxor. */
int mat_eq(const F *A, const F *B, size_t n) {
    const F err_max = 10e-3;
    F err, diff, a, b;
    size_t i, i_max;

    err = 0.0;
    i_max = n*n;
    for (i = 0; i < i_max; ++i) {
        a = A[i];
        b = B[i];
        diff = a - b;
        err += diff * diff;
    }
    return (sqrt(err) / i_max) < err_max;
}

void mat_assert_eq(const F *A, const F *B, size_t n) {
    if (!mat_eq(A, B, n)) {
        puts("");
        mat_print(A, n);
        puts("");
        mat_print(B, n);
        assert(0);
    }
}

size_t zmin(size_t x, size_t y) {
    return (x < y) ? x : y;
}

/* C = A*B, width n, naive. */
void mat_mul_cpu(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    F tmp;
    size_t i, j, k;
    UNUSED(cache);

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            tmp = 0.0;
            for (k = 0; k < n; ++k) {
                tmp += A[i*n+k] * B[k*n+j];
            }
            C[i*n+j] = tmp;
        }
    }
}

/* Transpose matrix B to increase cache hits. */
void mat_mul_cpu_trans(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    F tmp;
    size_t i, j, k;
    UNUSED(cache);

    mat_trans((F*)B, n);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            tmp = 0.0;
            for (k = 0; k < n; ++k) {
                tmp += A[i*n+k] * B[j*n+k];
            }
            C[i*n+j] = tmp;
        }
    }
    mat_trans((F*)B, n);
}

/* Zero vector. */
void vec_zero(Vec *vec, size_t vec_n) {
    size_t i;
    for (i = 0; i < vec_n; ++i) {
        (*vec)[i] = 0.0;
    }
}

/* Load vector from array. */
void vec_load(Vec *vec, size_t vec_n, const F* A, size_t A_base) {
    size_t i;
    for (i = 0; i < vec_n; ++i) {
        (*vec)[i] = A[A_base + i];
    }
}

/* Sum elements of the vector. */
F vec_sum(Vec vec, size_t vec_n) {
    size_t i;
    F sum;
    sum = 0.0;
    for (i = 0; i < vec_n; ++i) {
        sum += vec[i];
    }
    return sum;
}

/* Transpose matrix B to both:
 *
 * - increase cache hits
 * - simd GCC vector extensions which is made possible.
 *   by the transposition, to increase likelyhood of SIMDs.
 *
 * Note that GCC 6 O=3 is smart enough to use SIMD
 * even for the naive CPU method. However this was still way faster.
 * */
void mat_mul_cpu_trans_vec(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    F tmpf;
    size_t i, j, k, k_max, ai, bi;
    Vec tmp, a, b;
    UNUSED(cache);

    mat_trans((F*)B, n);
    k_max = (n / VECTOR_NELEMS) * VECTOR_NELEMS;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            vec_zero(&tmp, VECTOR_NELEMS);
            for (k = 0; k < k_max; k += VECTOR_NELEMS) {
                ai = i * n + k;
                bi = j * n + k;
                vec_load(&a, VECTOR_NELEMS, A, ai);
                vec_load(&b, VECTOR_NELEMS, B, bi);
                tmp += a * b;
            }
            tmpf = 0.0;
            for (; k < n; ++k) {
                tmpf += A[i*n+k] * B[j*n+k];
            }
            C[i*n+j] = vec_sum(tmp, VECTOR_NELEMS) + tmpf;
        }
    }
    mat_trans((F*)B, n);
}

/* Blocked matrix multiplication.
 * TODO slower than transpose, sometimes similar timing to naive.
 * Why do they say that this is better?
 * */
void mat_mul_cpu_block(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    size_t ib, jb, kb, i, j, k, i_max, j_max, k_max, nb ;
    F tmp;
    UNUSED(cache);

    nb = lround(sqrt(n));
    for (ib = 0; ib < n; ib += nb) {
        i_max = zmin(ib + nb, n);
        for (jb = 0; jb < n; jb += nb) {
            k_max = zmin(jb + nb, n);
            for (kb = 0; kb < n; kb += nb) {
                j_max = zmin(kb + nb, n);

                /* TODO would be cool to recurse here, but would require more offset parameters,
                 * likely similar to tose of CBLAS. */
                for (i = ib; i < i_max; ++i) {
                    for (j = kb; j < j_max; ++j) {
                        tmp = 0.0;
                        for (k = jb; k < k_max; ++k) {
                            tmp += A[i*n+k] * B[k*n+j];
                        }
                        C[i*n+j] += tmp;
                    }
                }
            }
        }
    }
}

/* The golden single thread CPU standard. */
void mat_mul_cpu_cblas(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    UNUSED(cache);
    cblas_sgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        n,
        n,
        n,
        1.0,
        A,
        n,
        B,
        n,
        0.0,
        C,
        n
    );
}

/* Simplest possible CL implementation. No speedup. */
void mat_mul_cl(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    cl_uint ncl;
    size_t global_work_size[2], mat_sizeof;

    /* Setup variables. */
    global_work_size[0] = n;
    global_work_size[1] = n;
    mat_sizeof = n * n * sizeof(F);
    ncl = n;

    /* Run kernel. */
    common_create_kernel_file(&cache->common, "matmul.cl", NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_a, CL_TRUE, 0, mat_sizeof, (F*)A, 0, NULL, NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_b, CL_TRUE, 0, mat_sizeof, (F*)B, 0, NULL, NULL);
    clSetKernelArg(cache->common.kernel, 0, sizeof(cache->buf_a), &cache->buf_a);
    clSetKernelArg(cache->common.kernel, 1, sizeof(cache->buf_b), &cache->buf_b);
    clSetKernelArg(cache->common.kernel, 2, sizeof(cache->buf_c), &cache->buf_c);
    clSetKernelArg(cache->common.kernel, 3, sizeof(ncl), &ncl);
    clEnqueueNDRangeKernel(cache->common.command_queue, cache->common.kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
    clFlush(cache->common.command_queue);
    clFinish(cache->common.command_queue);
    clEnqueueReadBuffer(cache->common.command_queue, cache->buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);
}

/* Cache rows in private memory. Drastic speedups expected over naive CPU. */
void mat_mul_cl_row_priv(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    char options[256];
    cl_uint ncl;
    size_t global_work_size, mat_sizeof;

    /* Setup variables. */
    global_work_size = n;
    mat_sizeof = n * n * sizeof(F);
    ncl = n;

    /* Run kernel. */
    snprintf(options, sizeof(options), "-DPRIV_ROW_SIZE=%ju", n);
    common_create_kernel_file(&cache->common, "matmul_row_priv.cl", options);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_a, CL_TRUE, 0, mat_sizeof, (F*)A, 0, NULL, NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_b, CL_TRUE, 0, mat_sizeof, (F*)B, 0, NULL, NULL);
    clSetKernelArg(cache->common.kernel, 0, sizeof(cache->buf_a), &cache->buf_a);
    clSetKernelArg(cache->common.kernel, 1, sizeof(cache->buf_b), &cache->buf_b);
    clSetKernelArg(cache->common.kernel, 2, sizeof(cache->buf_c), &cache->buf_c);
    clSetKernelArg(cache->common.kernel, 3, sizeof(ncl), &ncl);
    clEnqueueNDRangeKernel(cache->common.command_queue, cache->common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(cache->common.command_queue);
    clFinish(cache->common.command_queue);
    clEnqueueReadBuffer(cache->common.command_queue, cache->buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);
}

/* Let's see if this is any different from local memory.
 * Outcome: much slower than private memory, slower than naive method. */
void mat_mul_cl_row_local(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    cl_uint ncl;
    size_t global_work_size, local_work_size, mat_sizeof;

    /* Setup variables. */
    /* Cannot be larger than 1 on this example, otherwise memory conflicts
     * will happen between work items. */
    local_work_size = 1;
    global_work_size = n;
    mat_sizeof = n * n * sizeof(F);
    ncl = n;

    /* Run kernel. */
    common_create_kernel_file(&cache->common, "matmul_row_local.cl", NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_a, CL_TRUE, 0, mat_sizeof, (F*)A, 0, NULL, NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_b, CL_TRUE, 0, mat_sizeof, (F*)B, 0, NULL, NULL);
    clSetKernelArg(cache->common.kernel, 0, sizeof(cache->buf_a), &cache->buf_a);
    clSetKernelArg(cache->common.kernel, 1, sizeof(cache->buf_b), &cache->buf_b);
    clSetKernelArg(cache->common.kernel, 2, sizeof(cache->buf_c), &cache->buf_c);
    clSetKernelArg(cache->common.kernel, 3, n * sizeof(F), NULL);
    clSetKernelArg(cache->common.kernel, 4, sizeof(ncl), &ncl);
    clEnqueueNDRangeKernel(cache->common.command_queue, cache->common.kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);
    clFlush(cache->common.command_queue);
    clFinish(cache->common.command_queue);
    clEnqueueReadBuffer(cache->common.command_queue, cache->buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);
}

/* Like row private, but to reduce global memory accesses,
 * we copy only once per work group to local memory.
 *
 * Each work group contains a few rows of A.
 *
 * We load the first column, multiply all rows by that column, synrhconize,
 * load another column, and so on.
 *
 * This leads to a thread blockage / memory access tradeoff.
 *
 * We make work groups as large as possible to reload memory less times. */
void mat_mul_cl_row_priv_col_local(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    char options[256];
    cl_uint ncl;
    size_t global_work_size, local_work_size, mat_sizeof;

    /* Setup variables. */
    global_work_size = n;
    mat_sizeof = n * n * sizeof(F);
    ncl = n;

    /* Run kernel. */
    snprintf(options, sizeof(options), "-DPRIV_ROW_SIZE=%ju", n);
    common_create_kernel_file(&cache->common, "matmul_row_priv_col_local.cl", options);
    local_work_size = 0;
    clGetDeviceInfo(cache->common.device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(local_work_size), &local_work_size, NULL);
    local_work_size = zmin(local_work_size, n);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_a, CL_TRUE, 0, mat_sizeof, (F*)A, 0, NULL, NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_b, CL_TRUE, 0, mat_sizeof, (F*)B, 0, NULL, NULL);
    clSetKernelArg(cache->common.kernel, 0, sizeof(cache->buf_a), &cache->buf_a);
    clSetKernelArg(cache->common.kernel, 1, sizeof(cache->buf_b), &cache->buf_b);
    clSetKernelArg(cache->common.kernel, 2, sizeof(cache->buf_c), &cache->buf_c);
    clSetKernelArg(cache->common.kernel, 3, n * sizeof(F), NULL);
    clSetKernelArg(cache->common.kernel, 4, sizeof(ncl), &ncl);
    clEnqueueNDRangeKernel(cache->common.command_queue, cache->common.kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);
    clFlush(cache->common.command_queue);
    clFinish(cache->common.command_queue);
    clEnqueueReadBuffer(cache->common.command_queue, cache->buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);
}

/* Copy as many cols from B as possibl to the local memory, only then start multiplying.
 * This leads to less memory barrier hits.
 * How many rows we copy is limited by the local memory size, ideally the entire matrix will fit. */
void mat_mul_cl_row_priv_cols_local(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    char options[256];
    cl_uint ncl, n_local_cols;
    cl_ulong local_mem_size;
    size_t col_size, global_work_size, local_work_size, mat_sizeof;

    /* Setup variables. */
    col_size = n * sizeof(F);
    global_work_size = n;
    mat_sizeof = n * n * sizeof(F);
    ncl = n;

    /* Run kernel. */
    snprintf(options, sizeof(options), "-DPRIV_ROW_SIZE=%ju", n);
    common_create_kernel_file(&cache->common, "matmul_row_priv_cols_local.cl", options);
    local_work_size = 0;
    clGetDeviceInfo(cache->common.device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(local_work_size), &local_work_size, NULL);
    local_work_size = zmin(local_work_size, n);
    local_mem_size = 0;
    clGetDeviceInfo(cache->common.device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(local_mem_size), &local_mem_size, NULL);
    /* TODO: can blow up without that - 1. Why?
     * It only reaches the max without it, not crosses, right?
     * So bug in the kernel? */
    n_local_cols = zmin(local_mem_size / col_size, n) - 1;
    /*puts("");*/
    /*printf("max memory %llu\n", (unsigned long long)local_mem_size);*/
    /*printf("n_local_cols %llu\n", (unsigned long long)n_local_cols);*/
    /*printf("memory %llu\n", (unsigned long long)n_local_cols * n * sizeof(F));*/
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_a, CL_TRUE, 0, mat_sizeof, (F*)A, 0, NULL, NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_b, CL_TRUE, 0, mat_sizeof, (F*)B, 0, NULL, NULL);
    clSetKernelArg(cache->common.kernel, 0, sizeof(cache->buf_a), &cache->buf_a);
    clSetKernelArg(cache->common.kernel, 1, sizeof(cache->buf_b), &cache->buf_b);
    clSetKernelArg(cache->common.kernel, 2, sizeof(cache->buf_c), &cache->buf_c);
    clSetKernelArg(cache->common.kernel, 3, n_local_cols * col_size, NULL);
    clSetKernelArg(cache->common.kernel, 4, sizeof(ncl), &ncl);
    clSetKernelArg(cache->common.kernel, 5, sizeof(n_local_cols), &n_local_cols);
    clEnqueueNDRangeKernel(cache->common.command_queue, cache->common.kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);
    clFlush(cache->common.command_queue);
    clFinish(cache->common.command_queue);
    clEnqueueReadBuffer(cache->common.command_queue, cache->buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);
}

void mat_mul_cl_block(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    cl_uint ncl, nblkcl;
    size_t global_work_size[2], local_work_size[2], mat_sizeof, nblk;

    /* Setup variables. */
    global_work_size[0] = n;
    global_work_size[1] = n;
    mat_sizeof = n * n * sizeof(F);
    ncl = n;

    /* Run kernel. */
    common_create_kernel_file(&cache->common, "matmul_block.cl", NULL);
    clGetDeviceInfo(cache->common.device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(nblk), &nblk, NULL);
    nblk = sqrt(zmin(nblk, n));
    nblk = zmin(nblk, 3);
    nblkcl = nblk;
    local_work_size[0] = nblk;
    local_work_size[1] = nblk;
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_a, CL_TRUE, 0, mat_sizeof, (F*)A, 0, NULL, NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_b, CL_TRUE, 0, mat_sizeof, (F*)B, 0, NULL, NULL);
    clSetKernelArg(cache->common.kernel, 0, sizeof(cache->buf_a), &cache->buf_a);
    clSetKernelArg(cache->common.kernel, 1, sizeof(cache->buf_b), &cache->buf_b);
    clSetKernelArg(cache->common.kernel, 2, sizeof(cache->buf_c), &cache->buf_c);
    clSetKernelArg(cache->common.kernel, 3, nblk * nblk * sizeof(F), NULL);
    printf("nblk = %llu\n", (unsigned long long)nblk);
    printf("local memory = %llu\n", (unsigned long long)2 * nblk * nblk * sizeof(F));
    clSetKernelArg(cache->common.kernel, 4, nblk * nblk * sizeof(F), NULL);
    clSetKernelArg(cache->common.kernel, 5, sizeof(ncl), &ncl);
    clSetKernelArg(cache->common.kernel, 6, sizeof(nblkcl), &nblkcl);
    clEnqueueNDRangeKernel(
        cache->common.command_queue, cache->common.kernel, 2, NULL,
        global_work_size, local_work_size, 0, NULL, NULL
    );
    clFlush(cache->common.command_queue);
    clFinish(cache->common.command_queue);
    clEnqueueReadBuffer(cache->common.command_queue, cache->buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);
}

void mat_mul_cl_clblas(const F *A, const F *B, F *C, size_t n, Cache *cache) {
    cl_event event;
    size_t mat_sizeof;

    mat_sizeof = n * n * sizeof(F);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_a, CL_TRUE, 0, mat_sizeof, (F*)A, 0, NULL, NULL);
    clEnqueueWriteBuffer(cache->common.command_queue, cache->buf_b, CL_TRUE, 0, mat_sizeof, (F*)B, 0, NULL, NULL);
    clblasSgemm(
        clblasRowMajor,
        clblasNoTrans,
        clblasNoTrans,

        n,
        n,
        n,
        1.0,

        cache->buf_a,
        0,
        n,

        cache->buf_b,
        0,
        n,

        0.0,
        cache->buf_c,
        0,
        n,

        1,
        &(cache->common.command_queue),
        0,
        NULL,
        &event
    );
    clWaitForEvents(1, &event);
    clEnqueueReadBuffer(cache->common.command_queue, cache->buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);
}

double bench(MatMul f, const F *A, const F *B, F *C, F *C_ref, size_t n, Cache *cache) {
    double dt, time;
    mat_zero(C, n);
    time = common_get_nanos();
    f(A, B, C, n, cache);
    dt = common_get_nanos() - time;
    if (C_ref != NULL)
        mat_assert_eq(C, C_ref, n);
    printf("%.3e ", dt);
    fflush(stdout);
    return dt;
}

int main(int argc, char **argv) {
    srand(time(NULL));
    Cache cache;
    double max_runtime;
    /* Overly slow ones commented out by default. */
    MatMul mat_mul_funcs[] = {
        /*mat_mul_cpu,*/
        mat_mul_cpu_trans,
        mat_mul_cpu_trans_vec,
        mat_mul_cpu_block,
        mat_mul_cpu_cblas,
        /*mat_mul_cl,*/
        mat_mul_cl_row_priv,
        mat_mul_cl_row_local,
        mat_mul_cl_row_priv_col_local,
        mat_mul_cl_row_priv_cols_local,
        /* TODO broken for larger matrics, some cells contain trash.
         * Likey some memory overflow problem. */
        /*mat_mul_cl_block,*/
        mat_mul_cl_clblas,
    };
    int first, func_done[NELEMS(mat_mul_funcs)] = {0};
    size_t f, i;
    size_t mat_sizeof;

    /* CLI args. */
    if (argc > 1) {
        max_runtime = strtod(argv[1], NULL);
    } else {
        max_runtime = 1.0;
    }

    common_init(&(cache.common), NULL);

    /* Unit test 2x2. */
    {
        const F A[] = {
            1.0, 2.0,
            3.0, 4.0
        };
        const F B[] = {
            5.0, 6.0,
            7.0, 8.0
        };
        enum N { n = 2 };
        F C[n*n];
        const F C_ref[] = {
            19.0, 22.0,
            43.0, 50.0
        };
        cl_buf_init(&cache, n * n * sizeof(F));
        for (f = 0; f < sizeof(mat_mul_funcs)/sizeof(mat_mul_funcs[0]); ++f) {
            mat_zero(C, n);
            mat_mul_funcs[f](A, B, C, n, &cache);
            mat_assert_eq(C, C_ref, n);
        }
        cl_buf_deinit(&cache);
    }

    /* Unit test 4x4. */
    {
        const F A[] = {
             1.0,  2.0,  3.0,  4.0,
             5.0,  6.0,  7.0,  8.0,
             9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0,
        };
        const F B[] = {
            17.0, 18.0, 19.0, 20.0,
            21.0, 22.0, 23.0, 24.0,
            25.0, 26.0, 27.0, 28.0,
            29.0, 30.0, 31.0, 32.0,
        };
        const F C_ref[] = {
             250.0,  260.0,  270.0,  280.0,
             618.0,  644.0,  670.0,  696.0,
             986.0, 1028.0, 1070.0, 1112.0,
            1354.0, 1412.0, 1470.0, 1528.0,
        };
        enum N { n = 4 };
        F C[n*n];
        cl_buf_init(&cache, n * n * sizeof(F));
        for (f = 0; f < NELEMS(mat_mul_funcs); ++f) {
            mat_zero(C, n);
            mat_mul_funcs[f](A, B, C, n, &cache);
            mat_assert_eq(C, C_ref, n);
        }
        cl_buf_deinit(&cache);
    }

    /* Benchmarks. */
    {
        double dt;
        F *A = NULL, *B = NULL, *C = NULL, *C_ref = NULL, *dst = NULL, *ref = NULL;
        int done;
        size_t n = 2;

        puts("#matmul");
        done = 0;
        while(1) {
            printf("%zu ", (size_t)log2(n));
            mat_sizeof = n * n * sizeof(F);

            /* CPU setup. */
            A = aligned_alloc(VECTOR_SIZEOF, mat_sizeof);
            B = aligned_alloc(VECTOR_SIZEOF, mat_sizeof);
            C = aligned_alloc(VECTOR_SIZEOF, mat_sizeof);
            C_ref = aligned_alloc(VECTOR_SIZEOF, mat_sizeof);
            if (NULL == A || NULL == B || NULL == C) {
                printf("error: could not allocate memory for n = %zu", n);
                break;
            }
            mat_rand(A, n);
            mat_rand(B, n);

            cl_buf_init(&cache, mat_sizeof);
            first = 1;
            for (f = 0; f < NELEMS(mat_mul_funcs); ++f) {
                if (func_done[f]) {
                    printf("%*s", 10, "");
                } else {
                    if (first) {
                        dst = C_ref;
                        ref = NULL;
                        first = 0;
                    } else {
                        dst = C;
                        ref = C_ref;
                    }
                    dt = bench(mat_mul_funcs[f], A, B, dst, ref, n, &cache);
                    if (dt > max_runtime)
                        func_done[f] = 1;
                }
            }
            puts("");
            done = 1;
            for (i = 0; i < NELEMS(mat_mul_funcs); ++i) {
                if (!func_done[i]) {
                    done = 0;
                    break;
                }
            }
            if (done)
                break;
            n *= 2;

            /* CPU deinit. */
            free(A);
            free(B);
            free(C);
            free(C_ref);

            cl_buf_deinit(&cache);
        }
        common_deinit(&cache.common);
    }

    return EXIT_SUCCESS;
}
