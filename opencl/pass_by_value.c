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
    cl_context context;
    cl_device_id device;
    cl_int input = 1, ret;
    cl_kernel kernel;
    cl_mem buffer;
    cl_platform_id platform;
    cl_program program;

	/* Run kernel. */
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int), NULL, NULL);
    program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
    ret = clBuildProgram(program, 1, &device, "", NULL, NULL);
    common_check_build(ret, device, program);
    kernel = clCreateKernel(program, "main", NULL);
    clSetKernelArg(kernel, 0, sizeof(cl_int), &input);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &buffer);
    command_queue = clCreateCommandQueue(context, device, 0, NULL);
    clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
    clFlush(command_queue);
    clFinish(command_queue);
    clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, sizeof(cl_int), &input, 0, NULL, NULL);

	/* Assertions. */
    assert(input == 2);

	/* Cleanup. */
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);
    clReleaseMemObject(buffer);
    return EXIT_SUCCESS;
}
