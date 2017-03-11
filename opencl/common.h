#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// http://stackoverflow.com/questions/28500496/opencl-function-found-deprecated-by-visual-studio
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>

typedef struct {
    cl_context context;
    cl_device_id device;
    cl_kernel kernel;
    cl_program program;
} Common;

static void common_init(
    Common *common,
    const char *source
) {
	char *err;
	size_t err_len;
    cl_int ret;
    cl_platform_id platform;

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &(common->device), NULL);
    common->context = clCreateContext(NULL, 1, &(common->device), NULL, NULL, NULL);
    common->program = clCreateProgramWithSource(common->context, 1, &source, NULL, NULL);
    ret = clBuildProgram(common->program, 1, &(common->device), "", NULL, NULL);
    if (CL_SUCCESS != ret) {
		clGetProgramBuildInfo(common->program, common->device, CL_PROGRAM_BUILD_LOG, 0, NULL, &err_len);
		err = malloc(err_len);
		clGetProgramBuildInfo(common->program, common->device, CL_PROGRAM_BUILD_LOG, err_len, err, NULL);
		fprintf(stderr, "error: kernel build:\n%s\n", err);
		free(err);
		exit(EXIT_FAILURE);
    }
    common->kernel = clCreateKernel(common->program, "main", NULL);
}

static char * common_read_file(const char *path) {
    char *buffer;
    FILE *f;
    long length;

    f = fopen(path, "r");
    fseek (f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = calloc(1, length + 1);
    fread (buffer, 1, length, f);
    fclose (f);
    buffer[length] = '\0';
    return buffer;
}

static void common_init_file(
    Common *common,
    const char *source_path
) {
    char *source;
    source = common_read_file(source_path);
    common_init(common, source);
    free(source);
}

static void common_deinit(
    Common *common
) {
    clReleaseProgram(common->program);
    clReleaseKernel(common->kernel);
    clReleaseContext(common->context);
    clReleaseDevice(common->device);
}

#endif
