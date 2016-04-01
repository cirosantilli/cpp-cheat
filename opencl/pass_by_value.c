/*
Increment a vector. It is useless to do this on a GPU, not enough work / IO.
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <CL/cl.h>

int main(void) {
    const char *source =
        "__kernel void main(int in, __global int *out) {\n"
        "    out[0] = in + 1;\n"
        "}\n";
    cl_command_queue command_queue;
    cl_context context;
    cl_device_id device;
    cl_int input = 1;
    cl_kernel kernel;
    cl_mem buffer;
    cl_platform_id platform;
    cl_program program;

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    command_queue = clCreateCommandQueue(context, device, 0, NULL);
    buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int), NULL, NULL);
    program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
    clBuildProgram(program, 1, &device, "", NULL, NULL);
    kernel = clCreateKernel(program, "main", NULL);
    clSetKernelArg(kernel, 0, sizeof(cl_int), &input);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &buffer);
    clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
    clFlush(command_queue);
    clFinish(command_queue);
    clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, sizeof(cl_int), &input, 0, NULL, NULL);

    assert(input == 2);
    return EXIT_SUCCESS;
}
