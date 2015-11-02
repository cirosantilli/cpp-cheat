/*
Minimal OpenCL program that does something observable: increment a number.
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <CL/cl.h>

int main() {
    cl_command_queue command_queue;
    cl_context context;
    cl_device_id device;
    cl_int input = 1;
    cl_int kernel_result = 0;
    cl_kernel kernel;
    cl_mem buffer;
    cl_platform_id platform;
    cl_program program;
    const char *source = "__kernel void increment(int in, __global int* out) { out[0] = in + 1; }";

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    command_queue = clCreateCommandQueue(context, device, 0, NULL);
    buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(cl_int), NULL, NULL);
    program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
    clBuildProgram(program, 1, &device, "", NULL, NULL);
    kernel = clCreateKernel(program, "increment", NULL);
    clSetKernelArg(kernel, 0, sizeof(cl_int), &input);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &buffer);
    clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
    clFlush(command_queue);
    clFinish(command_queue);
    clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, sizeof (cl_int), &kernel_result, 0, NULL, NULL);

    assert(kernel_result == 2);
    return EXIT_SUCCESS;
}
