"""
Define a new GDB command with Python.

https://sourceware.org/gdb/onlinedocs/gdb/Commands-In-Python.html
"""

class NewCmd(gdb.Command):
    # Will appear on help newcmd.
    "docstring"
    def __init__(self):
        super().__init__(
            'newcmd',          # Name.
            gdb.COMMAND_NONE,  # Category when `help` is entered.
            gdb.COMPLETE_NONE, # No autocomplete.
            False              # Take subcommand?
        )
    def invoke(self, arg, from_tty):
        """
        Everything printed here to stdout is captured by `execute to_string=True`.
        """
        print('newcmd')
        assert type(arg) is str
        print('arg = ' + arg)
        print('from_tty = ' + str(from_tty))
# This already registers it.
NewCmd()

gdb.execute('help newcmd')
print()
gdb.execute('newcmd a b')
