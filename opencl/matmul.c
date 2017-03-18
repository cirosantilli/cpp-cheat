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

#define VECTOR_SIZE (4 * sizeof(F))

typedef cl_float F;
typedef F F4 __attribute__ ((vector_size(VECTOR_SIZE)));
typedef void (*MatMul)(const F *A, const F *B, F *C, size_t n);

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

/* C = A*B, width n, naive. */
void mat_mul_cpu(const F *A, const F *B, F *C, size_t n) {
    F tmp;
    size_t i, j, k;

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
void mat_mul_cpu_trans(const F *A, const F *B, F *C, size_t n) {
    F tmp;
    size_t i, j, k;

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

/* Transpose matrix B to:
 *
 * - increase cache hits,
 * - simd GCC vector extensions which is made possible.
 *   by the transposition, to increase likelyhood of SIMDs.
 *
 * Note that GCC 6 O=3 is smart enough to use SIMD
 * even for the naive CPU method. However this was more efficient.
 * */
void mat_mul_cpu_trans_vec(const F *A, const F *B, F *C, size_t n) {
    size_t i, j, k, ai, bi;
    F4 tmp, a4, b4;

    mat_trans((F*)B, n);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;
            tmp[3] = 0.0;
            for (k = 0; k < n; k += 4) {
                ai =  i*n+k;
                bi =  j*n+k;
                a4[0] = A[ai+0];
                a4[1] = A[ai+1];
                a4[2] = A[ai+2];
                a4[3] = A[ai+3];
                b4[0] = B[bi+0];
                b4[1] = B[bi+1];
                b4[2] = B[bi+2];
                b4[3] = B[bi+3];
                tmp += a4 * b4;
            }
            C[i*n+j] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
        }
    }
    mat_trans((F*)B, n);
}

size_t zmin(size_t x, size_t y) {
	return (x < y) ? x : y;
}

/* Blocked matrix multiplication.
 * TODO slower than transpose, sometimes similar timing to naive.
 * Why do they say that this is better? */
void mat_mul_cpu_block(const F *A, const F *B, F *C, size_t n) {
    size_t ib, jb, kb, i, j, k, i_max, j_max, k_max, nb ;
    F tmp;

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

/* Simplest possible CL implementation. No speedup. */
void mat_mul_cl(const F *A, const F *B, F *C, size_t n) {
    cl_mem buf_a, buf_b, buf_c;
    Common common;
    cl_uint ncl;
    size_t global_work_size[2], mat_sizeof, n2;

    /* Setup variables. */
    global_work_size[0] = n;
    global_work_size[1] = n;
    n2 = n * n;
    mat_sizeof = n2 * sizeof(F);
     ncl = n;

    /* Run kernel. */
    common_init_file(&common, "matmul.cl");
    buf_a = clCreateBuffer(common.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mat_sizeof, (F*)A, NULL);
    buf_b = clCreateBuffer(common.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mat_sizeof, (F*)B, NULL);
    buf_c = clCreateBuffer(common.context, CL_MEM_WRITE_ONLY, mat_sizeof, C, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buf_a), &buf_a);
    clSetKernelArg(common.kernel, 1, sizeof(buf_b), &buf_b);
    clSetKernelArg(common.kernel, 2, sizeof(buf_c), &buf_c);
    clSetKernelArg(common.kernel, 3, sizeof(ncl), &ncl);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buf_c, CL_TRUE, 0, mat_sizeof, C, 0, NULL, NULL);

    /* Cleanup. */
    clReleaseMemObject(buf_a);
    clReleaseMemObject(buf_b);
    clReleaseMemObject(buf_c);
    common_deinit(&common);
}

/* Cache rows in private memory. Drastic speedups expected over naive CPU. */
void mat_mul_cl_row(const F *A, const F *B, F *C, size_t n) {
    cl_mem buf_a, buf_b, buf_c;
    Common common;
    cl_uint ncl;
    size_t global_work_size[2], mat_sizeof, n2;

    /* Setup variables. */
    global_work_size[0] = n;
    global_work_size[1] = n;
    n2 = n * n;
    mat_sizeof = n2 * sizeof(F);
     ncl = n;

    /* Run kernel. */
    common_init_file(&common, "matmul_row.cl");
    buf_a = clCreateBuffer(common.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mat_sizeof, (F*)A, NULL);
    buf_b = clCreateBuffer(common.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mat_sizeof, (F*)B, NULL);
    buf_c = clCreateBuffer(common.context, CL_MEM_WRITE_ONLY, mat_sizeof, C, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buf_a), &buf_a);
    clSetKernelArg(common.kernel, 1, sizeof(buf_b), &buf_b);
    clSetKernelArg(common.kernel, 2, sizeof(buf_c), &buf_c);
    clSetKernelArg(common.kernel, 3, sizeof(ncl), &ncl);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
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
	printf("%f ", dt);
	return dt;
}

int main(int argc, char **argv) {
    srand(time(NULL));
    double max_cpu_runtime;
	MatMul mat_mul_funcs[] = {
		mat_mul_cpu_trans,
		mat_mul_cpu_trans_vec,
		mat_mul_cpu_block,
		mat_mul_cpu_cblas,
		/* Comment out, because this overflows GPU memory and blocks computer
		 * before the others get to meaningful times. */
		/*mat_mul_cl,*/
		mat_mul_cl_row,
	};

	/* CLI args. */
    if (argc > 1) {
        max_cpu_runtime = strtod(argv[1], NULL);
    } else {
        max_cpu_runtime = 1.0;
    }

    /* Unit test our implementations. */
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

        mat_zero(C, n);
        mat_mul_cpu(A, B, C, n);
        assert(mat_eq(C, C_ref, n));

        mat_zero(C, n);
        mat_mul_cpu_trans(A, B, C, n);
        assert(mat_eq(C, C_ref, n));

        mat_zero(C, n);
        mat_mul_cpu_block(A, B, C, n);
        assert(mat_eq(C, C_ref, n));

        mat_zero(C, n);
        mat_mul_cpu_cblas(A, B, C, n);
        assert(mat_eq(C, C_ref, n));

        mat_zero(C, n);
        mat_mul_cl(A, B, C, n);
        assert(mat_eq(C, C_ref, n));

        mat_zero(C, n);
        mat_mul_cl_row(A, B, C, n);
        assert(mat_eq(C, C_ref, n));
    }

    /* Unit test for vector implementation, which requires 4x4 matrices. */
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
            250.000000, 260.000000, 270.000000, 280.000000,
            618.000000, 644.000000, 670.000000, 696.000000,
            986.000000, 1028.000000, 1070.000000, 1112.000000,
            1354.000000, 1412.000000, 1470.000000, 1528.000000,
        };
        enum N { n = 4 };
        F C[n*n];

        mat_zero(C, n);
        mat_mul_cpu_trans_vec(A, B, C, n);
        assert(mat_eq(C, C_ref, n));
    }

    /* Benchmarks. */
    {
		double dt;
        F *A = NULL, *B = NULL, *C = NULL, *C_ref = NULL;
        size_t f, n = 4, a_sizeof;

        puts("#matmul");
        puts("n cpu cpu_trans cpu_trans_vec cpu_block cpu_cblas cl_row");
        a_sizeof = n * n * sizeof(F);
        A = aligned_alloc(VECTOR_SIZE, a_sizeof);
        B = aligned_alloc(VECTOR_SIZE, a_sizeof);
        C = aligned_alloc(VECTOR_SIZE, a_sizeof);
        C_ref = aligned_alloc(VECTOR_SIZE, a_sizeof);
        while(1) {
            printf("%zu ", n);
            if (A == NULL || B == NULL || C == NULL) {
                printf("Could not allocate memory for n = %zu. Aborting.", n);
                break;
            }
            mat_rand(A, n);
            mat_rand(B, n);
			dt = bench(mat_mul_cpu, A, B, C_ref, NULL, n);
			for (f = 0; f < sizeof(mat_mul_funcs)/sizeof(mat_mul_funcs[0]); ++f) {
				bench(mat_mul_funcs[f], A, B, C, C_ref, n);
			}
            puts("");
            if (dt > max_cpu_runtime)
                break;
            n *= 2;
            a_sizeof = n * n * sizeof(F);
            A = realloc(A, a_sizeof);
            B = realloc(B, a_sizeof);
            C_ref = realloc(C_ref, a_sizeof);
            C = realloc(C, a_sizeof);
        }
        free(A);
        free(B);
        free(C);
    }

    return EXIT_SUCCESS;
}
