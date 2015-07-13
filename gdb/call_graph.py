"""
## Call graph

This implementation disassembles every function it stops at,
and adds a breakpoint at the functions it calls.

This is slower runtime than initial `rbreak .`,
but typically faster as we move locally.

- http://stackoverflow.com/questions/9549693/gdb-list-of-all-function-calls-made-in-an-application
- http://stackoverflow.com/questions/311948/make-gdb-print-control-flow-of-functions-as-they-are-called
"""

gdb.execute('file call_graph_py.out', to_string=True)
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

        # Mark new breakpoints.
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

    print('{}{} : {} : {}'.format(
        stack_depth * depth_string,
        source_path,
        frame.name(),
        args
    ))
    gdb.execute('continue', to_string=True)
