#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <CL/cl.h>

#define MEM_SIZE (128)

static const char *source_str =
    "__kernel void hello(__global char *string) {\n"
    "    string[0] = 'h';\n"
    "    string[1] = 'e';\n"
    "    string[2] = 'l';\n"
    "    string[3] = 'l';\n"
    "    string[4] = 'o';\n"
    "    string[5] = ' ';\n"
    "    string[6] = 'w';\n"
    "    string[7] = 'o';\n"
    "    string[8] = 'r';\n"
    "    string[9] = 'l';\n"
    "    string[10] = 'd';\n"
    "    string[11] = '\\0';\n"
    "}\n";

int main(void) {
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem memobj = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_platform_id platform_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;
    char string[MEM_SIZE];
    size_t source_size;

    source_size = strlen(source_str);

    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);
    program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
            (const size_t *)&source_size, &ret);
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    kernel = clCreateKernel(program, "hello", &ret);
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);

    /* Execute OpenCL Kernel */
    ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);
    /* Copy results from the memory buffer */
    ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
            MEM_SIZE * sizeof(char),string, 0, NULL, NULL);
    puts(string);

    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(memobj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    return EXIT_SUCCESS;
}
