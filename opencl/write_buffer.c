/*
clEnqueueWriteBuffer test.

Allows us to reuse an existing device buffer and kernel, possibly saving allocation time.
*/

#include "common.h"

int main(void) {
    const char *source =
        "__kernel void kmain(__global int *io) {\n"
        "    io[get_global_id(0)]++;\n"
        "}\n";
    cl_int io[2];
    cl_mem buffer;
    Common common;
    const size_t global_work_size = sizeof(io) / sizeof(io[0]);

    /* Setup. */
    common_init(&common, source);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE, sizeof(io), NULL, NULL);

    /* Run 1. */
    io[0] = 0;
    io[1] = 1;
    clEnqueueWriteBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(io), io, 0, NULL, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(io), io, 0, NULL, NULL);
    assert(io[0] == 1);
    assert(io[1] == 2);

    /* Run 2. */
    io[0] = 10;
    io[1] = 11;
    clEnqueueWriteBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(io), io, 0, NULL, NULL);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(io), io, 0, NULL, NULL);
    assert(io[0] == 11);
    assert(io[1] == 12);

    /* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
