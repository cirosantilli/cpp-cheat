"""
## Break return

Add a breakpoint to every return instruction of the current function.

http://stackoverflow.com/questions/3649468/setting-breakpoint-in-gdb-where-the-function-returns
"""

class BreakReturn(gdb.Command):
    def __init__(self):
        super().__init__(
            'break-return',
            gdb.COMMAND_RUNNING,
            gdb.COMPLETE_NONE,
            False
        )
    def invoke(self, arg, from_tty):
        frame = gdb.selected_frame()
        block = frame.block()
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
            if instruction['asm'].startswith('retq '):
                gdb.Breakpoint('*{}'.format(instruction['addr']))
BreakReturn()

gdb.execute('file continue_return_py.out', to_string=True)
gdb.execute('start', to_string=True)
gdb.execute('disas')
print()
gdb.execute('break-return')
gdb.execute('continue')
gdb.execute('disas')
