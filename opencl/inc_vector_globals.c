/*
API exercise, increment a vector with less global work groups than integers,
which forces us to put a for loop in the kernel.

I don't think we can get the size of each global work group from the kernel,
so we just calculate it on CPU and pass as a parameter.

This is how the work will be split:

    | work group 0 | work group 1 | work group 2 |
    | in[0] in[1]  | in[2] in[3]  | in[4]        |
*/

#include "common.h"

#define FAKE_MAX_GROUP_NELEMS 2

int main(void) {
    const char *source =
        "__kernel void kmain(uint group_nlems, __global int *out) {\n"
        "    uint i_min = get_global_id(0) * group_nlems;\n"
        "    uint i_max = i_min + group_nlems;\n"
        "    for (uint i = i_min; i < i_max; ++i) {\n"
        "        out[i]++;\n"
        "    };\n"
        "}\n";
    /* Not a multiple of work size on purpose, so we have to think about the edge case.
     * We can neither:
     * - add an if to the kernel. But I don't want to do that as it slows every kernel down.
     * - pad with trash to a multiple
     * */
    cl_int io[] = {1, 2, 3, 4, 5}, *io_align;
    cl_mem buffer;
    Common common;
    const cl_uint nelems = sizeof(io) / sizeof(io[0]);
    const cl_uint group_nelems = FAKE_MAX_GROUP_NELEMS;
    const size_t global_work_size = 1 + (nelems - 1) / FAKE_MAX_GROUP_NELEMS;
    const size_t nelems_align = global_work_size * group_nelems;
    const size_t io_align_sizeof = nelems_align * sizeof(*io_align);

    /* Run kernel. */
    io_align = malloc(io_align_sizeof);
    memcpy(io_align, io, sizeof(io));
    common_init(&common, source);
    clSetKernelArg(common.kernel, 0, sizeof(group_nelems), &group_nelems);
    buffer = clCreateBuffer(common.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, io_align_sizeof, io_align, NULL);
    clSetKernelArg(common.kernel, 1, sizeof(buffer), &buffer);
    clEnqueueNDRangeKernel(common.command_queue, common.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFlush(common.command_queue);
    clFinish(common.command_queue);
    clEnqueueReadBuffer(common.command_queue, buffer, CL_TRUE, 0, io_align_sizeof, io_align, 0, NULL, NULL);

    /* Assertions. */
    assert(io_align[0] == 2);
    assert(io_align[1] == 3);
    assert(io_align[2] == 4);
    assert(io_align[3] == 5);
    assert(io_align[4] == 6);

    /* Cleanup. */
    free(io_align);
    clReleaseMemObject(buffer);
    common_deinit(&common);
    return EXIT_SUCCESS;
}
