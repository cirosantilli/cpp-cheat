"""
## disas

Python implementation of the `disas` command.
"""

def disas():
    frame = gdb.selected_frame()
    # TODO: make this work for files without debugging info.
    # block() is only available with it.
    #
    # What we need is to use symbol information instead.
    # ELF symboltable symbols have the initial address
    # and the size attributes, so that should be enough.
    block = frame.block()
    # Find the current function if in an inner block.
    while block:
        if block.function:
            break
        block = block.superblock
    start = block.start
    end = block.end
    arch = frame.architecture()
    pc = gdb.selected_frame().pc()
    instructions = arch.disassemble(start, end - 1)
    for instruction in instructions:
        print('{:x} {}'.format(instruction['addr'], instruction['asm']))

gdb.execute('file disas_py.out', to_string=True)
gdb.execute('start', to_string=True)
disas()

# Test from the inner block.
gdb.execute('break 9', to_string=True)
gdb.execute('continue', to_string=True)
print()
disas()
