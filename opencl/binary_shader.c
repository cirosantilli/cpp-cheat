/*
*/

#include "common.h"

int main(void) {
    const char *source =
        "__kernel void kmain(__global int *out) {\n"
        "    out[get_global_id(0)]++;\n"
        "}\n"
    ;
    cl_int input[] = {1, 2};
    cl_kernel kernel;
    cl_mem buffer;
    cl_program program;
    Common common;
    const size_t global_work_size = sizeof(input) / sizeof(input[0]);

	/* Run kernel. */
    common_init(&common, source);

    unsigned char *binary;
    size_t binary_size;
    FILE *f;

    clGetProgramInfo(common.program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &binary_size, NULL);
    binary = malloc(binary_size);
    clGetProgramInfo(common.program, CL_PROGRAM_BINARIES, binary_size, binary, NULL);

    /* Not mandatory, but fun to reverse engineer their format later on. */
    f = fopen("a.bin.tmp", "w");
    fwrite(binary, binary_size, 1, f);
    fclose(f);

    program = clCreateProgramWithBinary(common.context, 1, &common.device, &binary_size, (const unsigned char **)&binary, NULL, NULL);
    kernel = clCreateKernel(program, "kmain", NULL);
    free(binary);


    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(input), input, NULL);
    clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, sizeof(input), input, 0, NULL, NULL);

	/* Assertions. */
    assert(input[0] == 2);
    assert(input[1] == 3);

	/* Cleanup. */
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseMemObject(buffer);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
