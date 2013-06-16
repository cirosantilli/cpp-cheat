/*
signals are a simple way for processes to communicate

signals are limited to passing a single byte between two processes

what almost each signal does is all predefined by ansi c
or specific operating systems

# example: control c

an example most linux people have used directly already:
hit ctrl+c in a terminal and this will send an INT signal
to the running process.

Unless the process implements a handler for this process,
this has the effect of destroying the process,
which is what happens by default for most, but not all signals.

# sources

- http://www.alexonlinux.com/signal-handling-in-linux
- http://www.kernel.org/doc/man-pages/online/pages/man7/signal.7.html

# ansi c

there is a small C ANSI signal interface,
and individual operating systems may implement many more
which is the case for linux

6 signals defined:

- SIGINT:  (Interrupt) Ask the process to terminate, possibly nicely. Sample cause: bash ctrl+c.
- SIGABRT: (Abort) Abnormal termination, such as is initiated by the abort function.
- SIGFPE:  (Floating-Point Exception) Erroneous arithmetic operation, such as zero divide or an operation resulting in overflow (not necessarily with a floating-point operation).
- SIGILL:  (Illegal Instruction) Invalid function image, such as an illegal instruction. This is generally due to a corruption in the code or to an attempt to execute data.
- SIGSEGV: (Segmentation Violation) Invalid access to storage: When a program tries to read or write outside the memory it has allocated.
- SIGTERM: (Terminate) Termination request sent to program. Major cause: shutdown, window close.

functions defined (handlers):

- SIG_DFL Default handling: The signal is handled by the default action for that particular signal.
- SIG_IGN Ignore Signal: The signal is ignored.
- SIG_ERR Special return value indicating failure.
*/

#include <stdio.h>
#include <signal.h>

#ifdef POSIX

/*
many more signals are defined in by posix and made available in unistd

simple easy to understand list:

- SIGKILL

    kills program immeiatelly

    contrary to `SIGINT`, programs cannot handle those signals
    and try to finish off nicely: the program finishes immediatelly.

- SIGSTOP

    freezes program. ctrl+z.

    programs cannot handle this signal, it always freezes the process immediatelly

- SIGHUP

    controlling terminal was killed

    this is why killing the terminal kills the process by default

- SIGPIPE

    process write to a pipe with no readers on other side

- SIGCHLD

    child terminated

- SIGALRM

    received after the alarm call after given no of secs

- SIGUSR1 and SIGUSR2: left to users to do whatever they want with
*/

#include <unistd.h>
#endif

void signal_handler(int sig)
{
    //sig arg allows us to use a single function for several different signals
    printf("sig: %d\n", sig);
    (void) signal(SIGINT, SIG_DFL);
      //reassign SIGINT to SIG_DFL handler which takes the default action for the signal
      //each process has a default action
      //in linux, the default actions are:
        //Term   Default action is to terminate the process.
        //Ign    Default action is to ignore the signal.
        //Core   Default action is to terminate the process and dump core (see core(5)).
        //Stop   Default action is to stop the process.
        //Cont   Default action is to continue the process if it is currently stopped.
      //the most common being Term
}


int main()
{
    (void) signal(SIGINT, signal_handler);
    (void) signal(SIGTERM, signal_handler);
        //registers signal_handler as handler for SIGINT and SIGTERM

    while(1)
    {
        puts("a");
#ifdef POSIX
        sleep(1);
#endif
    }
}
