"""
## Call graph rbreak

Build a function call graph of the non-dynamic functions of an executable.

This implementation is very slow for very large projects, where `rbreak .` takes forever to complete.

- http://stackoverflow.com/questions/9549693/gdb-list-of-all-function-calls-made-in-an-application
- http://stackoverflow.com/questions/311948/make-gdb-print-control-flow-of-functions-as-they-are-called
"""

gdb.execute('file cc1', to_string=True)
gdb.execute('rbreak .', to_string=True)
gdb.execute('set args hello_world.c', to_string=True)
# rbreak before start to ignore dynamically linked stdlib functions.
gdb.execute('set confirm off')
gdb.execute('start', to_string=True)
depth_string = 4 * ' '
thread = gdb.inferiors()[0].threads()[0]
while thread.is_valid():
    frame = gdb.selected_frame()
    symtab = frame.find_sal().symtab

    stack_depth = 0
    f = frame
    while f:
        stack_depth += 1
        f = f.older()

    # Not present for files without debug symbols.
    source_path = '???'
    if symtab:
        #source_path = symtab.fullname()
        source_path = symtab.filename

    # Not present for files without debug symbols.
    args = '???'
    block = None
    try:
        block = frame.block()
    except:
        pass
    if block:
        args = ''
        for symbol in block:
            if symbol.is_argument:
                args += '{} = {}, '.format(symbol.name, symbol.value(frame))

    print('{}{} : {} : {}'.format(
        stack_depth * depth_string,
        source_path,
        frame.name(),
        args
    ))
    gdb.execute('continue', to_string=True)
