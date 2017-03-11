/*
PLay with some misc work item built-in functions.

https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/workItemFunctions.html
*/

#include "common.h"

#define NUM_FUNCTIONS (8)
/* Play around with those parameters. */
static size_t offset = 4;
static size_t global = 1;
static size_t local = 1;

int main(void) {
    cl_command_queue command_queue;
    cl_int ret;
    cl_mem buffer;
    cl_uint output[NUM_FUNCTIONS];
    Common common;

	/* Run kernel. */
    common_init_file(&common, "work_item_builtin.cl");
    buffer = clCreateBuffer(common.context, CL_MEM_WRITE_ONLY, NUM_FUNCTIONS * sizeof(cl_uint), NULL, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(cl_mem), &buffer);
    command_queue = clCreateCommandQueue(common.context, common.device, 0, NULL);
    clEnqueueNDRangeKernel(command_queue, common.kernel, 1, &offset, &global, &local, 0, NULL, NULL);
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
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(command_queue);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
