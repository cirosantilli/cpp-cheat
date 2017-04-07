/*
Kernel takes an integer value `int` instead of a pointer.

cl_int is passed directly to clSetKernelArg instead of using
a buffer obtained from clCreateBuffer.

Does not need to be __global because it is not a pointer.

In practice, this is often used to pass problem size parameters to the kernel.
*/

#include "common.h"

int main(void) {
    const char *source =
        "__kernel void kmain(int in, __global int *out) {\n"
        "    out[0] = in + 1;\n"
        "}\n";
    cl_int in = 1, out;
    cl_mem buffer;
    Common common;

    /* Run kernel. */
    common_init(&common, source);
    clSetKernelArg(common.kernel, 0, sizeof(in), &in);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE, sizeof(out), NULL, NULL);
    clSetKernelArg(common.kernel, 1, sizeof(buffer), &buffer);
    clEnqueueTask(common.command_queue, common.kernel, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(out), &out, 0, NULL, NULL);

    /* Assertions. */
    assert(out == 2);

    /* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
