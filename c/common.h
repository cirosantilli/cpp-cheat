#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h> /* PRIxPTR,  */
#include <iso646.h>
#include <limits.h> /* *_MAX, *_MIN for integer types */
#include <locale.h>
#include <setjmp.h> /* setjmp, longjmp */
#include <signal.h>
#include <stdbool.h> /* false, true */
#include <stdarg.h> /* ..., va_list, va_start, va_arg, va_end */
#include <stddef.h> /* offsetof, ptrdiff_t, size_t, type_t */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE, malloc, rand, srand */
#include <stdio.h> /* printf, puts */
#include <string.h> /* sprintf, strlen, strcpy, memset, memcmp */
#include <math.h>
#include <time.h> /* time() */
#include <wchar.h>
#if __STDC_VERSION__ >= 199901L
# ifndef __STDC_NO_COMPLEX__
#  include <complex.h>
# endif
# if __STDC_VERSION__ >= 201112L
#  include <stdnoreturn.h>
#  ifndef __STDC_NO_THREADS__
#   include <threads.h>
#  endif
# endif
#endif

#define COMMON_TMP_EXT ".tmp"
#define COMMON_TMPFILE __FILE__ COMMON_TMP_EXT
#define COMMON_TMPFILE_NAMED(name) __FILE__ "__" name COMMON_TMP_EXT
#define COMMON_ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

/* Standard action to take in case of an IO error. */
#define COMMON_IO_ERROR(function, path) \
    fprintf(stderr, "error: %s errno = %d, path = %s\n", function, errno, path); \
    exit(EXIT_FAILURE);

#define PRIxPTR_WIDTH ((int)(sizeof(void*)*2))

#endif
