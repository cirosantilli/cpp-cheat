# Introduction

<https://sourceware.org/gdb/onlinedocs/gdb/>

GDB allows you to advance through programs one line or assembly instruction at a time, and find out the exact program state at any point.

## Alternatives

GDB with the default configuration is not a convenient interactive font-end if you are going to do a lot debugging.

Instead, use either of:

- `-tui` option
- IDE front-ends
- <https://github.com/cgdb/cgdb> ncurses

The great advantage of GDB, as for most command line applications, is that you can script it. Just put the debugging commands in a file, then run it with `-x file.gdb`.

This method is more efficient for non-trivial debugging, as you have to gradually improve on the debug information to extract, so that you are actually writing a data mining program.

You will also want to use the `commmands` command with `-x`.

Being terminal based also makes it integrable into Vim.

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
- break at instruction with given opcode: <http://stackoverflow.com/questions/14031930/break-on-instruction-with-specififc-opcode-in-gdb>
