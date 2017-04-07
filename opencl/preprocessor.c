/*
This is a way to pass constants to the code.

In particular, it allows to allocate private arrays with a given length.

You could of course use the source itself as a template for snprintf,
but this is a bit nicer.
*/

#include "common.h"

int main(void) {
    char options[256];
    const char *source =
        "__kernel void kmain(__global int *out) {\n"
        "    out[0] = X;\n"
        "}\n";
    cl_int io[] = {0};
    const cl_int X = 1;
    cl_mem buffer;
    Common common;
    const size_t global_work_size = sizeof(io) / sizeof(io[0]);

    /* Run kernel. */
    snprintf(options, sizeof(options), "-DX=%d", X);
    common_init_options(&common, source, options);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(io), io, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(io), io, 0, NULL, NULL);

    /* Assertions. */
    assert(io[0] == X);

    /* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
