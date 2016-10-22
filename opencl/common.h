#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

void common_check_build(
	cl_int ret,
    cl_device_id device,
    cl_program program
) {
	char *err;
	size_t err_len;
    if (CL_SUCCESS != ret) {
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &err_len);
		err = malloc(err_len);
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, err_len, err, NULL);
		printf("Kernel build error:\n%s\n", err);
		free(err);
		exit(EXIT_FAILURE);
    }
}

#endif
