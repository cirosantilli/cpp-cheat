#!/usr/bin/env python3

"""
Print lines of the current stack frame.
"""

import sys

file_path = 'if_else.out'
gdb.execute('file {}'.format(file_path), to_string=True)
gdb.execute('start', to_string=True)

sal = gdb.selected_frame().find_sal()
# RIP of the first instruction in this frame (address of second instruction).
gdb.write('pc = 0x{:x}\n'.format(sal.pc))
# Memory address of the end of the next instruction.
gdb.write('last = 0x{:x}\n'.format(sal.last))
# Line number of the first line of the frame on the source file.
gdb.write('line = {}\n'.format(str(sal.line)))

symtab = sal.symtab
# Name of the source file that generated the current line.
p = symtab.fullname()
gdb.write('fullname = {}\n'.format(p))
# The actual source is not embedded into the debug information:
# only the line numbers. We must read it again.
f = open(p, 'r')
source_lines = f.readlines()
f.close()

# @input line LineTableEntry
def print_line(line):
    line_number = line.line
    gdb.write(
        '{:2d} | {:x} | {}'.format(
            line_number,
            line.pc,
            source_lines[line_number - 1]
        ),
    )

# Dump the entire stack frame.
print('linetable = line | address')
linetable = symtab.linetable()
for line in linetable:
    print_line(line)

# Dump all executed lines.
thread = gdb.inferiors()[0].threads()[0]
while thread.is_valid():
    sal = gdb.decode_line()[1][0]
    print(sal.line)
    linetable = sal.symtab.linetable()
    print(linetable.line(sal.line))
    gdb.execute('next', to_string=True)
