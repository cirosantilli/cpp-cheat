/*
# ptrace

    Control a child process. You can observe anything in it's state,
    including memory and registers.

    The child stops transfers control to parent on the following events:

    - signals are raised
    - `PTRACE_SYSCALL` is used and a system call is reached. Yes, `strace` is "easy" to write.
    - `PTRACE_SINGLESTEP` does a single instruction and then stops. So this is how GDB does it.

    Bibliograpy:

    - https://github.com/nelhage/ministrace/blob/for-blog/ministrace.c
*/

#include "common.h"

#ifdef __x86_64__
#define REGRAX(regs) (intmax_t)regs.rax
#define REGRIP(regs) (intmax_t)regs.rip
#elif defined __i386__
#define REGRAX(regs) (intmax_t)regs.eax
#define REGRIP(regs) (intmax_t)regs.eip
#endif

int main() {

    pid_t child_pid;
    int i;
    struct user_regs_struct regs;
    int status;

    child_pid = fork();
    if (child_pid == 0) {
        /*
        Says that this child can be traced now.

        Alternatives inclue using PTRACE_ATTACH or PTRACE_SEIZE from the parent.
        */
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);

        /* We must stop ourselves, or else the child might just run first and finish before the parent. */
        kill(getpid(), SIGSTOP);

        /* Not puts because it is cached. */
        write(1, "child0\n", 7);
        write(1, "child1\n", 7);
        exit(EXIT_SUCCESS);
    }

    ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);

    /*
    This loop goes over: kill (one stop), 2x write (2 stops each).

    kill stops because of the signal it raises. Stops signals happen only once.

    Writes stop because of `PTRACE_SYSCALL`.

    `exit()` calls `sys_exit_group` (x86_64 231) on Ubuntu 14.04,
    not `sys_exit`, to deal with multithreading.
    */
    for (i = 0; i < 7; i++) {
        /*
        Stops both when the system call enters and leaves!

        The main thing to get out of the exiting syscall is the return value in rax.
        */
        ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
        waitpid(child_pid, &status, 0);
        ptrace(PTRACE_GETREGS, child_pid, NULL, &regs);
        /*
        TODO What is the -38 at exit?
        http://stackoverflow.com/questions/7514837/why-this-ptrace-programe-always-saying-syscall-returned-38?lq=1
        */
        puts("GETREGS");
        printf("  rax =   %jd\n", REGRAX(regs));
        printf("  rip = 0x%jx\n", REGRIP(regs));

        puts("PEEKUSER");
        printf(
            "  ORIG_RAX = %jd\n",
            ptrace(PTRACE_PEEKUSER, child_pid, sizeof(long)*ORIG_RAX)
        );
        printf(
            "  RAX = %jd\n",
            ptrace(PTRACE_PEEKUSER, child_pid, sizeof(long)*RAX)
        );

        /* Print one word from the virtual memory of the tracee. */
        printf(
            "PEEKTEXT rip = 0x%jx\n",
            ptrace(PTRACE_PEEKTEXT, child_pid, REGRIP(regs), NULL)
        );

        /* With PTRACE_O_TRACESYSGOOD this can be used to distinguish between TODO */
        if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
            puts("PTRACE_O_TRACESYSGOOD");

        fflush(stdout);
        if (i == 6) {
            assert(WIFEXITED(status));
            assert(!WIFSTOPPED(status));
        } else {
            assert(!WIFEXITED(status));
            assert(WIFSTOPPED(status));
        }
        puts("");
    }

    return EXIT_SUCCESS;
}
