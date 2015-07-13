"""
## Continue until return

http://stackoverflow.com/questions/3649468/setting-breakpoint-in-gdb-where-the-function-returns
"""

class ContinueReturn(gdb.Command):
    def __init__(self):
        super().__init__(
            'continue-return',
            gdb.COMMAND_RUNNING,
            gdb.COMPLETE_NONE,
            False
        )
    def invoke(self, arg, from_tty):
        thread = gdb.inferiors()[0].threads()[0]
        while thread.is_valid():
            gdb.execute('ni', to_string=True)
            frame = gdb.selected_frame()
            arch = frame.architecture()
            pc = gdb.selected_frame().pc()
            instruction = arch.disassemble(pc)[0]['asm']
            if instruction.startswith('retq '):
                break
ContinueReturn()

gdb.execute('file continue_return_py.out', to_string=True)
gdb.execute('start', to_string=True)
gdb.execute('continue-return')
gdb.execute('disas')
