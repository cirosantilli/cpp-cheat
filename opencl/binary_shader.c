/*
Let's play with clCreateProgramWithBinary.

Compile the "inc.cl" CL C shader to binary, save the binary to a file, and load the shader from the binary:

    ./prog

Ignore the CL C shader, load binary from a file, and run it:

    ./prog 0

Use another shader instead:

    ./prog 1 dec.cl

The name "binary" is a possible lie: NVIDIA Linux driver 375.39
just dumps PTX human readable assembly, which we can modify without
reverse engineering. Hurray!
*/

#include "common.h"

int main(int argc, char **argv) {
    Common common;
    char *source_path;
    cl_int input[] = {1, 2};
    cl_mem buffer;
    const size_t global_work_size = sizeof(input) / sizeof(input[0]);
    int use_cache;

    if (argc > 1) {
        use_cache = !strcmp(argv[1], "0");
    } else {
        use_cache = 0;
    }
    if (argc > 2) {
        source_path = argv[2];
    } else {
        source_path = "inc.cl";
    }

    /* Create binary or kernel from binary. */
    common_create_kernel_or_use_cache(&common, use_cache, source_path, __FILE__ ".bin.tmp");

    /* Run the kernel created from the binary. */
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(input), input, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(input), input, 0, NULL, NULL);

	/* Assertions. */
    assert(input[0] == 2);
    assert(input[1] == 3);

	/* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
