/*
Just a small subset of clinfo, for parameters that we actually need
to query at runtim time, like work group size.

Full list at:
https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/clGetDeviceInfo.html
*/

#include "common.h"

#define PRINT_CHAR(id) \
    clGetDeviceInfo(device, CL_ ## id, sizeof(buf_char), buf_char, NULL); \
    printf(#id " = %s\n", buf_char);

#define PRINT_SIZE_T(id) \
    clGetDeviceInfo(device, CL_ ## id, sizeof(buf_size_t), &(buf_size_t), NULL); \
    printf(#id " = %zu\n", buf_size_t);

#define PRINT_CL_UINT(id) \
    clGetDeviceInfo(device, CL_ ## id, sizeof(buf_cl_uint), &(buf_cl_uint), NULL); \
    printf(#id " = %ju\n", (uintmax_t)buf_cl_uint);

#define PRINT_CL_ULONG(id) \
    clGetDeviceInfo(device, CL_ ## id, sizeof(buf_cl_ulong), &(buf_cl_ulong), NULL); \
    printf(#id " = 0x%lx\n", (uintmax_t)buf_cl_ulong);

int main(void) {
    /* TODO how to ensure that this is big enough? */
    char buf_char[0x1000];
    cl_device_id device;
    cl_platform_id platform;
    cl_uint buf_cl_uint;
    cl_ulong buf_cl_ulong;
    size_t buf_size_t;

    /* Setup. */
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);

    /* Print. */
    puts("#clinfo");
    PRINT_CHAR(DEVICE_EXTENSIONS);
    PRINT_CHAR(DEVICE_NAME);
    PRINT_CHAR(DEVICE_PROFILE);
    PRINT_CHAR(DEVICE_VENDOR);
    PRINT_CHAR(DEVICE_VERSION);
    PRINT_CHAR(DRIVER_VERSION);
    PRINT_SIZE_T(DEVICE_MAX_WORK_GROUP_SIZE);
    PRINT_CL_UINT(DEVICE_MAX_WORK_ITEM_DIMENSIONS);
    /* TODO this is wrong, it is actually an array of
     * DEVICE_MAX_WORK_ITEM_DIMENSIONS elements.
     * But yeah, likely the same for all dimensions,
     * and equal to DEVICE_MAX_WORK_GROUP_SIZE. */
    PRINT_SIZE_T(DEVICE_MAX_WORK_ITEM_SIZES);
    PRINT_CL_ULONG(DEVICE_LOCAL_MEM_SIZE);
    PRINT_CL_UINT(DEVICE_MAX_COMPUTE_UNITS);

    /* Cleanup. */
#ifdef CL_1_2
    clReleaseDevice(device);
#endif
    return EXIT_SUCCESS;
}
