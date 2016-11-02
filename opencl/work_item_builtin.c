/*
https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/workItemFunctions.html
*/

#include "common.h"

#define NUM_FUNCTIONS (8)
/* Play around with those parameters. */
static size_t offset = 4;
static size_t global = 1;
static size_t local = 1;

int main(void) {
    const char *source =
        "__kernel void main(__global uint *out) {\n"
        "    out[0] = get_work_dim();\n"
        /* Total number of work items that will run this kernel possibly in parallel. */
        "    out[1] = get_global_size(0);\n"
        /* Unique global ID of the current work item. */
        "    out[2] = get_global_id(0);\n"
        /* Number of work items in this group. */
        "    out[3] = get_local_size(0);\n"
        /* Local ID of this work item inside this work group. */
        "    out[4] = get_local_id(0);\n"
        /* How many work groups will execute this kernel, == global_size / local_size */
        "    out[5] = get_num_groups(0);\n"
        /* Current group. */
        "    out[6] = get_group_id(0);\n"
        /* Global offset passed on to NDrange. */
        "    out[7] = get_global_offset(0);\n"
        "}\n";
    cl_command_queue command_queue;
    cl_context context;
    cl_device_id device;
    cl_int ret;
    cl_kernel kernel;
    cl_mem buffer;
    cl_platform_id platform;
    cl_program program;
    cl_uint output[NUM_FUNCTIONS];

	/* Run kernel. */
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, NUM_FUNCTIONS * sizeof(cl_uint), NULL, NULL);
    program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
    ret = clBuildProgram(program, 1, &device, "", NULL, NULL);
    common_check_build(ret, device, program);
    kernel = clCreateKernel(program, "main", NULL);
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer);
    command_queue = clCreateCommandQueue(context, device, 0, NULL);
    clEnqueueNDRangeKernel(command_queue, kernel, 1, &offset, &global, &local, 0, NULL, NULL);
    clFlush(command_queue);
    clFinish(command_queue);
    clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, NUM_FUNCTIONS * sizeof(cl_uint), &output, 0, NULL, NULL);

	/* Check the values. */
    printf("work_dim      = %d\n", output[0]);
    printf("global_size   = %d\n", output[1]);
    printf("global_id     = %d\n", output[2]);
    printf("local_size    = %d\n", output[3]);
    printf("local_id      = %d\n", output[4]);
    printf("num_groups    = %d\n", output[5]);
    printf("group_id      = %d\n", output[6]);
    printf("global_offset = %d\n", output[7]);

	/* Cleanup. */
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);
    clReleaseMemObject(buffer);
    return EXIT_SUCCESS;
}
