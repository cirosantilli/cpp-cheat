/*
Process an arbitrary input vector with a given shader and print output to stdout.

Sample usage:

    echo '1 2 3' | tr ' ' '\n' >vec_io.vec
    ./prog vec_io.cl vec_io.vec

Output:

    2.000000e+00
    3.000000e+00
    4.000000e+00

Or you can use the default kernel and stdin input:

    echo '1 2 3' | tr ' ' '\n' | ./prog

Multi vector operations can be done by reusing parts of the vector as in `+=`, e.g.:

	echo '1 2 3 4' | tr ' ' '\n' | ./vec_io.out vec_io_sum.cl

gives:

	4.000000e+00
	6.000000e+00
	3.000000e+00
	4.000000e+00

which represents:

	(1, 2) += (3, 4) == (4, 6)

Set global work size and work group size different than defaults (n and 1):

    ./prog -g 10 -l 5 vec_io.cl vec_io.vec

Generate a binary shader , and then use it (clCreateProgramWithBinary) instead of the CL C:

    ./prog vec_io.cl vec_io.vec
    ./prog -b vec_io.c.bin.tmp vec_io.vec

This allows you to modify the binary shader while reverse engineer it.

Generic boilerplate that:

- takes a vector as input either from stdin or from a file, one per line
- processes it with a kernel read from a file, one vector item per work item (configurable with options)
- produces as output a vector of the same size to stdout

This allows you to quickly play with different kernels without recompiling the C code.

But is unsuitable for real applications, which require  querying the CL implementation
for limits, specially work group and memory maximum sizes. Although you could use a script
to parse clinfo and get those values out... hmmm...
*/

#include "common.h"

int main(int argc, char **argv) {
    char *source_path;
    cl_float *io;
    cl_mem buffer;
    Common common;
    FILE *input_vector_file;
    float f;
    int a, global_work_size_given, use_cache;
    size_t i, global_work_size, local_work_size, n, nmax, io_sizeof;

    /* Treat CLI arguments. */
    global_work_size_given = 0;
    local_work_size = 1;
    use_cache = 0;
    for (a = 1; a < argc; ++a) {
        if (argv[a][0] == '-') {
            switch(argv[a][1]) {
                case 'b':
                    use_cache = 1;
                break;
                case 'g':
                    a++;
                    global_work_size = strtoul(argv[a], NULL, 10);
                    global_work_size_given = 1;
                break;
                case 'l':
                    a++;
                    local_work_size = strtoul(argv[a], NULL, 10);
                break;
            }
        } else {
            break;
        }
    }
    if (argc > a) {
        source_path = argv[a];
    } else {
        source_path = (char *)"vec_io.cl";
    }
    a++;
    if (argc > a) {
        input_vector_file = fopen(argv[a], "r");
    } else {
        input_vector_file = stdin;
    }

    /* Initialize data. */
    n = 0;
    nmax = n + 1;
    io = (cl_float *)malloc(nmax * sizeof(*io));
    while(fscanf(input_vector_file, "%f", &f) != EOF) {
        io[n] = f;
        n++;
        if (n == nmax) {
            nmax *= 2;
            io = (cl_float *)realloc(io, nmax * sizeof(*io));
        }
    }
    io_sizeof = n * sizeof(*io);
    if (!global_work_size_given) {
        global_work_size = n;
    }

    /* Create kernel. */
    common_create_kernel_or_use_cache(&common, use_cache, source_path, (char *)(__FILE__ ".bin.tmp"));
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, io_sizeof, io, NULL);
    clSetKernelArg(common.kernel, 0, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, io_sizeof, io, 0, NULL, NULL);

    /* Print result. */
    for (i = 0; i < n; ++i) {
        printf("%.6e\n", io[i]);
    }

    /* Cleanup. */
    clReleaseMemObject(buffer);
    common_deinit(&common);
    free(io);
    fclose(input_vector_file);
    return EXIT_SUCCESS;
}
