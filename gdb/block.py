"""
## Block

Represents a scope.

https://sourceware.org/gdb/onlinedocs/gdb/Blocks-In-Python.html

## Symbol

https://sourceware.org/gdb/onlinedocs/gdb/Symbols-In-Python.html
"""

gdb.execute('file block_py.out', to_string=True)
# Inner block.
gdb.execute('break 37', to_string=True)
gdb.execute('run', to_string=True)
frame = gdb.selected_frame()
block = frame.block()
while block:
    print(32 * '=')
    print('function = ' + str(block.function))
    print('is_valid() = ' + str(block.is_valid()))
    print('start = ' + str(block.start))
    print('end = ' + str(block.end))
    print('is_global = ' + str(block.is_global))
    print('is_static = ' + str(block.is_static))
    print()
    for symbol in block:
        print('name = ' + str(symbol.name))
        # gdb.SYMBOL_LOC_XXX constants.
        print('addr_class = ' + str(symbol.addr_class))
        print('linkage_name = ' + str(symbol.linkage_name))
        print('print_name = ' + str(symbol.print_name))
        print('type = ' + str(symbol.type))
        print('line = ' + str(symbol.line))
        print('is_argument = ' + str(symbol.is_argument))
        print('is_constant = ' + str(symbol.is_constant))
        print('is_function = ' + str(symbol.is_function))
        print('is_variable = ' + str(symbol.is_variable))
        print('needs_frame = ' + str(symbol.needs_frame))
        try:
            print('value = ' + str(symbol.value(frame)))
        except:
            pass
        print()
    block = block.superblock
