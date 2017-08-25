/*
# brk

# sbrk

    https://stackoverflow.com/questions/6988487/what-does-brk-system-call-do/31082353#31082353

    Was in POSIX 2001, but got removed.

    You must have in your mind:

        ---> brk
        |
        | Heap. Grows up ^^^
        |
        ---> brk_start
        |
        | brk random offset ASLR
        |
        ---> bss end

    Get and set the break data segment (TODO is it really the data semgment? what about the brk offset?)
    that the kernel assigns to the process.

    Set it to an absolute value, and return -1 on failure, 0 on success:

        int brk(void*)

    Move it by the given delta, and return the *old* value on success, `-1` on failure:

        void *sbrk(intptr_t increment);

    This is where the heap lives: `malloc` may use those system calls to do its job,
    although it can also use `mmap`.

    Once the `brk` is changed,
    the application can then use the newly allocated memory as it pleases,
    and the Kernel must treat that zone as being used and preserve it.

    The kernel may just say: you are taking up too much memory,
    or "this would overlap with another memory regions", and deny the request.

# Get heap size

    - http://stackoverflow.com/questions/8367001/how-to-check-heap-size-for-a-process-on-linux
    - http://stackoverflow.com/questions/2354507/how-to-find-size-of-heap-present-in-linux

    More precisely, how to get the `brk_start`?
*/

#include "common.h"

int main(void) {
    /* Get the top of the heap. */
    {
        void *b = sbrk(0);
        printf("sbrk(0) = %p\n", b);
    }

    /* Allocate 2 characters on the heap. */
    {
        /* With sbrk. */
        {
            size_t size = 2 * sizeof(char);
            void *b = sbrk(size);
            if (b != (void*)-1) {
                /* Now we safely use s2 an s2 + 1 to store what we want. */
                char *p = (char *)b;
                *p = (char)1;
                *(p + 1) = (char)2;
                assert(*p == (char)1);
                assert(*(p + 1) == (char)2);
                /* Restore it back. This is more convenient with brk. */
                if (sbrk(-size) == (void*)-1) {
                    perror("sbrk");
                    exit(EXIT_FAILURE);
                }
            } else {
                perror("sbrk");
            }
        }

        /*
        With brk.

        The initial allocation is more convenient with sbrk,
        since we need an initial sbrk anyways to find the current break.
        */
        {
            size_t size = 2 * sizeof(char);
            void *b = sbrk(0);
            char *p = (char *)b;
            if (brk(p + size) == 0) {
                *p = (char)1;
                *(p + 1) = (char)2;
                assert(*p == (char)1);
                assert(*(p + 1) == (char)2);
                if (brk(b)) {
                    perror("brk");
                    exit(EXIT_FAILURE);
                }
            } else {
                perror("brk");
            }
        }
    }

#if 0
    /*
    Attempting this without changing `brk` is an almost sure segfault:
    unlike the stack, you can't just increment the heap directly,
    Linux prevents you.
    */
    {
        void *b = sbrk(0);
        char *p = (char *)b;
        /* SEGFAULT */
        *p = 1;
    }
#endif

    return EXIT_SUCCESS;
}
