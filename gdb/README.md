# GDB

GNU debugger.

<https://sourceware.org/gdb/onlinedocs/gdb/>

Allows you to advance through programs one line or assembly instruction at a time, and find out the exact state at any point.

## Debug information

GDB can use optional debugging contained in executables to debug them.

This helps greatly, as it allows GDB to match information that is lost at compilation time with the source code, e.g.:

- what source line am I at?
- what is the name of the local variables (normally compiled just as stack offsets)

You must tell your compiler to generate debug information: it is turned off by default and not included in package managers, as it increases executable size.

For `gcc`:

    gcc -ggdb3 a.c

It is also possible to debug without debugging information, but it is much harder. In particular, you will have to rely much more on assembly level debugging, and reverse engineering the functions of variables without their name.

There are a few standards for debugging information format. DWARF is the most popular on ELF.

---

Run executable and debug it with GDB:

    gdb a.out

Attach to a running instance of `a.out` after it was started:

    gdb -p "$pid"

the process stops at the instruction it was executing at the time.

This can also be achieved with the `attach` command.

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

- the `layout` command
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

## libc source

## Stdlib source

In Ubuntu 14.04, the libc does not come with debugging symbols, so you cannot for example get any information out of `l` if you enter one of those functions.

How to install one: <http://stackoverflow.com/questions/10000335/how-to-use-debug-version-of-libc>

You can still to assembly level operations of course, like `disassemble`, `si` or `fin`.

## Commands

Commands you can run from inside GDB

### h

Show command categories:

    h

Sample output:

    aliases -- Aliases of other commands
    breakpoints -- Making program stop at certain points
    data -- Examining data
    files -- Specifying and examining files
    internals -- Maintenance commands
    obscure -- Obscure features
    running -- Running the program
    stack -- Examining the stack
    status -- Status inquiries
    support -- Support facilities
    tracepoints -- Tracing of program execution without stopping the program
    user-defined -- User-defined commands

To view the actual commands, use:

    h aliases

Then to get help on an specific command:

    h break

### running

#### q

#### Ctrl + D

Quit:

    q

If a programs is currently being debugged, it gets killed. To prevent that, first use `detach`.

#### file

Set the file to run.

    file a.out

Same as the first argument passed on the command line:

    gdb a.out

#### r

#### run

Start running the program set by `file` or from the command line:

    r

If already running, kill and rerun. Keeps breakpoints, etc.

Start running with arguments. Next `r` calls will reuse those argument:

    r 1 2

Remove previously set arguments:

    set args

You can also pass command line arguments at invocation time with:

    gdb --args executable arg0 arg1

The program will run until it reaches:

-   the regular end

-   a breakpoint

-   a signal like on a segmentation fault:

    You could see something like:

        Program received signal SIGSEGV, Segmentation fault.
        0x0000000000401d5b in quick_sort<int> (input=...) at quick.cpp:33
        33              if (input[right] < input[pivot]) {

    which says that it happened at line 33 of file `quick.cpp`.

##### Break immediately after run

TODO

I could only break at the first line of main, but that is not the first thing to be executed.

Is it possible to break at the very first instruction that GDB executes?

<http://stackoverflow.com/questions/7808769/how-to-debug-a-crash-before-main>

#### k

Kill program:

    k

Keeps breakpoints, etc. saved for next debug session.

#### generate-core-file

Dump the core:

    generate-core-file

The core contains the entire program state, including RAM memory and CPU registers, and you can just start from that point with GDB whenever you want.

A glibc hello world core is 2M large.

You can later restart from that point with:

    gdb executable.out core.1234

### Movement

#### c

#### Continue

Continue running from current location until:

- breakpoint
- Ctrl + C, e.g. if you are in an infinite loop

#### s

#### Step into

Step into.

Run current line and go to next.

If function call, go into the first line of the function.

    s

#### n

#### Step over

Next.

Run current line and go to next.

If function call, run the entire function now.

#### fin

Go to the return of the current function.

#### si

#### stepi

Step one assembly instruction instead of code line.

The code line gets printed every time.

Show the instruction instead: <http://stackoverflow.com/questions/1902901/show-current-instruction-in-gdb>

#### ni

#### nexti

Like `si` by for `next`.

#### Step over

### Breakpoints

Show breakpoints:

    i b

#### b

#### break

Set breakpoint.

    b 10

    b func

    b c.c:10

    b c.c:func

Two lines after and before the current line:

    b +2
    b -2

Set breakpoint at address:

    b *0x400440

#### dis

#### disable

Disable breakpoint `1`:

    dis 1

`1` can be gotten from `i b`.

#### en

Enable breakpoint 1:

    en 1

`1` is gotten from `i b`.

#### d

#### delete

Delete all breakpoints:

    d

Delete breakpoint `1`:

    d 1

#### cl

#### clear

Delete breakpoint at line 10:

    cl 10
    cl file.c:10

Delete all breakpoints in the given function:

    cl func
    cl file.c:func

### Information

### Status

Get information about the running process.

#### l

List 10 lines of code around the current line:

    l

Sample output if we are on line 33:

    28          std::tie(left_begin, pivot) = recursion_stack.back();
    29          recursion_stack.pop_back();
    30          left = left_begin;
    31          right = left;
    32          while (right < pivot) {
    33              if (input[right] < input[pivot]) {
    34                  std::swap(input[left], input[right]);
    35                  left++;
    36              }
    37              right++;

If you hit `l` again, it will list 10 more lines, from 38 to 47.

List 10 previous from last listed:

    l -

List 10 lines around line 20:

    l 20

Line ranges:

    l 5,20
    l ,20
    l 5,

List entire functions and files:

    l func
    l c.c
    l c.c:12
    l c.c:func

Change the default list size:

    set listsize 5

#### whe

Sample output:

    #0  0x0000000000401d5b in quick_sort<int> (input=...) at quick.cpp:33
    #1  0x00000000004016d7 in main (argc=2, argv=0x7fffffffd768) at quick.cpp:49

So here we see that:

- function `main` called function `quick_sort` at line 49
- function `main` called function `quick_sort` at line 49

TODO understand everything

#### bt

#### backtrace

Show all current frames, i.e. the current function calls:

#### f

#### frame

TODO examples

Show current frame number:

    f

Go to frame 1:

    f 1

The frame number can be retrieved from `backtrace`.

Once you change the frame, it is as if you have moved to that point:

- local variables will be those at that point
- `l` will list the code around that point

and so on.

#### down

#### up

Move a stack frame up or down and print it.

#### i

#### info

Breakpoints:

    i b

Most common CPU registers:

    i r

All CPU registers, including stuff like YMM:

    i al

Single CPU register:

    i r rax

Sample output:

    rax            0x40057d 4195709

`0x40057d` equals `4195709` in hex.

Global and static variable names:

    i variables

a minimal glibc hello world has lots of them, so it is not very useful. Filter by regular expression:

    i variables a.c

Current function arguments:

    i args

Local variables and values:

    i locals

Information about the process being debugged:

    i proc
    i program

Memory segments: <http://stackoverflow.com/questions/5691193/gdb-listing-all-mapped-memory-regions-for-a-crashed-process>

    i proc mappings
    i proc files

#### p

#### print

Print value of variable x in current frame:

    p x
    p x+1
    p x*2
    p func(1)
    p array

Print 3 values of array, starting at the 5th element:

    p array[3]@5

Set print format:

    (gdb) p mychar    #default
    $33 = 65 'A'
    (gdb) p /o mychar #octal
    $34 = 0101
    (gdb) p /x mychar #hex
    $35 = 0x41
    (gdb) p /d mychar
    $36 = 65
    (gdb) p /u mychar #unsigned decimal
    $37 = 65
    (gdb) p /t mychar #binary
    $38 = 1000001
    (gdb) p /f mychar #float
    $39 = 65
    (gdb) p /a mychar
    $40 = 0x41

#### pt

Print type of variable `x`:

    pt x

Sample output:

    type = double

#### printf

Like the C function.

Useful for batch mode scripts that automatically check executables.

    printf "rax = %d\n", $rax

#### disas

#### disassemble

Print disassembly of the current function:

    disas

Sample output:

    Dump of assembler code for function main:
       0x000000000040052d <+0>:     push   %rbp
       0x000000000040052e <+1>:     mov    %rsp,%rbp
       0x0000000000400531 <+4>:     push   %rbx
       0x0000000000400532 <+5>:     sub    $0x18,%rsp
       0x0000000000400536 <+9>:     movl   $0x0,-0x14(%rbp)
    => 0x000000000040053d <+16>:    addl   $0x1,-0x14(%rbp)
       0x0000000000400541 <+20>:    mov    $0x5f5e100,%ecx
       0x0000000000400546 <+25>:    mov    -0x14(%rbp),%eax
       0x0000000000400549 <+28>:    cltd
       0x000000000040054a <+29>:    idiv   %ecx
       0x000000000040054c <+31>:    mov    %edx,%eax
       0x000000000040054e <+33>:    test   %eax,%eax
       0x0000000000400550 <+35>:    jne    0x400570 <main+67>
       0x0000000000400552 <+37>:    mov    $0x5f5e100,%ebx
       0x0000000000400557 <+42>:    mov    -0x14(%rbp),%eax
       0x000000000040055a <+45>:    cltd
       0x000000000040055b <+46>:    idiv   %ebx
       0x000000000040055d <+48>:    mov    %eax,%esi
       0x000000000040055f <+50>:    mov    $0x400608,%edi
       0x0000000000400564 <+55>:    mov    $0x0,%eax
       0x0000000000400569 <+60>:    callq  0x400410 <printf@plt>
       0x000000000040056e <+65>:    jmp    0x40053d <main+16>
       0x0000000000400570 <+67>:    jmp    0x40053d <main+16>

Also print line source code interleaved:

    disas/m

Sample output:

    Dump of assembler code for function main:
    5       int main() {
       0x000000000040052d <+0>:     push   %rbp
       0x000000000040052e <+1>:     mov    %rsp,%rbp
       0x0000000000400531 <+4>:     push   %rbx
       0x0000000000400532 <+5>:     sub    $0x18,%rsp

    6           int i = 0;
       0x0000000000400536 <+9>:     movl   $0x0,-0x14(%rbp)

    7           while (1) {
    8               i++;
    => 0x000000000040053d <+16>:    addl   $0x1,-0x14(%rbp)

    9               if (i % PERIOD == 0)
       0x0000000000400541 <+20>:    mov    $0x5f5e100,%ecx
       0x0000000000400546 <+25>:    mov    -0x14(%rbp),%eax
       0x0000000000400549 <+28>:    cltd
       0x000000000040054a <+29>:    idiv   %ecx
       0x000000000040054c <+31>:    mov    %edx,%eax
       0x000000000040054e <+33>:    test   %eax,%eax
       0x0000000000400550 <+35>:    jne    0x400570 <main+67>

    10                  printf("%d\n", i / PERIOD);
       0x0000000000400552 <+37>:    mov    $0x5f5e100,%ebx
       0x0000000000400557 <+42>:    mov    -0x14(%rbp),%eax
       0x000000000040055a <+45>:    cltd
       0x000000000040055b <+46>:    idiv   %ebx
       0x000000000040055d <+48>:    mov    %eax,%esi
       0x000000000040055f <+50>:    mov    $0x400608,%edi
       0x0000000000400564 <+55>:    mov    $0x0,%eax
       0x0000000000400569 <+60>:    callq  0x400410 <printf@plt>

    11          }
       0x000000000040056e <+65>:    jmp    0x40053d <main+16>
       0x0000000000400570 <+67>:    jmp    0x40053d <main+16>

    End of assembler dump.

Current line once:

    display/i $pc

Current line every time the debugger stops:

    set disassemble-next-line on

#### x

Examine 4 bytes of memory:

    x 0x00000000004000b0

Sample output:

    0x4000b0 <_start>:  0x000001b8

where `_start` is a label that is there.

Examine 160 bytes:

    x/160xb 0x400000

Sample output:

    0x400000:   0x7f    0x45    0x4c    0x46    0x02    0x01    0x01    0x00
    0x400008:   0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
    0x400010:   0x02    0x00    0x3e    0x00    0x01    0x00    0x00    0x00
    0x400018:   0x40    0x04    0x40    0x00    0x00    0x00    0x00    0x00
    0x400020:   0x40    0x00    0x00    0x00    0x00    0x00    0x00    0x00
    0x400028:   0xf0    0x13    0x00    0x00    0x00    0x00    0x00    0x00
    0x400030:   0x00    0x00    0x00    0x00    0x40    0x00    0x38    0x00
    0x400038:   0x09    0x00    0x40    0x00    0x23    0x00    0x20    0x00
    0x400040:   0x06    0x00    0x00    0x00    0x05    0x00    0x00    0x00
    0x400048:   0x40    0x00    0x00    0x00    0x00    0x00    0x00    0x00
    0x400050:   0x40    0x00    0x40    0x00    0x00    0x00    0x00    0x00
    0x400058:   0x40    0x00    0x40    0x00    0x00    0x00    0x00    0x00
    0x400060:   0xf8    0x01    0x00    0x00    0x00    0x00    0x00    0x00
    0x400068:   0xf8    0x01    0x00    0x00    0x00    0x00    0x00    0x00
    0x400070:   0x08    0x00    0x00    0x00    0x00    0x00    0x00    0x00
    0x400078:   0x03    0x00    0x00    0x00    0x04    0x00    0x00    0x00
    0x400080:   0x38    0x02    0x00    0x00    0x00    0x00    0x00    0x00
    0x400088:   0x38    0x02    0x40    0x00    0x00    0x00    0x00    0x00
    0x400090:   0x38    0x02    0x40    0x00    0x00    0x00    0x00    0x00
    0x400098:   0x1c    0x00    0x00    0x00    0x00    0x00    0x00    0x0

### set

Configure GDB.

## Invocation

### batch

Only run `-x` and `-ex` commands and exit.

Sample application: disassemble a single function: <http://stackoverflow.com/questions/22769246/disassemble-one-function-using-objdump>

    gdb -batch -ex 'file function_int_int_int.out' -ex 'disassemble main'

### ex

Run given command from string.

### x

Run commands in the given file.
