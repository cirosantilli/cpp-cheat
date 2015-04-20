# GDB

GDB uses symbol information contained in executables to debug them

You need to generate debug information with the compile files to be able to use GDB.

For C, you can use:

    gcc -ggdb3 a.c

To run executable and debug it with GDB use:

    gdb a.out

It is possible to attach GDB to a running instance of a program after it was started:

    gdb a.out $pid

When you quit GDB, the process will continue to run normally.

## Commands

Commands you can run from inside GDB

### h

Help:

    h

### r

Run program:

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
        33	            if (input[right] < input[pivot]) {

    which says that it happened at line 33 of file `quick.cpp`.

### k

Kill program:

    k

Keeps breakpoints, etc. saved for next debug session.

### q

Quit:

    q

### b

Set breakpoint.

    b 10

    b func

    b c.c:10

    b c.c:func

Two lines after and before the current line:

    b +2
    b -2

### l

List 10 lines of code around the current line:

    l

Sample output if we are on line 33:

    28	        std::tie(left_begin, pivot) = recursion_stack.back();
    29	        recursion_stack.pop_back();
    30	        left = left_begin;
    31	        right = left;
    32	        while (right < pivot) {
    33	            if (input[right] < input[pivot]) {
    34	                std::swap(input[left], input[right]);
    35	                left++;
    36	            }
    37	            right++;

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

### whe

Sample output:

    #0  0x0000000000401d5b in quick_sort<int> (input=...) at quick.cpp:33
    #1  0x00000000004016d7 in main (argc=2, argv=0x7fffffffd768) at quick.cpp:49

So here we see that:

- function `main` called function `quick_sort` at line 49
- function `main` called function `quick_sort` at line 49

TODO understand everything

## Step backwards in time

## Omniscient debugging

Considered a "high priority project" by the FSF as of January 2015 <http://www.fsf.org/campaigns/priority-projects/reversible-debugging-in-gdb>

---

TODO format the rest of this section as md:

    i b
        #view breakpoints

    dis 1
        #disable breakpoint 1.
        #1 is gotten from `i b`

    en 1
        #enable breakpoint 1.
        #1 is gotten from `i b`

    d
        #delete all breakpoints
    d 1
        #delete breakpoint 1

    cl 10
    cl func
    cl file:func
    cl file:10
        #delete breakpoint at line 10

    w
        #set watchpoint
        #stop prog when var or expr changes value

    c
        #set catchpoint
        #TODO ?

    s
        #step exec next line
        #if func call, step inside funv
    n
        #setp next. if func call
        #run entire func now

    ba
        #show backtrace of stack at current point

    f
        #show cur frame number
    f 1
        #go to frame 1

    p
        #p x
            #print value of variable x in current frame
            #vars in other frames cannot be seen
        #p x+1
        #p x*2
        #p func(1)
        #p array
        #p array[3]@5
            #print 3 vals or array, starting at elem 5
        #p myStruct
        #p myStruct.key
        #set print pretty

        #format
            #(gdb) p mychar    #default
            #$33 = 65 'A'
            #(gdb) p /o mychar #octal
            #$34 = 0101
            #(gdb) p /x mychar #hex
            #$35 = 0x41
            #(gdb) p /d mychar
            #$36 = 65
            #(gdb) p /u mychar #unsigned decimal
            #$37 = 65
            #(gdb) p /t mychar #binary
            #$38 = 1000001
            #(gdb) p /f mychar #float
            #$39 = 65
            #(gdb) p /a mychar
            #$40 = 0x41

        #p &mychar
            #addres of mychar
            #p *(&mychar)

        #pt x
            #print type of var x

    attach
        #links to a running process

    gdbinit
        #~/.gdbinit
        #somedir/.gdbinit
