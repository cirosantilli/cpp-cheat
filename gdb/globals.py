"""
Print global variables.

Better than `info variables` because that produces too much unwanted output:
this only shows actually defined globals.

TODO this does not see global variables defined in other files. Does not seem possible:
http://stackoverflow.com/questions/30013252/get-all-global-variables-local-variables-in-gdbs-python-interface/31231722#31231722

## global_block

Every block and symtab has an associated global block.
"""

class Globals(gdb.Command):
    "Dump global variables."
    def __init__ (self):
        super().__init__(
            'globals',
            gdb.COMMAND_STATUS,
            gdb.COMPLETE_NONE,
            False
        )
    def invoke(self, arg, from_tty):
        frame = gdb.selected_frame()
        block = frame.block().global_block
        for symbol in block:
            if symbol.is_variable:
                print('{} = {}'.format(symbol.name, symbol.value(frame)))
Globals()
gdb.execute('file visible_variables_py.out', to_string=True)
gdb.execute('start', to_string=True)
gdb.execute('globals')
