/*Let's play with clCreateProgramWithBinary.

Compile the "inc.cl" CL C shader to binary, save the binary to a file, and load the shader from the binary:

    ./prog

Ignore the CL C shader, load binary from a file, and run it:

    ./prog 0

Use another shader instead:

    ./prog 1 dec.cl

The name "binary" is a possible lie: NVIDIA Linux driver 375.39
just dumps PTX human readable assembly, which we can modify without
reverse engineering. Hurray!
*/

#define BIN_PATH __FILE__ ".bin.tmp"

#include "common.h"

int main(int argc, char **argv) {
    Common common;
    FILE *f;
    char *binary, *source_path;
    cl_int input[] = {1, 2}, errcode_ret, binary_status;
    cl_kernel kernel;
    cl_mem buffer;
    cl_program program;
    const size_t global_work_size = sizeof(input) / sizeof(input[0]);
    int use_cache;
    long lenght;
    size_t binary_size;

    if (argc > 1) {
        use_cache = !strcmp(argv[1], "0");
    } else {
        use_cache = 0;
    }
    if (argc > 2) {
        source_path = argv[2];
    } else {
        source_path = "inc.cl";
    }

    /* Get the binary, and create a kernel with it. */
    if (use_cache) {
        common_init(&common, NULL);
        binary = common_read_file(BIN_PATH, &lenght);
        binary_size = lenght;
    } else {
        common_init_file(&common, source_path);
        clGetProgramInfo(common.program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &binary_size, NULL);
        binary = malloc(binary_size);
        clGetProgramInfo(common.program, CL_PROGRAM_BINARIES, binary_size, &binary, NULL);
        f = fopen(BIN_PATH, "w");
        fwrite(binary, binary_size, 1, f);
        fclose(f);
    }
    program = clCreateProgramWithBinary(
        common.context, 1, &common.device, &binary_size,
        (const unsigned char **)&binary, &binary_status, &errcode_ret
    );
    assert(NULL != program);
    common_assert_success(binary_status);
    common_assert_success(errcode_ret);
    free(binary);
    common_build_program(&common, NULL, &program);
    kernel = clCreateKernel(program, "kmain", &errcode_ret);
    assert(NULL != kernel);
    common_assert_success(errcode_ret);

    /* Run the kernel created from the binary. */
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
