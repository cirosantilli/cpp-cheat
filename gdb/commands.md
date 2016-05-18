# Commands

Commands you can run from inside GDB

## Empty line

If you hit enter without typing anything, it redoes the last command.

E.g.:

    step
    <enter>

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

Ignore program stdout and stderr: <http://stackoverflow.com/questions/2388561/block-output-of-debugged-program-gdb>:

    run >/dev/null

### start

Like run, but also add a temporary (deleted once hit) breakpoint at `main` and stop there.

`main` this is not the actual executable entry point, see also: <http://stackoverflow.com/questions/10483544/stopping-at-the-first-machine-code-instruction-in-gdb>

### q

### quit

Quit!

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

### continue

Continue running from current location until:

- breakpoint
- Ctrl + C, e.g. if you are in an infinite loop

### s

### step

Step into.

Run current line and go to next.

If function call, go into the first line of the function.

    s

### n

### next

### Step over

Next.

Run current line and go to next.

If function call, run the entire function now.

If there is no debugging information with attached source code, run until this function returns.

### fin

### finish

Go to the return of the current frame: function or loop.

Does not work on the top frame.

Stopping at the return is way harder: http://stackoverflow.com/questions/3649468/setting-breakpoint-in-gdb-where-the-function-returns

### si

### stepi

Step one assembly instruction instead of code line.

The source code line gets printed every time.

Show the instruction instead: <http://stackoverflow.com/questions/1902901/show-current-instruction-in-gdb>

If there is no debugging information with attached source code, run until another function is entered: usually either a function call or return.

Sample output if there are multiple instructions for the current line:

    0x0000000000400593	24	    printf("%d\n", f3(0));

Which contains the:

- address
- source line number
- source line

If there is no source code:

    0x0000000000400535 in main ()

If each instruction corresponds to a single line:

    9	    i += 1;

the address number is not shown.

### ni

### nexti

### Step over

Like `si` by for `next`.

Don't enter `call`.

Does enter `int` in 16-bit code. In that case, you can use instead: TODO <http://stackoverflow.com/questions/24491516/how-to-step-over-interrupt-calls-when-debugging-a-bootloader-bios-with-gdb-and-q> If only we could get the size of the current instruction automatically.

### until

Continue until given line or any following line of the same frame is reached, or if the frame returns.

TODO example.

TODO vs break + continue?

### advance

TODO vs until.

### skip

Prevent `step` from entering given functions: it is as if `next` had been used instead:

<http://stackoverflow.com/questions/1133365/preventing-gdb-from-stepping-into-a-function-or-file>

## Breakpoints

Show breakpoints:

    i b

### b

### break

Set breakpoint.

    # Line 10 of current file.
    b 10

    b func

    # Line 10 of given file.
    b c.c:10

    b c.c:func

Two lines after and before the current line:

    b +2
    b -2

Set breakpoint at address:

    b *0x400440

If you set a breakpoint in the middle of an instruction, segfault. E.g., supposing `0x400440` is 2 bytes long, then:

    b *0x400441
    c
    c

may segfault. TODO why?

`break function` does not break on the very first instruction of the function, but rather further after the prologue: <http://stackoverflow.com/questions/25545994/how-does-gdb-determine-function-entry-points> GDB guesses prologues even without debug information. TODO can debug information contain prologue information?

Break on nth line of function: <http://stackoverflow.com/questions/3013189/in-gdb-how-to-set-conditional-breakpoint-to-a-functions-3rd-line>

#### Dynamically loaded library breakpoints

When you do:

    break printf

before running the program, what happens depends on the value of:

    show breakpoint pending

which can be set with:

    set breakpoint pending on|off|auto

The default is auto, which is not `auto`, but rather asks for confirmation...

### Hardware breakpoints

### hbreak

Create a hardware breakpoint.

You should not use this unless you really need to, because x86 only has 4 hardware breakpoints, and software execution breakpoints are quite efficient.

So you should leave hardware breakpoints for watchpoints instead, for which the software implementation requires single stepping, which is very slow.

x86 hardware breakpoint description: <https://en.wikipedia.org/wiki/X86_debug_register> The `/proc/cpuid` flag is `de`.

### condition

https://sourceware.org/gdb/onlinedocs/gdb/Conditions.html

Make breakpoint number 2 only break if `a == 1`:

    condition 2 a == 1

For `break`, can also be specified with `if`:

    break 2 if a == 1

Which is much better as you don't need to specify the breakpoint number again.

Unfortunately `condition` must be used for certain commands, e.g. `catchpoint`, which does not support `if`.

It is necessary to specify the breakpoint explicitly, you cannot specify the last set breakpoint automatically...

### watch

### rwatch

### awatch

Break when variable is:

- `watch`: written
- `rwatch`: read
- `awatch`: written or read (all)

Uses hardware support by default, because the only way to software implement this is single stepping it.

Sample usage:

    watch var
    run

Watch a memory range: <http://stackoverflow.com/questions/11004374/watch-a-memory-range-in-gdb> x86 supports small watch ranges up to 8 bytes: <https://en.wikipedia.org/wiki/X86_debug_register>

Watch every member of a given structure type: <http://stackoverflow.com/questions/5557590/how-to-watch-a-member-of-a-struct-for-every-struct-variable-that-has-that-type>

#### watch local variable

<http://stackoverflow.com/questions/1354637/how-do-i-set-persistent-and-conditional-watchpoints-on-locally-scoped-variables>

Does not seem possible from outside of the function frame. And when it goes out of scope, the watch point is lost: <https://sourceware.org/gdb/onlinedocs/gdb/Set-Watchpoints.html>

The best solutions seems to be to script it.

### rbreak

Regexp break: set a breakpoint at all functions that match the given regular expression.

Break at all function calls:

    set confirm off
    rbreak .

If you do this after running `start`, it will add hundreds of breaks and take a noticeable amount (e.g. 30 seconds) of time for a hello world because of the dynamic library functions. If done before `start`, those will not be seen.

This will also pick up the execution of the loader which the kernel points to before `_start`: <http://stackoverflow.com/questions/31379422/why-is-init-from-glibcs-csu-init-first-c-called-before-start-even-if-start-i/31387656#31387656>

A file can be set to narrow down matches:

    rbreak a.c:.

Directories are not accepted: <http://stackoverflow.com/questions/29437138/can-gdb-set-break-at-every-function-inside-a-directory/31484890#31484890>

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

### commands

Run given commands whenever the last breakpoint or watchpoint is hit:

    break f
    commands
      printf "We entered f!"
      continue
    end

### dprintf

Sample usage:

    dprintf main,"hello\n"
    run

TODO. Vs `commands`? Faster? <http://stackoverflow.com/questions/31653903/what-is-the-difference-between-dprintf-vs-break-commands-continue>

### dis

### display

Print out given expression whenever the debugger stops.

This includes `n` and `s`.

Multiple `disp` are shown sequentially.

The format `/FMT` is the same as `x`.

Print `"hello disp"` and the three instructions after the current one:

    display "hello disp"
    display/3i $pc

Sample output:

    10      i += 1;
    2: x/3i $pc
    => 0x400531 <main+4>:   mov    0x200b0d(%rip),%eax        # 0x601044 <i>
       0x400537 <main+10>:  add    $0x1,%eax
       0x40053a <main+13>:  mov    %eax,0x200b04(%rip)        # 0x601044 <i>
    1: "hello disp" = "hello disp"

#### undisplay

Stop all `display` commands:

    undisplay

To stop a given `display`, first get its id with:

    info display
    i di

Sample output:

    Auto-display expressions now in effect:
    Num Enb Expression
    1:   y  /16bi $pc

Then:

    undisplay 1

#### disable display

#### enable display

Temporarily disable or enable `display` commands.

They are not forgotten, and can be reactivated later.

### info breakpoints

List breakpoints:

    info breakpoints

Sample output:

    Num     Type           Disp Enb Address            What
    1       breakpoint     keep y   0x0000000000400535 in main at big_function.c:8
    2       breakpoint     keep y   0x0000000000400535 in main at big_function.c:8

## Examine state

## Status

Get information about the running process.

### l

### list

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

### search

### forward-search

### fo

Search for line in current source that matches a regular expression:

    fo ret.rn

Sample output:

    39          return 0;

Search starts at the first line after the current one, and goes until the end of the current source file.

If you search multiple times, searches start from the last match, much like multiple `list` commands.

`$_` is set to the line number, so you can do things like:

    fo ret.rn
    break $_

This is great to have tests that don't depend on the exact line numbers to set breakpoint.

The GDB test suite uses a similar technique, but it does not use GDB for it, but rather the Tcl function `gdb_get_line_number`.

### rev

Like `fo`, but search backwards.

### whe

### where

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

Single CPU register: <http://stackoverflow.com/questions/5429137/how-to-print-register-values-in-gdb>

    i r rax

Sample output:

    rax            0x40057d 4195709

`0x40057d` equals `4195709` in hex.

Can also be observed with:

    p $rax

Global and static variable names:

    i variables

Tends to produce a very large output.

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

### echo

Like `printf`, but:

- does not take `"`
- does not take format strings

Backslash escapes are considered.

E.g.:

    echo asdf\n

Just use the saner `printf` instead.

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

Without debug information in an unstripped ELF:

- uses the `st_size` of the symbol to dissemble to determine where to stop
- without arguments, finds the current function by searching for the closest symbol that contains `$pc` and has `st_size` set

Being a `STT_FUNC` does not seem required.

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
    0x400098:   0x1c    0x00    0x00    0x00    0x00    0x00    0x00    0x00

### x i format

Disassemble 3 instructions starting at given address. Current address:

    x/3i $pc

Sample output:

    => 0x400531 <main+4>:   mov    0x200b0d(%rip),%eax        # 0x601044 <i>
       0x400537 <main+10>:  add    $0x1,%eax
       0x40053a <main+13>:  mov    %eax,0x200b04(%rip)        # 0x601044 <i>

## Configuration

### set

`set` has many unrelated functions. Here we document setting related.

#### set pagination

Don't ask for that annoying enter to continue pagination messages:

    set pagination off

#### set prompt

Print given strings before and after the prompt line.

Make the prompt bold and red:

    set prompt \033[1;31m(gdb) \033[m

#### focus

Change focus to another split:

    focus next

Once focus falls on the code window, you can scroll it with the up and down arrow keys.

## Colors

<http://stackoverflow.com/questions/209534/how-to-highlight-and-color-gdb-output-during-interactive-debugging>

Can be achieved with options.

## Expressions

GDB says that any expression in the language being debugged can be evaluated. TODO how?! In particular, how can it be sure that it has the same compiler version available as the program?

Furthermore, it magically understands the type of the expression and prints it nicely, e.g.:

    print 1
    print "asdf"

TODO what is the expression evaluator for expressions like `print` ?

## alias

Alias for a command:

    alias ir info registers

Unlike bash aliases, cannot include the arguments, only subcommands. E.g., the following fails:

    alias ir info registers eax

use `define` instead for that.

## define

Define commands.

    define irab
      info registers eax
      info registers ebx
    end

## Scripting features

Be warned: you will soon run into impossible to overcome limitations and start using the python API.

### source

Source a given GDB, Python or Guile file:

    source a.gdb
    source a.py

It is recognized by it's extension.

Can be done at invocation time with `-x`.

GDB also has auto-sourcing capabilities for script files with a given naming convention:

- `.gdbinit` on the current directory
- `objfile-gdb.ext` on the same directory as an object / executable file gets sourced when you do `file` <https://sourceware.org/gdb/onlinedocs/gdb/objfile_002dgdbdotext-file.html#objfile_002dgdbdotext-file>

You have to auto-list paths from which auto-loading will be allowed for security: <https://sourceware.org/gdb/onlinedocs/gdb/Auto_002dloading-safe-path.html>

### Comments

Any line starting with `#` is ignored:

    # asdf

### Convenience variable

    set $a = 1
    print $a

Each expression that gets evaluated gets an integer variable value:

    (gdb) print 1 + 1
    $1 = 2
    (gdb) print $1
    $1 = 2

Trying to reset it is an error:

    (gdb) set $1 = 2
    Left operand of assignment is not a modifiable lvalue.

### while

    while 1
      print 1
    end

### Continue despite error

<http://stackoverflow.com/questions/17923865/gdb-stops-in-a-command-file-if-there-is-an-error-how-to-continue-despite-the-er>

Not possible?

## Reverse debugging

### checkpoint

### restart

Save program state, and go back to it later: <https://sourceware.org/gdb/onlinedocs/gdb/Checkpoint_002fRestart.html>

Not sure how this works if system resources are being used, e.g. open files.

https://sourceware.org/gdb/onlinedocs/gdb/Checkpoint_002fRestart.html

### reverse commands

<https://sourceware.org/gdb/onlinedocs/gdb/Reverse-Execution.html#Reverse-Execution>

Tutorial: <https://www.sourceware.org/gdb/wiki/ProcessRecord/Tutorial>

Can only be run on a target that supports reverse debugging.

TODO the only such I know is `record`, which can be entered with `record`.

#### record

Enter the `record` target, which records everything that needs to be recorded to reverse debug.

Must be run when the program is running.

There are two main types of record:

-   `record full`, which is the default for `record`: software recording

-   `record btrace`, which uses hardware support.

    Can only be used if you have hardware support.

    There is hardware support for tracing in some processors! E.g. Intel:

    - <https://software.intel.com/en-us/blogs/2013/09/18/processor-tracing>
    - <http://blog.asset-intertech.com/test_data_out/2013/11/what-are-intel-lbr-bts-and-aet.html>

    Note however that there is very little processor and VM support as of 2015:

    - <http://stackoverflow.com/questions/16991582/extract-execution-log-from-gdb-record-in-a-virtualbox-vm>
    - <http://stackoverflow.com/questions/22507169/how-to-run-record-instruction-history-and-function-call-history-in-gdb>

## target

Target is a name for where GDB got it's data from, and what type of run this is.

TODO: get current target

List all targets:

    help target

TODO `child` vs `exec`?

### target sim

Run on a simulator.

Example usage: <http://draskovblog.blogspot.fr/2008/12/about-gdb-target-sim.html>

TODO:

- needs the `--target` configure flag to work?
- what simulator is used? Does GDB have built-in simulators??

## Alter program state

## Modify program state

## Fiddle with program

<https://sourceware.org/gdb/onlinedocs/gdb/Altering.html#Altering>

### Set registers values

Same syntax for convenience variables, very insane:

    set $eax = 1
    info registers eax

### Set memory value

- <http://stackoverflow.com/questions/3305164/how-to-modify-memory-contents-using-gdb>
- <http://stackoverflow.com/questions/19503057/in-gdb-how-can-i-write-a-string-to-memory>

### Run arbitrary assembly code

Nope: <http://stackoverflow.com/questions/5480868/how-to-call-assembly-in-gdb>

## C++

<http://stackoverflow.com/questions/8528979/how-to-determine-whether-an-object-is-an-instance-of-certain-c-class-in-gdb>
