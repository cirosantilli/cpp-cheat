# GDB

GNU debugger.

1. [Invocation](invocation.md)
1. [Commands](commands.md)
1.  Examples
    1. [nested.c](nested.c)
    1. [count_infinite.c](count_infinite.c)
    1. [big_function.c](big_function.c)
    1. [C++ function overload](overload.cpp)
    1. [Segmentation Fault](segv.c)

<https://sourceware.org/gdb/onlinedocs/gdb/>

Allows you to advance through programs one line or assembly instruction at a time, and find out the exact state at any point.

## Alternatives

GDB with the default configuration is not a convenient font-end if you are going to do a lot debugging.

Instead, use either of:

- `-tui` option
- IDE front-ends
- <https://github.com/cgdb/cgdb> ncurses

## GUI configuration

### tui

Convenient mode, which shows which line of the code you are at.

Can also be entered through:

- the `layout tui` command
- `Ctrl-x` keyboard shortcuts: TODO get them working

### Colors

<http://stackoverflow.com/questions/209534/how-to-highlight-and-color-gdb-output-during-interactive-debugging>

Can be achieved with options.

### .gdbinit

Run at startup.

Hardcore things can be done with this: <https://github.com/gdbinit/Gdbinit>

## Step backwards in time

## Omniscient debugging

Considered a "high priority project" by the FSF as of January 2015 <http://www.fsf.org/campaigns/priority-projects/reversible-debugging-in-gdb>

## Assembly level debugging

GDB works better by default for C level operations, but you can also use it to debug assembly directly.

The following are useful:

- `disassemble`
- `stepi`
- `nexti`
- `layout asm`
- <http://stackoverflow.com/questions/1902901/show-current-instruction-in-gdb>
- <http://stackoverflow.com/questions/589653/switching-to-assembly-in-gdb>

### Break at instruction with given opcode

http://stackoverflow.com/questions/14031930/break-on-instruction-with-specififc-opcode-in-gdb

## libc source

## Stdlib source

In Ubuntu 14.04, the libc does not come with debugging symbols, so you cannot for example get any information out of `l` if you enter one of those functions.

How to install one: <http://stackoverflow.com/questions/10000335/how-to-use-debug-version-of-libc>

You can still to assembly level operations of course, like `disassemble`, `si` or `fin`.

## Internals

Hardware vs software breakpoints: <http://stackoverflow.com/questions/8878716/what-is-the-difference-between-hardware-and-software-breakpoints> x86 has 4 registers which can raise an exception is the PC points to the instruction stored in them. GDB can then deal with the exception and take over.
