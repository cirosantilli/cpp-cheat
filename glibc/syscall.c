/*
How to make a system call from C.

# syscall

        man syscall

    Function used to make direct system calls from C.

    Takes the syscall number followed by a variable number of arguments:

        syscall(number, arg1, arg2, ...)

    This function is not a bare system call only on what concerns error handling:
    the same processing that is done for the POSIX library is done in case of error,
    with error returns always `-1` and `errno` being set accordingly.

    This function automatically puts RAM variables into registers before calling the system call,
    and gets the return value from `eax` into RAM.

    It is however an exact system call when there is no error situation. For example,
    syscall getpriority returns values between 0 and 39, while the POSIX version
    can always return negative values.

    where the arguments are the arguments of the system call

    Don't use bare system call numbers since those vary between architectures.
    In this way, if you use a syscall that is available to all archs your code is arch portable.

    Most system calls are defined on most architectures and have names which map
    to the actual number, depending on the architecture. This is done with the
    `__NR_XXX` constants in `asm/unistd.h` or SYS_<NAME> in `sys/types`

    TODO return value type is long int?

# __NR_XXX macros

    Are defined in the Linux kernel directly.

# SYS_ macros

    Are defined in terms of `__NR_` for compatibility.

    TODO: what is the difference between `asm/unistd.h __NR_X` and `sys/types SYS_NAME`?
    which is better in which situations?

# _syscall macro

    Deprecated method to do direct system calls. Don't use it.

#TODO

    TODO how to get the system call constants such as PRIO_PROCESS without going into POSIX libs?
    is this exactly how those are exposed? Or is there a way that does not require POSIX headers?
*/

#include "common.h"

int main(void) {
#ifdef __linux__
    puts("__linux__");

    /*
    Basic usage without extra arguments.
    */
    {
        assert(syscall(__NR_getpid)  == getpid());
        assert(syscall(__NR_getppid) == getppid());
    }

    /*
    With arguments
    */
    {
        syscall(__NR_exit, 0);
    }
#endif
}
