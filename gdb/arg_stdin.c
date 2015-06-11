/*
- gdb --args arg_stdin.out arg arg1
- set args arg0 arg1 <stdin_file
*/

#include <stdio.h>

int main(int argc, char **argv) {
    char s[16];
    fgets(s, sizeof(s), stdin);
    printf("stdin line 0 = %s", s);
    printf("argv[0] = %s\n", argv[0]);
    if (argc > 1) {
        printf("argv[1] = %s\n", argv[1]);
        if (argc > 2) {
            printf("argv[2] = %s\n", argv[2]);
        }
    }
    return 0;
}
