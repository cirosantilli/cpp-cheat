/*
Kernel takes an integer value instead of a pointer.

cl_int is passed directly to clSetKernelArg instead of using
a buffer obtained from clCreateBuffer.

Increment a vector. It is useless to do this on a GPU, not enough work / IO.
*/

#include "common.h"

int main(void) {
    const char *source =
        "__kernel void main(int in, __global int *out) {\n"
        "    out[0] = in + 1;\n"
        "}\n";
    cl_command_queue command_queue;
    cl_int input = 1;
    cl_mem buffer;
    Common common;

	/* Run kernel. */
    common_init(&common, source);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE, sizeof(cl_int), NULL, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(cl_int), &input);
    clSetKernelArg(common.kernel, 1, sizeof(cl_mem), &buffer);
    command_queue = clCreateCommandQueue(common.context, common.device, 0, NULL);
    clEnqueueTask(command_queue, common.kernel, 0, NULL, NULL);
    clFlush(command_queue);
    clFinish(command_queue);
    clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, sizeof(cl_int), &input, 0, NULL, NULL);

	/* Assertions. */
    assert(input == 2);

	/* Cleanup. */
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(command_queue);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
