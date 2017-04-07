/*
Pass an int by reference and increment it.

This is our OpenCL hello world, so we are not doing:

- error checking
- factoring out with anything else
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* To prevent deprecation warnings when headers are 2.0. */
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>

int main(void) {
    const char *source =
        /* kernel pointer arguments must be __global, __constant, or __local. */
        /* https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/restrictions.html */
        /**/
        /* Kernel functions cannot be called main... NVIDIA's compiler may allow that
         * but others don't, so don't do it. */
        "__kernel void kmain(__global int *out) {\n"
        "    out[0]++;\n"
        "}\n";
    cl_command_queue command_queue;
    cl_context context;
    cl_device_id device;
    cl_int input = 1;
    cl_kernel kernel;
    cl_mem buffer;
    cl_platform_id platform;
    cl_program program;

    /* Run kernel. */
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
    clBuildProgram(program, 1, &device, "", NULL, NULL);
    kernel = clCreateKernel(program, "kmain", NULL);
    buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_int), &input, NULL);
    clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
    command_queue = clCreateCommandQueue(context, device, 0, NULL);
    clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
    clFlush(command_queue);
    clFinish(command_queue);
    clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, sizeof(input), &input, 0, NULL, NULL);

    /* Asserts. */
    assert(input == 2);

    /* Cleanup. */
    clReleaseCommandQueue(command_queue);
    clReleaseMemObject(buffer);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseContext(context);
#ifdef CL_1_2
    clReleaseDevice(device);
#endif
    return EXIT_SUCCESS;
}
