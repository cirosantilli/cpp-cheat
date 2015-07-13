"""
## disas

Python implementation of disas
"""

def disas():
    frame = gdb.selected_frame()
    block = frame.block()
    while block:
        if block.function:
            break
    start = block.start
    end = block.end
    arch = frame.architecture()
    pc = gdb.selected_frame().pc()
    instructions = arch.disassemble(start, end - 1)
    for instruction in instructions:
        print('{:x} {}'.format(instruction['addr'], instruction['asm']))

gdb.execute('file if_else.out', to_string=True)
gdb.execute('start', to_string=True)
disas()
print()
gdb.execute('disas')
