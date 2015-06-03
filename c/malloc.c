/*
# malloc

    The main way to get new dynamic memory.

    Returns a `void*` which can be used for any type.

    Typecast from `void*` is implicitly done without warning.

    On Linux, implemented with either:

    - brk
    - mmap

    This is one of those library functions which cannot be implemented in pure C itself,
    as they require system calls.

    See also: glibc non-POSIX alloca which allocates on the stack.

    # malloc vs VLA

        Dynamic memory has the following characteristics which VLA does not:

        -   no scope

            therefore can be allocated in functions
            and returned to caller

        -   heap much larger than stack

        So it is more flexible, at the cost of some runtime speed.
*/

#include "common.h"

int main() {
    /* Basic usage */
    {
        size_t bytes = sizeof(int) * 2;
        int *is = malloc(bytes);
        if (is == NULL) {
            printf("malloc failed\n");
        } else {
            is[0] = 1;
            assert(is[0] == 1);
            free(is);
        }
    }

    /*
    # free

        Main way to free dynamic memory after you are done with it.

        Freeing a NULL pointer does nothing:
        http://stackoverflow.com/questions/1938735/does-freeptr-where-ptr-is-null-corrupt-memory
    */
    {
        free(NULL);

        /*
        WARN attempted to free a non heap object.

        If this compiled, it could lead to segfault.
        */
        {
            int i;
            /*free(&i);*/
        }

        /* freeing a pointer twice leads to a segfault */
        {
            int *ip = malloc(sizeof(int));
            free(ip);
            /* RUNTIME ERROR: segmentation fault. */
            /*free(ip);*/
        }
    }

    /*
    # realloc

        Change size of allocated memory with malloc.

        If you already have allocated some memory, it might be faster to enlargen it
        rather than to free it and reallocate.

        The library may however choose to move your memory somewhere else if not enough is available

        You must use a second pointer to get its value, because in case the reallocation fails,
        you still need the old pointer to clear up old memory.
    */
    {
        size_t bytes = sizeof(int) * 2;
        int *is = malloc(bytes);
        if (is == NULL) {
            printf("malloc failed\n");
        } else {
            is[1] = 1;
            /* You must use a second pointer here. */
            int *is2 = realloc(is, sizeof(int) * 4);
            if (is2 == NULL) {
                printf("realloc failed\n");
            } else {
                is = is2;
                is[3] = 1;
                /* Old values are untouched. */
                assert(is[1] == 1);
                assert(is[3] == 1);
            }
            free(is);
        }
    }

    /*
    # calloc

        Like malloc but initializes allocated bytes to zero.

        why calloc? <http://www.quora.com/C-programming-language/What-does-the-c-stand-for-in-calloc>
        Clear seems most likely.

        Takes number of elements and elemetn size separately.
    */
    {
        int *is = calloc(2, sizeof(int));
        if (is == NULL) {
            printf("calloc failed\n");
        } else {
            assert(is[0] == 0);
            assert(is[1] == 0);
            free(is);
        }
    }

    /*
    # malloc multi dimensional arrays

        http://stackoverflow.com/questions/1970698/c-malloc-for-two-dimensional-array

        For a 2D N x M array, there are two solutions:

        - N mallocs of size M
        - one malloc of size N x M

        In C++, using vectors of vectors is an easier solution.
    */
    {
        /* One malloc. */
        {
        }
    }

    /*
    # Allocate too much memory

        If you try to allocate too much memory:

        - TODO OS kill programs, or malloc fails gracefuly?

        Time to try that out!

        TODO how to pass more than INT_MAX to malloc to break it? =)
    */
    {
        if (0) {
            size_t n = 1024 * 1024 * 1024;
            int *ip = malloc(n);
            if (ip == NULL) {
                printf("could not allocate %zu bytes", n);
            }
            free(ip);
        }

        /*
        Allocate 1024 Petabytes of RAM in 1 gb chunks!!!

        Someday this will be possible and people will laugh at this...

        Generates a segfault today.
        */
        if (0) {
            const size_t GB = 1 << 30;
            for (unsigned int i = 0; i < GB; i++) {
                int *ip = malloc(GB);
                ip[0] = 0;
                if (ip == NULL) {
                    printf("could not allocate %zu bytes", GB);
                }
            }
        }
    }
    return EXIT_SUCCESS;
}
