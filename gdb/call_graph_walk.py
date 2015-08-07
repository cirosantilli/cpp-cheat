"""
## Call graph

This implementation disassembles every function it stops at once,
and adds a breakpoint at the callq instructions.

We cannot break on the functions themselves, which would be good as it would lead to less breakpoints,
because otherwise we would need to disassemble functions every time looking for
polymorphic `callq *rax`.

This is slower runtime than initial `rbreak .`,
but typically faster for large code bases as it avoids the huge initial rbreak overhead.

The runtime of this method is still too slow for huge executables like GCC's `cc1`.

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
    gdb.execute('continue', to_string=True)
    # We are at the call instruction.
    if thread.is_valid():
        gdb.execute('stepi', to_string=True)
        # We are at the first instruction of the called function.
    else:
        break
