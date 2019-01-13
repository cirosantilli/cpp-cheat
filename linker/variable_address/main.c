#include <stdio.h>

int __attribute__((section(".mySection"))) myvar = 0x9ABCDEF0;

int main(void) {
    printf("adr %p\n", (void*)&myvar);
    printf("val 0x%x\n", myvar);
    myvar = 0;
    printf("val 0x%x\n", myvar);
    return 0;
}
