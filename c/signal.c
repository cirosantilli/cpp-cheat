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

# ansi c

there is a small C ANSI signal interface,
and individual operating systems may implement many more
which is the case for linux

6 signals defined:

- SIGABRT: (Abort) Abnormal termination, such as is initiated by the abort function.
- SIGFPE:  (Floating-Point Exception) Erroneous arithmetic operation, such as zero divide or an operation resulting in overflow (not necessarily with a floating-point operation).
- SIGILL:  (Illegal Instruction) Invalid function image, such as an illegal instruction. This is generally due to a corruption in the code or to an attempt to execute data.
- SIGSEGV: (Segmentation Violation) Invalid access to storage: When a program tries to read or write outside the memory it has allocated.
- SIGINT:  (Interrupt) Ask the process to terminate, possibly nicely. Sample cause: bash ctrl+c.
- SIGTERM: (Terminate) Termination request sent to program. Major cause: shutdown, window close.

functions defined (handlers):

- SIG_DFL Default handling: The signal is handled by the default action for that particular signal.
- SIG_IGN Ignore Signal: The signal is ignored.
- SIG_ERR Special return value indicating failure.

# sources

- <http://www.alexonlinux.com/signal-handling-in-linux>

    good intro, covers lots of POSIX / linux specific stuff,
    but also has nice examples that help understand the ANSI C model.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler( int sig )
{
    //sig arg allows us to use a single function for several different signals:
    //just look at it and decide which action to take based on the signal number

        printf( "sig: %d\n", sig );

    //after the signal is dealt with, the handler is then changed to its default action
    //if you want to continue using this handler for future signals, you have to reregister
    //it here: TODO confirm. If I remove this it does not work.

        signal( sig, signal_handler );

    //you can change the action handler at any time
    //for example, if you uncomment this line, only the first signal will be ignored
    //and but the second will be dealt with the default action:

        //(void) signal( sig, SIG_DFL );
}

int main()
{
    /*
        registers signal_handler as handler for SIGINT and SIGTERM:

        you can get a SIGINT on terminals via C-C on linux or C-Z on windows
        while the program runs on the foreground:

        you can get a SIGTERM by

        - opening a new termianal (ex: `xterm` on linux)
        - running this program on that terminal

        from the current terminal, and then closing the first terminal.
    */

        signal( SIGINT, signal_handler );
        signal( SIGTERM, signal_handler );

    int i = 0;
    while ( i < 10 )
    {
        printf( "%d\n", i );
        i++;

        /*
        TODO how to wait here for say 1 sec, so that user can try signals out?
        there is no simple ANSI way of doing that...

        on posix we would:
        */

            //sleep( 1 );
    }

    //TODO why does this not work:

        //puts( "press any key to exit" );
        //getchar();

    //if the user enters a C-C, the program exits

    //try with fgets

    return EXIT_SUCCESS;
}
