/*
# define

# Macros

# Preprocessor

    Requires -ggdb3, just -g is not enough.

    TODO confirm: GDB extension to DWARF.

    - http://stackoverflow.com/questions/2934006/how-do-i-print-a-defined-constant-in-gdb
    - http://stackoverflow.com/questions/13418634/call-setbufstdout-null-no-symbol-null-in-the-current-context
*/

/* Contains NULL. */
#include <stdio.h>

#define ABC 123

int main() {
    return 0;
}
