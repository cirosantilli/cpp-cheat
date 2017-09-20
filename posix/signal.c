/*
ANSI C also specifies signal, here are the POSIX extensions.

POSIX recommends `sigaction` instead of `signal`.

To send arbitrary signals to a process from a terminal, consider using the `kill` utility
(it does more than killing via a SIGTERM, as in general it sends any signal to a process)

Also consider the convenient non POSIX stadardized VT100 control characters such as `<C-C>`
which generate certain signals such as `SIGTERM`.

# ANSI signals

    ANSI C supports the concept of signals, and only POSIX specific features shall be discussed here.

    Please look for ANSI C info for any feature used but not explained here.

    Linux extends POSIX by adding new signals, Those shall not be discussed here.

# POSIX signals

    Docs here: http://pubs.opengroup.org/onlinepubs/009696699/basedefs/signal.h.html

    POSIX defines several signals in addition to the ANSI C signals.

    As in ANSI C, each signal has the following attributes:

    -   general description of which conditions generate the signal

    -   the signal can or cannot be handled.

        Most signals can be handled, but there are a few exceptions such as:

        - `SIGKILL`: always kill processes, cannot be handled.
        - `SIGKSTOP` and `SIGCONT`

    -   default action to take

        For signals that can be handled, you can change those behavious by creating your own handlers.

        The possible default behaviours are:

        -   T:

            Abnormal termination of the process.

            The process is terminated with all the consequences of `_exit()` except that the status made available to
            `wait()` and `waitpid()` indicates abnormal termination by the specified signal.

            Default action for most signals.

        -   A :Abnormal termination of the process.

            [XSI] [Option Start] Additionally, implementation-defined abnormal termination actions,
            such as creation of a core file, may occur. [Option End]

            Linux implements concept of core dumps on those cases.
            Note however that those may be turned on or off depending on the system configuration.

        -   I: Ignore the signal.

            An important example is `SIGCHLD`, which is generated when a child terminates,
            but has no effect by default, since in general killing the parent is not what
            should happen on most programs.

        -   S: Stop the process.

            Mainly `SIGSTOP`.

        -   C: Continue the process, if it is stopped; otherwise, ignore the signal.

            Mainly `SIGCONT`.

    POSIX specific signals include:

    # SIGKILL

        Kills program.

        Cannot be handled unlike to `SIGINT` and `SIGTERM`.

    # SIGQUIT

        Quit program.

        Used in case of abnormal termination (`A`), unlike `SIGINT` and `SIGTERM` which happen on normal temrination.

        May generate a core dump https://en.wikipedia.org/wiki/Core_dump depending on system configurations.

        On Ubuntu, coredumps are disabled by default. You can enable them for the current session with:

            ulimit -c unlimited

        on the terminal where you will run the command to enable core dumps.

        The setting can be permanently changed on the `/etc/security/limits.conf` file.

        The core file is binary. To interpret it you must have compiled the program with debugging
        information and then use GDB on the core file and the executable as:

            gcc -g -o myfile myfile.c
            gdb myfile core

    # SIGSTOP

        Freezes program.

        `ctrl+z`, in linux terminals.

        Cannot be handle.

    # SIGCONT

        Continues a process that

    # SIGHUP

        Controlling terminal was killed.

        This is why killing the terminal kills most process by default unless those process implement a handler.

    # SIGPIPE

        Process write to a pipe with no readers on other side

    # SIGCHLD

        Child terminated, stopped or continued.

        Ignored by default.

    # SIGALRM

        Received after the alarm call after given no of secs.

    # SIGUSR1

    # SIGUSR2

        Left to users to do whatever they want with. Default to `term`.

    # Parent death signal

        In POSIX, no signal needs to be sent to the child if the parent exits:
        http://stackoverflow.com/questions/284325/how-to-make-child-process-die-after-parent-exits
        In Linux, this can be achieved via the `prctl` syscall.
        This may seem surprising considering that:

        -   parents can wait for children

        -   children get a NOHUP when controling process is killed
            This is mentioned at: http://pubs.opengroup.org/onlinepubs/009695399/functions/exit.html

            TODO what is a controlling process?

    # Bibliography

        -   `man 7 signal`

        -   http://www.alexonlinux.com/signal-handling-in-linux

            good intro
*/

#include "common.h"

volatile sig_atomic_t i = 0;

void signal_handler(int sig) {
	i = 1;
	signal(sig, signal_handler);
}

int main(void) {
    signal(SIGALRM, signal_handler);
    /*
    # Send signal

    # kill

        This is done via the kill function:

            int kill(pid_t pid, int sig);
    */
	{
        assert(kill(getpid(), SIGALRM) == 0);
    }
    assert(i == 1);
    return EXIT_SUCCESS;
}
