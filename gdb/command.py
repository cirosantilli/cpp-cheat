"""
Define a new GDB command with Python.
"""

class NewCmd (gdb.Command):
    "newcmd docstring."
    def __init__ (self):
        super().__init__(
            'newcmd',
            gdb.COMMAND_SUPPORT,
            gdb.COMPLETE_NONE,
            True
        )
    def invoke(self, arg, from_tty):
        print('newcmd')
        print('arg = ' + str(arg))
        print('from_tty = ' + str(from_tty))
NewCmd()
gdb.execute('help newcmd')
gdb.execute('newcmd')
gdb.execute('newcmd a b')
