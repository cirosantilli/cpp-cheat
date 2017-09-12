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

void common_assert_success(cl_int ret) {
    assert(ret == CL_SUCCESS);
}

char* common_read_file(const char *path, long *length_out) {
    char *buffer;
    FILE *f;
    long length;

    f = fopen(path, "r");
    assert(NULL != f);
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = (char *)malloc(length);
    if (fread(buffer, 1, length, f) < (size_t)length) {
        return NULL;
    }
    fclose(f);
    if (NULL != length_out) {
        *length_out = length;
    }
    return buffer;
}

char* common_read_file_null(const char *path) {
    char *f;
    long length;
    f = common_read_file(path, &length);
    f = (char *)realloc(f, length + 1);
    f[length] = '\0';
    return f;
}

void common_build_program(
    Common *common,
    const char *options,
    cl_program *program
) {
    char *err;
    cl_int ret;
    size_t err_len;
    ret = clBuildProgram(*program, 1, &(common->device), options, NULL, NULL);
    if (CL_SUCCESS != ret) {
        clGetProgramBuildInfo(*program, common->device, CL_PROGRAM_BUILD_LOG, 0, NULL, &err_len);
        err = (char *)malloc(err_len);
        clGetProgramBuildInfo(*program, common->device, CL_PROGRAM_BUILD_LOG, err_len, err, NULL);
        fprintf(stderr, "error: clBuildProgram:\n%s\n", err);
        free(err);
        exit(EXIT_FAILURE);
    }
}

void common_create_program(
    Common *common,
    const char *source,
    const char *options,
    cl_program *program
) {
    *program = clCreateProgramWithSource(common->context, 1, &source, NULL, NULL);
    common_build_program(common, options, program);
}

void common_create_kernel(
    Common *common,
    const char *source,
    const char *options
) {
    if (NULL != source) {
        common_create_program(common, source, options, &common->program);
        common->kernel = clCreateKernel(common->program, "kmain", NULL);
        assert(NULL != common->kernel);
    } else {
        common->kernel = NULL;
        common->program = NULL;
    }
}

void common_create_kernel_file(
    Common *common,
    const char *source_path,
    const char *options
) {
    char *source;
    source = common_read_file_null(source_path);
    common_create_kernel(common, source, options);
    free(source);
}

/*
 * @param[in] source: if NULL, kernel and program are left to NULL on common
 **/
void common_init_options(
    Common *common,
    const char *source,
    const char *options
) {
    cl_platform_id platform;

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &(common->device), NULL);
    common->context = clCreateContext(NULL, 1, &(common->device), NULL, NULL, NULL);
    common->command_queue = clCreateCommandQueue(common->context, common->device, 0, NULL);
    common_create_kernel(common, source, options);
}

void common_init(
    Common *common,
    const char *source
) {
    common_init_options(common, source, "");
}

void common_init_file_options(
    Common *common,
    const char *source_path,
    const char *options
) {
    char *source;
    source = common_read_file_null(source_path);
    common_init_options(common, source, options);
    free(source);
}

void common_init_file(
    Common *common,
    const char *source_path
) {
    common_init_file_options(common, source_path, "");
}

void common_deinit_kernel_and_program(cl_kernel kernel, cl_program program) {
    if (NULL != kernel) {
        clReleaseKernel(kernel);
    }
    if (NULL != program) {
        clReleaseProgram(program);
    }
}

void common_deinit(
    Common *common
) {
    clReleaseCommandQueue(common->command_queue);
    common_deinit_kernel_and_program(common->kernel, common->program);
    clReleaseContext(common->context);
#ifdef CL_1_2
    clReleaseDevice(common->device);
#endif
}

void common_create_kernel_or_use_cache(
    Common *common,
    int use_cache,
    char *source_path,
    char *bin_path
) {
    FILE *f;
    char *binary;
    cl_int errcode_ret, binary_status;
    cl_kernel kernel;
    cl_program program;
    long length;
    size_t binary_size;

    if (use_cache) {
        common_init(common, NULL);
        binary = common_read_file(bin_path, &length);
        binary_size = length;
    } else {
        common_init_file(common, source_path);
        clGetProgramInfo(common->program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &binary_size, NULL);
        binary = (char *)malloc(binary_size);
        clGetProgramInfo(common->program, CL_PROGRAM_BINARIES, binary_size, &binary, NULL);
        f = fopen(bin_path, "w");
        fwrite(binary, binary_size, 1, f);
        fclose(f);
    }
    program = clCreateProgramWithBinary(
        common->context, 1, &common->device, &binary_size,
        (const unsigned char **)&binary, &binary_status, &errcode_ret
    );
    assert(NULL != program);
    common_assert_success(binary_status);
    common_assert_success(errcode_ret);
    free(binary);
    common_build_program(common, NULL, &program);
    kernel = clCreateKernel(program, "kmain", &errcode_ret);
    assert(NULL != kernel);
    common_assert_success(errcode_ret);
    /* Cleanup kernel and program if they were created from source. */
    common_deinit_kernel_and_program(common->kernel, common->program);
    common->kernel = kernel;
    common->program = program;
}

double common_get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

void common_vec_print_i(int *vec, size_t n) {
    size_t i;
    for (i = 0; i < n; ++i) {
        printf("%d\n", vec[i]);
    }
}

void common_vec_assert_eq_i(int *vec1, int *vec2, size_t n) {
    if (memcmp(vec1, vec2, n * sizeof(*vec1)) != 0) {
        common_vec_print_i(vec1, n);
        puts("");
        common_vec_print_i(vec2, n);
        assert(0);
    }
}

#endif
