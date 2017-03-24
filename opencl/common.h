#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* http://stackoverflow.com/questions/28500496/opencl-function-found-deprecated-by-visual-studio */
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>

/* Encapsulates objects that we use the same on most programs.
 * This excludes, notably, buffers. */
typedef struct {
    cl_command_queue command_queue;
    cl_context context;
    cl_device_id device;
    cl_kernel kernel;
    cl_program program;
} Common;

void common_init_options(
    Common *common,
    const char *source,
    const char *options
) {
	char *err;
	size_t err_len;
    cl_int ret;
    cl_platform_id platform;

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &(common->device), NULL);
    common->context = clCreateContext(NULL, 1, &(common->device), NULL, NULL, NULL);
    common->command_queue = clCreateCommandQueue(common->context, common->device, 0, NULL);
    if (NULL != source) {
        common->program = clCreateProgramWithSource(common->context, 1, &source, NULL, NULL);
        ret = clBuildProgram(common->program, 1, &(common->device), options, NULL, NULL);
        if (CL_SUCCESS != ret) {
            clGetProgramBuildInfo(common->program, common->device, CL_PROGRAM_BUILD_LOG, 0, NULL, &err_len);
            err = malloc(err_len);
            clGetProgramBuildInfo(common->program, common->device, CL_PROGRAM_BUILD_LOG, err_len, err, NULL);
            fprintf(stderr, "error: kernel build:\n%s\n", err);
            free(err);
            exit(EXIT_FAILURE);
        }
        common->kernel = clCreateKernel(common->program, "main", NULL);
    } else {
        common->kernel = NULL;
        common->program = NULL;
    }
}

void common_init(
    Common *common,
    const char *source
) {
	common_init_options(common, source, "");
}

char* common_read_file(const char *path) {
    char *buffer;
    FILE *f;
    long length;

    f = fopen(path, "r");
    assert(NULL != f);
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);
    if (fread(buffer, 1, length, f) < (size_t)length) {
    	return NULL;
    }
    fclose(f);
    buffer[length] = '\0';
    return buffer;
}

void common_init_file_options(
    Common *common,
    const char *source_path,
    const char *options
) {
    char *source;
    source = common_read_file(source_path);
    common_init_options(common, source, options);
    free(source);
}

void common_init_file(
    Common *common,
    const char *source_path
) {
	common_init_file_options(common, source_path, "");
}

void common_deinit(
    Common *common
) {
    clReleaseCommandQueue(common->command_queue);
    clReleaseProgram(common->program);
    if (NULL != common->kernel) {
        clReleaseKernel(common->kernel);
    }
    if (NULL != common->context) {
        clReleaseContext(common->context);
    }
#ifdef CL_1_2
	clReleaseDevice(common->device);
#endif
}

double common_get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

#endif
