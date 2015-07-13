"""
## Continue until instruction with given opcode

http://stackoverflow.com/questions/14031930/break-on-instruction-with-specific-opcode-in-gdb

TODO break at other breakpoints
"""

class ContinueI(gdb.Command):
    """
Continue until instruction with given opcode.

    ci OPCODE

Example:

    ci callq
    ci mov
"""
    def __init__(self):
        super().__init__(
            'ci',
            gdb.COMMAND_BREAKPOINTS,
            gdb.COMPLETE_NONE,
            False
        )
    def invoke(self, arg, from_tty):
        thread = gdb.inferiors()[0].threads()[0]
        while thread.is_valid():
            gdb.execute('si', to_string=True)
            frame = gdb.selected_frame()
            arch = frame.architecture()
            pc = gdb.selected_frame().pc()
            instruction = arch.disassemble(pc)[0]['asm']
            if instruction.startswith('retq '):
                gdb.write(instruction + '\n')
                break
ContinueI()

#gdb.execute('file big_function.out', to_string=True)
#gdb.execute('start', to_string=True)
#gdb.execute('help ci')
#gdb.execute('disas')
#print()
#gdb.execute('ci callq')
#gdb.execute('disas')
#print()
#gdb.execute('ci callq')
#gdb.execute('disas')
#print()
#gdb.execute('ci callq')
#gdb.execute('disas')
#print()
#gdb.execute('ci callq')
#gdb.execute('disas')
#print()
