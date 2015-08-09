#define _GNU_SOURCE

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h> /* perror */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <string.h>

#include <fcntl.h>
#include <sched.h> /* SCHED_BATCH, SCHED_IDLE, sched_getaffinity */
#include <unistd.h> /* brk, sbrk sysconf */

#include <sys/reg.h>
#include <sys/ptrace.h> /* ptrace */
#include <sys/syscall.h> /*  __NR_XXX, SYS_XXX */
#include <sys/types.h>
#include <sys/user.h> /* user_regs_struct */
#include <sys/wait.h> /* wait, sleep */

#include <gnu/libc-version.h> /* gnu_get_libc_version */
