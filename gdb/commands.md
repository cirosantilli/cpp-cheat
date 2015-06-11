# Commands

Commands you can run from inside GDB

## h

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

## running

### q

### Ctrl + D

Quit:

    q

If a programs is currently being debugged, it gets killed. To prevent that, first use `detach`.

### file

Set the file to run.

    file a.out

Same as the first argument passed on the command line:

    gdb a.out

### r

### run

Start running the program set by `file` or from the command line:

    r

If already running, kill and rerun. Keeps breakpoints, etc.

Start running with arguments. Next `r` calls will reuse those argument:

    r 1 2

The program will run until it reaches:

-   the regular end

-   a breakpoint

-   a signal like on a segmentation fault:

    You could see something like:

        Program received signal SIGSEGV, Segmentation fault.
        0x0000000000401d5b in quick_sort<int> (input=...) at quick.cpp:33
        33              if (input[right] < input[pivot]) {

    which says that it happened at line 33 of file `quick.cpp`.

### set args

Set command line arguments and stdin:

    set args arg0 arg1 <stdin.txt
    run

Remove previously set arguments:

    set args

Arguments can also be set with `--args` at invocation time.

But there seems to be no invocation time way to set stdin except `-ex 'set-args'`:

<http://stackoverflow.com/questions/455544/how-to-load-program-reading-stdin-and-taking-parameters-in-gdb>

#### Break immediately after run

TODO

I could only break at the first line of main, but that is not the first thing to be executed.

Is it possible to break at the very first instruction that GDB executes?

<http://stackoverflow.com/questions/7808769/how-to-debug-a-crash-before-main>

### k

Kill program:

    k

Keeps breakpoints, etc. saved for next debug session.

### generate-core-file

Dump the core:

    generate-core-file

The core contains the entire program state, including RAM memory and CPU registers, and you can just start from that point with GDB whenever you want.

A glibc hello world core is 2M large.

You can later restart from that point with:

    gdb executable.out core.1234

## Movement

### c

### Continue

Continue running from current location until:

- breakpoint
- Ctrl + C, e.g. if you are in an infinite loop

### s

### Step into

Step into.

Run current line and go to next.

If function call, go into the first line of the function.

    s

### n

### Step over

Next.

Run current line and go to next.

If function call, run the entire function now.

### fin

Go to the return of the current function.

### si

### stepi

Step one assembly instruction instead of code line.

The code line gets printed every time.

Show the instruction instead: <http://stackoverflow.com/questions/1902901/show-current-instruction-in-gdb>

### ni

### nexti

Like `si` by for `next`.

### Step over

## Breakpoints

Show breakpoints:

    i b

### b

### break

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

### dis

### disable

Disable breakpoint `1`:

    dis 1

`1` can be gotten from `i b`.

### en

Enable breakpoint 1:

    en 1

`1` is gotten from `i b`.

### d

### delete

Delete all breakpoints:

    d

Delete breakpoint `1`:

    d 1

### cl

### clear

Delete breakpoint at line 10:

    cl 10
    cl file.c:10

Delete all breakpoints in the given function:

    cl func
    cl file.c:func

## Information

## Status

Get information about the running process.

### l

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

#### List current function without typing its name

<http://stackoverflow.com/questions/16734783/in-gdb-i-can-call-some-class-functions-but-others-cannot-be-resolved-why>

### whe

Sample output:

    #0  0x0000000000401d5b in quick_sort<int> (input=...) at quick.cpp:33
    #1  0x00000000004016d7 in main (argc=2, argv=0x7fffffffd768) at quick.cpp:49

So here we see that:

- function `main` called function `quick_sort` at line 49
- function `main` called function `quick_sort` at line 49

TODO understand everything

### bt

### backtrace

Show all current frames, i.e. the current function calls.

### f

### frame

Select and print a stack frame:

    f

Sample output:

    #0  f0 (i=3) at nested.c:8
    8           return i + 1;

Interpretation:

- `0`: we are on the deepest frame
- `f0`: function name
- `i = 3`: argument `i` equals `3` on this call
- `nested.c:8` filename and line
- `return i + 1;`: line content

Show a given frame number:

    f 1

The frame number can be retrieved from `backtrace`.

`1` is the first caller function, `2` the next one, and so on.

Once you change the frame, it is as if you have moved to that point:

- local variables and arguments with `i locals` and `i args` will be those at that given frame
- `l` will list the code around that point

and so on.

### down

### up

Move a stack frame up or down and print it.

### i

### info

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

### p

### print

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

### pt

Print type of variable `x`:

    pt x

Sample output:

    type = double

### printf

Like the C function.

Useful for batch mode scripts that automatically check executables.

    printf "rax = %d\n", $rax

### disas

### disassemble

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

### x

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

## set

Configure GDB.

### layout

Enter very useful curses split windows views:

    layout src
    layout asm
    layout register

From the command line with the `-tui` option.

Close it:

- <http://stackoverflow.com/questions/8409540/how-to-close-layout-src-windows-in-gdb>
- <http://stackoverflow.com/questions/8953720/multiple-problems-with-gdbs-tui-mode>
