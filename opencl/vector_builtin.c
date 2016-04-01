/*
Increment a vector using a vector built-in type.

TODO why does it not work?

http://stackoverflow.com/questions/13118228/how-to-pass-vector-paramater-to-opencl-kernel-in-c
*/

#include <assert.h>
#include <stdlib.h>

#include <CL/cl.h>

int main(void) {
    const char *source =
        "__kernel void main(__global int2 *out) {\n"
        "      out[get_global_id(0)]++;\n"
        "}\n";
    cl_command_queue command_queue;
    cl_context context;
    cl_device_id device;
    cl_int input[] = {0, 1, 2, 3};
    const size_t global_work_size = sizeof(input) / sizeof(cl_int2);
    cl_kernel kernel;
    cl_mem buffer;
    cl_platform_id platform;
    cl_program program;

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    command_queue = clCreateCommandQueue(context, device, 0, NULL);
    buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(input), &input, NULL);
    program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
    clBuildProgram(program, 1, &device, "", NULL, NULL);
    kernel = clCreateKernel(program, "main", NULL);
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer);
    clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(command_queue);
    clFinish(command_queue);
    clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, sizeof(input), &input, 0, NULL, NULL);

    assert(input[0] == 1);
    assert(input[1] == 2);
    assert(input[2] == 3);
    assert(input[3] == 4);
    return EXIT_SUCCESS;
}
