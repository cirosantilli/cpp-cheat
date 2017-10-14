/*
# Virtual memory

# Process address space

    Let's have some fun reverse engeneering the process memory space modeul used on your OS!

    This is all implementation defined behaviour on ANSI C, but the test code is the same on all OS.

    All of this reflects how the process is represented in main memory.
*/

#include "common.h"

int bss = 0;
int data = 1;

int main(int argc, char **argv) {
    int stack1;
    int stack2;
    void *heap;
    char *str = "abc";
    heap = malloc(1);

    printf("  &env        = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)getenv("HOME"));
    printf("  &argv       = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)argv);
    printf("  &argc       = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&argc);
    printf("  &stack1     = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&stack1);
    printf("  &stack2     = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&stack2);
    printf("  &heap       = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)heap);
    printf("  &bss        = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&bss);
    printf("  &data       = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&data);
    printf("  &main       = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&main);
    printf("  &str char*  = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&str);

    free(heap);
    return EXIT_SUCCESS;
}
