/*
Sample usage:

	echo '1 2 3' | tr ' ' '\n' >vec_io.vec
	./prog vec_io.cl vec_io.vec

Or you can use the default kernel and stdin input:

	echo '1 2 3' | tr ' ' '\n' | ./prog

Generic boilerplate that:

-     takes a vector as input either from stdin or from a file, one per line

-     processes it with a kernel read from a file, one vector item per work item

-     produces as output a vector of the same size to stdout

This allows you to quickly play with different kernels without recompiling the C code.

But is unsuitable for real applications, which require  querying the CL implementation
for limits, specially work group and memory maximum sizes.
*/

#include "common.h"

int main(int argc, char **argv) {
    char *cl_source_path;
    cl_float *io;
    cl_mem buffer;
    Common common;
    FILE *input_vector_file;
    float f;
    size_t i, n, nmax, io_sizeof;

    /* Treat CLI arguments. */
    if (argc > 1) {
        cl_source_path = argv[1];
    } else {
        cl_source_path = "vec_io.cl";
    }
    if (argc > 2) {
        input_vector_file = fopen(argv[2], "r");
    } else {
        input_vector_file = stdin;
    }

    /* Initialize data. */
    n = 0;
    nmax = n + 1;
    io = malloc(nmax * sizeof(*io));
    while(fscanf(input_vector_file, "%f", &f) != EOF) {
        io[n] = f;
        n++;
        if (n == nmax) {
            nmax *= 2;
            io = realloc(io, nmax * sizeof(*io));
        }
    }
    io_sizeof = n * sizeof(*io);

    /* Run kernel. */
    common_init_file(&common, cl_source_path);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, io_sizeof, io, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &n, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, io_sizeof, io, 0, NULL, NULL);

    /* Print result. */
    for (i = 0; i < n; ++i) {
        printf("%f\n", io[i]);
    }

    /* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
    free(io);
    fclose(input_vector_file);
    return EXIT_SUCCESS;
}
