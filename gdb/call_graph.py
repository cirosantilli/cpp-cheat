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
gdb.execute('start', to_string=True)
depth_string = 4 * ' '
thread = gdb.inferiors()[0].threads()[0]
disassembled_functions = set()
while True:
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

        # Put a breakpoint on the address of every funtion called from this function.
        # Only do that the first time we enter a function (TODO implement.)
        start = block.start
        if not start in disassembled_functions:
            disassembled_functions.add(start)
            end = block.end
            arch = frame.architecture()
            pc = gdb.selected_frame().pc()
            instructions = arch.disassemble(start, end - 1)
            for instruction in instructions:
                # This is UGLY. I wish there was a disassembly Python interface to GDB,
                # like https://github.com/aquynh/capstone which allows me to extract
                # the opcode without parsing.
                if instruction['asm'].split()[0] == 'callq':
                    gdb.Breakpoint('*{}'.format(instruction['addr']), internal=True)

    print('{}{} : {} : {}'.format(
        stack_depth * depth_string,
        source_path,
        frame.name(),
        args
    ))
    # We are at the call instruction.
    gdb.execute('continue', to_string=True)
    if thread.is_valid():
        # We are at the first instruction of the called function.
        gdb.execute('stepi', to_string=True)
    else:
        break
