#ifndef COMMON_H
#define COMMON_H

/* Enable GNU extensions present in the standard headers. */
#define _GNU_SOURCE

/* C */
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h> /* perror */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <string.h>

/* POSIX */
#include <semaphore.h>
#include <fcntl.h>
#include <sched.h> /* SCHED_BATCH, SCHED_IDLE, sched_getaffinity */
#include <sys/mman.h> /* mmap */
#include <sys/types.h>
#include <sys/wait.h> /* wait, sleep */
#include <unistd.h> /* brk, sbrk sysconf */

/* glibc. */
#include <gnu/libc-version.h> /* gnu_get_libc_version */
#include <sys/ptrace.h> /* ptrace */
#include <sys/reg.h>
#include <sys/syscall.h> /*  __NR_XXX, SYS_XXX */
#include <sys/user.h> /* user_regs_struct */

#endif
