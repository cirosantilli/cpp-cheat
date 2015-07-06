"""
# Visible variables

To list and get value of currently visible variables,
we have to go up on the block list.

http://stackoverflow.com/questions/30013252/get-all-global-variables-local-variables-in-gdbs-python-interface/31231722#31231722
"""

def dump_vars():
    frame = gdb.selected_frame()
    block = frame.block()
    names = set()
    while block:
        if(block.is_global):
            print()
            print('global vars')
        for symbol in block:
            if (symbol.is_argument or symbol.is_variable):
                name = symbol.name
                if not name in names:
                    # value is Value object.
                    print('{} = {}'.format(name, symbol.value(frame)))
                    names.add(name)
        block = block.superblock


gdb.execute('file visible_variables_py.out', to_string=True)
gdb.execute('break 10', to_string=True)
gdb.execute('run', to_string=True)
dump_vars()
print()
print(32 * '-')
gdb.execute('next', to_string=True)
dump_vars()
