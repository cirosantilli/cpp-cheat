/*
We can pass data through multiple kernels with multiple
clEnqueueNDRangeKernel calls on a single command queue.
*/

#include "common.h"

int main(void) {
    const char *source =
        "__kernel void add(__global int *out) {\n"
        "    out[get_global_id(0)]++;\n"
        "}\n"
        "__kernel void mul(__global int *out) {\n"
        "    out[get_global_id(0)] *= 2;\n"
        "}\n"
    ;
    cl_int input[] = {1, 2};
    cl_kernel kernel_add, kernel_mul;
    cl_mem buffer;
    cl_program program;
    Common common;
    const size_t global_work_size = sizeof(input) / sizeof(input[0]);

    /* Run kernel. */
    common_init(&common, NULL);
    common_create_program(&common, source, NULL, &program);
    kernel_add = clCreateKernel(program, "add", NULL);
    kernel_mul = clCreateKernel(program, "mul", NULL);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(input), input, NULL);
    clSetKernelArg(kernel_add, 0, sizeof(buffer), &buffer);
    clSetKernelArg(kernel_mul, 0, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, kernel_add, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clEnqueueNDRangeKernel(common.command_queue, kernel_mul, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(input), input, 0, NULL, NULL);

    /* Assertions. */
    assert(input[0] == 4);
    assert(input[1] == 6);

    /* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
