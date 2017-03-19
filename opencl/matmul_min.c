#include "common.h"

#include <cblas.h>

typedef cl_float F;
typedef void (*MatMul)(const F *A, const F *B, F *C, size_t n);

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

size_t zmin(size_t x, size_t y) {
	return (x < y) ? x : y;
}

/* The golden single thread CPU standard. */
void mat_mul_cpu_cblas(const F *A, const F *B, F *C, size_t n) {
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
        1.0,
        C,
        n
    );
}

/* Cache rows in private memory. Drastic speedups expected over naive CPU. */
void mat_mul_cl_row_priv(const F *A, const F *B, F *C, size_t n) {
	char options[256];
    cl_mem buf_a, buf_b, buf_c;
    Common common;
    cl_uint ncl;
    size_t global_work_size, mat_sizeof, n2;

    /* Setup variables. */
    global_work_size = n;
    n2 = n * n;
    mat_sizeof = n2 * sizeof(F);
    ncl = n;

    /* Run kernel. */
	snprintf(options, sizeof(options), "-DPRIV_ROW_SIZE=%ju", n);
    common_init_file_options(&common, "matmul_row_priv.cl", options);
    buf_a = clCreateBuffer(common.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mat_sizeof, (F*)A, NULL);
    buf_b = clCreateBuffer(common.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mat_sizeof, (F*)B, NULL);
    buf_c = clCreateBuffer(common.context, CL_MEM_WRITE_ONLY, mat_sizeof, C, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buf_a), &buf_a);
    clSetKernelArg(common.kernel, 1, sizeof(buf_b), &buf_b);
    clSetKernelArg(common.kernel, 2, sizeof(buf_c), &buf_c);
    clSetKernelArg(common.kernel, 3, sizeof(ncl), &ncl);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);

    /* Cleanup. */
    clReleaseMemObject(buf_a);
    clReleaseMemObject(buf_b);
    clReleaseMemObject(buf_c);
    common_deinit(&common);
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
void mat_mul_cl_row_priv_priv_col_local(const F *A, const F *B, F *C, size_t n) {
	char options[256];
    cl_mem buf_a, buf_b, buf_c;
    Common common;
    cl_uint ncl;
    size_t global_work_size, local_work_size, mat_sizeof, n2;

    /* Setup variables. */
    global_work_size = n;
    local_work_size = 0;
    n2 = n * n;
    mat_sizeof = n2 * sizeof(F);
    ncl = n;

    /* Run kernel. */
	snprintf(options, sizeof(options), "-DPRIV_ROW_SIZE=%ju", n);
    common_init_file_options(&common, "matmul_row_priv_col_local.cl", options);
    clGetDeviceInfo(common.device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(local_work_size), &local_work_size, NULL);
    local_work_size = zmin(local_work_size, n);
    buf_a = clCreateBuffer(common.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mat_sizeof, (F*)A, NULL);
    buf_b = clCreateBuffer(common.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mat_sizeof, (F*)B, NULL);
    buf_c = clCreateBuffer(common.context, CL_MEM_WRITE_ONLY, mat_sizeof, C, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buf_a), &buf_a);
    clSetKernelArg(common.kernel, 1, sizeof(buf_b), &buf_b);
    clSetKernelArg(common.kernel, 2, sizeof(buf_c), &buf_c);
	clSetKernelArg(common.kernel, 3, n * sizeof(F), NULL);
    clSetKernelArg(common.kernel, 4, sizeof(ncl), &ncl);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);

    /* Cleanup. */
    clReleaseMemObject(buf_a);
    clReleaseMemObject(buf_b);
    clReleaseMemObject(buf_c);
    common_deinit(&common);
}

double bench(MatMul f, const F *A, const F *B, F *C, F *C_ref, size_t n) {
	double dt, time;
	mat_zero(C, n);
	time = common_get_nanos();
	f(A, B, C, n);
	dt = common_get_nanos() - time;
	if (C_ref != NULL)
		assert(mat_eq(C, C_ref, n));
	printf("%.3e ", dt);
	return dt;
}

int main(void) {
    srand(time(NULL));
    int done = 0;
    double dt;
	MatMul mat_mul_funcs[] = {
        mat_mul_cpu_cblas,
        mat_mul_cl_row_priv,
        mat_mul_cl_row_priv_priv_col_local,
	};
	size_t f, n = 4, a_sizeof;
    F *A = NULL, *B = NULL, *C = NULL, *C_ref = NULL;

    a_sizeof = n * n * sizeof(F);
    while(1) {
        A = realloc(A, a_sizeof);
        B = realloc(B, a_sizeof);
        C_ref = realloc(C_ref, a_sizeof);
        C = realloc(C, a_sizeof);
        printf("%zu ", (size_t)log2(n));
        if (A == NULL || B == NULL || C == NULL) {
            printf("Could not allocate memory for n = %zu. Aborting.", n);
            break;
        }
        mat_rand(A, n);
        mat_rand(B, n);
        for (f = 0; f < sizeof(mat_mul_funcs)/sizeof(mat_mul_funcs[0]); ++f) {
            if (f == 0)
                dt = bench(mat_mul_cpu, A, B, C_ref, NULL, n);
            else
                dt = bench(mat_mul_funcs[f], A, B, C, C_ref, n);
            if (dt > 1.0)
                done = 1;
        }
        puts("");
        if (done)
            break;
        n *= 2;
        a_sizeof = n * n * sizeof(F);
    }
    free(A);
    free(B);
    free(C);

    return EXIT_SUCCESS;
}
