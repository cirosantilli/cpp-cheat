/*
Just a small subset of clinfo, for parameters that we actually need
to query at runtim time, like work group size.

Full list at:
https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/clGetDeviceInfo.html
*/

#include "common.h"

#define PRINT_SIZE_T(id) \
    clGetDeviceInfo(device, CL_ ## id, sizeof(size_t), &(buf_size_t), NULL); \
    printf(#id " = %zu\n", buf_size_t);

#define PRINT_CL_UINT(id) \
    clGetDeviceInfo(device, CL_ ## id, sizeof(cl_uint), &(buf_cl_uint), NULL); \
    printf(#id " = %ju\n", (uintmax_t)buf_cl_uint);

int main(void) {
    cl_platform_id platform;
    cl_device_id device;
    size_t buf_size_t;
    cl_uint buf_cl_uint;

    /* Setup. */
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);

    /* Print. */
    puts("#clinfo");
    PRINT_CL_UINT(DEVICE_MAX_WORK_ITEM_DIMENSIONS)
    PRINT_SIZE_T(DEVICE_MAX_WORK_GROUP_SIZE)
    PRINT_SIZE_T(DEVICE_MAX_WORK_ITEM_SIZES)

    /* Cleanup. */
#ifdef CL_1_2
	clReleaseDevice(device);
#endif
    return EXIT_SUCCESS;
}
