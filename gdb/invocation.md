# Invocation

## Debug information

GDB can use optional debugging contained in executables to debug them.

This helps greatly, as it allows GDB to match information that is lost at compilation time with the source code, e.g.:

- what source line am I at?
- what is the name of the local variables (normally compiled just as stack offsets)

You must tell your compiler to generate debug information: it is turned off by default and not included in package managers, as it increases executable size.

For `gcc`:

    gcc -ggdb3 a.c

It is also possible to debug without debugging information, but it is much harder. In particular, you will have to rely much more on assembly level debugging, and reverse engineering the functions of variables without their name.

There are a few standards for debugging information format:

- DWARF, dominates Linux.
- <https://en.wikipedia.org/wiki/Stabs>, dominated `a.out`, but now dead.
- COFF: <https://en.wikipedia.org/wiki/COFF>, dominates Windows.
- XCOFF: <https://en.wikipedia.org/wiki/XCOFF>, dominates AIX.

### libc debugging symbols

In Ubuntu 14.04, the libc does not come with debugging symbols, so you cannot for example get any information out of `l` if you enter one of those functions.

How to install one: <http://stackoverflow.com/questions/10000335/how-to-use-debug-version-of-libc>

You can still to assembly level operations of course.

## Configuration files

### .gdbinit

GDB script run at startup.

Hardcore things can be done with it: <https://github.com/gdbinit/Gdbinit>

## Basic usage

Start GDB with a given executable:

    gdb a.out

Same as using the `file` command from inside GDB.

You then have to start running the program with a command like `run` or `start`.

## Attach

Attach a running process with given process ID:

    a.out &
    gdb a.out $!

This pauses the process by default. The solution seems to be `-ex cont` <http://stackoverflow.com/questions/9746018/gdb-attach-to-a-process-without-stop>:

## p

Allows to attach to a PID without the executable:

    a.out &
    gdb -p $!

Can also be achieved with the `attach` command.

Attach with PID but without executable: <http://stackoverflow.com/questions/9974254/gdb-attaching-to-a-process-where-executable-is-deleted>

TODO: do we lose anything by not passing the executable along? Maybe not because of the `/proc/<pid>/exe` symlink which allows a process to find the path to it's executable.

## batch

Only run `-x` and `-ex` commands and exit immediately when the program finishes or a breakpoint is reached.

Sample application: disassemble a single function: <http://stackoverflow.com/questions/22769246/disassemble-one-function-using-objdump>

    gdb -batch -ex 'disassemble main' -ex 'run' main.out

## ex

Run given command from string:

    gdb -ex 'break main' -ex 'run'

Must pass as single command per `-ex` argument.

## x

Run commands in the given file.

TODO: file.gdb:

    watch i
    commands
      continue
    end

with `gdb -x file.gdb -ex run main.out` stops at the first watch point, then I `c` and it does not stop anymore.

But:

    watch i
    commands
      continue
    end
    run

with: `gdb -x file.gdb main.out` does not stop as expected. What is the difference?

## args

You can also pass command line arguments at invocation time with:

    gdb --args executable arg0 arg1

## tui

Start debugging in `tui` mode.

Same as the `layout src` command.

## Core files

For the program to generate the core file do:

    ulimit -c unlimited
    ./a.out

This generates a `core` file. Now:

    gcc ./a.out core

will put you in the state just before what created the core, often a segfault.

But if the error is easily reproducible, you can just run:

    gcc ./a.out

and `run` inside GCC. It will also stop at the segfault, without the need to generate and load core files.
