/*
Increment a vector, one value per work item.

It is useless to do this on a GPU, not enough work per IO,
it is just a clEnqueueNDRangeKernel + get_global_id hello world.

- http://stackoverflow.com/questions/15194798/vector-step-addition-slower-on-cuda
- http://stackoverflow.com/questions/22005405/how-to-add-up-the-elements-of-an-array-in-gpu-any-function-similar-to-cublasdas
- http://stackoverflow.com/questions/15161575/reduction-for-sum-of-vector-when-size-is-not-power-of-2
*/

#include "common.h"

int main(int argc, char **argv) {
    const char *source =
        "__kernel void main(__global int *io) {\n"
        "    io[get_global_id(0)]++;\n"
        "}\n";
    cl_int *io, *expected_output;
    cl_mem buffer;
    Common common;
    size_t i, n, io_sizeof;

	if (argc > 1) {
		n = strtoul(argv[1], NULL, 10);
	} else {
		n = 2;
	}

	/* Initialize data. */
	io_sizeof = n * sizeof(*io);
	io = malloc(io_sizeof);
	expected_output = malloc(n * sizeof(*expected_output));
	for (i = 0; i < n; ++i) {
		io[i] = i;
		expected_output[i] = i + 1;
	}

	/* Run kernel. */
    common_init(&common, source);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, io_sizeof, io, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &n, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, io_sizeof, io, 0, NULL, NULL);

	/* Assertions. */
	common_vec_assert_eq_i(io, expected_output, n);

	/* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
	free(io);
	free(expected_output);
    return EXIT_SUCCESS;
}
