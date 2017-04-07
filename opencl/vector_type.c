/*
Increment a vector type (int2) using a vector built-in type.

http://stackoverflow.com/questions/13118228/how-to-pass-vector-paramater-to-opencl-kernel-in-c

TODO: is using them faster than scalars?

- http://stackoverflow.com/questions/20200203/using-own-vector-type-in-opencl-seems-to-be-faster
*/

#include "common.h"

int main(void) {
    const char *source =
        "__kernel void kmain(__global int2 *out) {\n"
        "      out[get_global_id(0)]++;\n"
        "}\n";
    cl_int input[] = {0, 1, 2, 3};
    cl_mem buffer;
    Common common;
    const size_t global_work_size = sizeof(input) / sizeof(cl_int2);

    /* Run kernel. */
    common_init(&common, source);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(input), input, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(cl_mem), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(input), input, 0, NULL, NULL);

    /* Assertions. */
    assert(input[0] == 1);
    assert(input[1] == 2);
    assert(input[2] == 3);
    assert(input[3] == 4);

    /* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
