/*
http://stackoverflow.com/questions/9464190/error-code-11-what-are-all-possible-reasons-of-getting-error-cl-build-prog

Real programs should always check for build failures and print the error message,
which can contain great debug messages (piped from some forked compiler :-))
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <CL/cl.h>

#define COUNT (7)

int main(void) {
    const char *source =
        "__kernel void main(__global size_t *out) {\n"
        "  asdfqwer;"
        "}\n";
    cl_context context;
    cl_device_id device;
    cl_platform_id platform;
    cl_program program;

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
    {
        size_t len;
        char error_message[2048];
        cl_int err = clBuildProgram(program, 1, &device, "", NULL, NULL);
        if (err != CL_SUCCESS) {
            /* Would be wise to have a switch that transforms all possible codes into strings here. */
            printf("clBuildProgram failed. Error code: %d\n", err);
            clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(error_message), error_message, &len);
            printf("error message = %s\n", error_message);
        }
    }
    return EXIT_SUCCESS;
}
