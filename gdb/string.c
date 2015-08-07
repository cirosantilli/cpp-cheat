/*
String.

- http://stackoverflow.com/questions/1530736/how-to-print-a-null-terminated-string-with-newlines-without-showing-backslash-es
- http://stackoverflow.com/questions/2821033/assembly-gdb-print-string
- http://stackoverflow.com/questions/12758217/printing-string-pointed-to-from-register-in-gdb
*/

#include <stdio.h>

char *s = "ab\ncd\n";

int main() {
    printf("%s\n", s);
    return 0;
}
