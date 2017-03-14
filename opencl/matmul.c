/*
Matrix multiplication.

Based on the amazing:
https://github.com/HandsOnOpenCL/Exercises-Solutions/tree/a908ac3f0fadede29f2735eb1264b0db7f4311a0/Solutions/Exercise08

The most basic / useful application where OpenCL might be faster than CPU.

TODO: make a SERIOUS matrix implementation. Also compare with existing SERIOUS CPU and GPU implementations:

- http://stackoverflow.com/questions/1907557/optimized-matrix-multiplication-in-c
- http://stackoverflow.com/questions/12289235/simple-and-fast-matrix-vector-multiplication-in-c-c
- https://www.quora.com/What-is-the-best-way-to-multiply-two-matrices-in-C++
- http://www.netlib.org/utk/papers/autoblock/node2.html
- http://stackoverflow.com/questions/25900312/optimizing-batched-matrix-multiplication-opencl-code
*/

#include "common.h"

typedef cl_float F;

/* C = A*B, width n, naive. */
void mat_mul_cpu(const F *A, const F *B, F *C, size_t n) {
	F tmp;
	size_t i, j, k;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			tmp = 0;
			for (k = 0; k < n; ++k) {
				tmp += A[i*n+k] * B[k*n+j];
			}
			C[i*n+j] = tmp;
		}
	}
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

int main(void) {
	srand(time(NULL));

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
		size_t n = sqrt(sizeof(A)/sizeof(A[0]));
		F C[n*n];
		const F C_expect[] = {
			19.0, 22.0,
			43.0, 50.0
		};

		mat_zero(C, n);
		mat_mul_cpu(A, B, C, n);
		assert(mat_eq(C, C_expect, n));

		mat_zero(C, n);
		mat_mul_cl(A, B, C, n);
		assert(mat_eq(C, C_expect, n));
	}

	/* Benchmarks. */
	{
		F *A = NULL, *B = NULL, *C = NULL, *C_ref = NULL;
		double dt, time;
		size_t n = 1, n2, a_sizeof;

		puts("#matmul");
		puts("n mat_mul_cpu mat_mul_cl mat_mul_cl_row");
		while(1) {
			printf("%zu ", n);
			n2 = n * n;
			a_sizeof = n2 * sizeof(F);
			A = realloc(A, a_sizeof);
			B = realloc(B, a_sizeof);
			C_ref = realloc(C_ref, a_sizeof);
			C = realloc(C, a_sizeof);
			if (A == NULL || B == NULL || C == NULL) {
				printf("Could not allocate memory for n = %zu", n);
				break;
			}
			mat_rand(A, n);
			mat_rand(B, n);

			time = common_get_nanos();
			mat_mul_cpu(A, B, C_ref, n);
			dt = common_get_nanos() - time;
			printf("%f ", dt);

			/*time = common_get_nanos();*/
			/*mat_mul_cl(A, B, C, n);*/
			/*printf("%f ", common_get_nanos() - time);*/

			time = common_get_nanos();
			mat_mul_cl_row(A, B, C, n);
			printf("%f", common_get_nanos() - time);

			assert(mat_eq(C, C_ref, n));
			puts("");
			if (dt > 1.0)
				break;
			n *= 2;
		}
		free(A);
		free(B);
		free(C);
	}

    return EXIT_SUCCESS;
}
