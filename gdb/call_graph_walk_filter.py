"""
## Call graph walk filter

This implementation disassembles every function it stops at,
and adds a breakpoint at the functions callq commands.

TODO this is currenty broken. I half gave up on it when I noticed that
the bottleneck was filtering functions by directory, which is harder on this walk implementation
because we have to break at the callq instructions.
I'm keeping this file as some of the walking code might be reused.

This is slower runtime than initial `rbreak .`,
but typically faster as we move locally.

- http://stackoverflow.com/questions/9549693/gdb-list-of-all-function-calls-made-in-an-application
- http://stackoverflow.com/questions/311948/make-gdb-print-control-flow-of-functions-as-they-are-called
"""

import re

path_filter_re = re.compile(r'/gcc/')

gdb.execute('file cc1', to_string=True)
gdb.execute('set args hello_world.c', to_string=True)
gdb.execute('start', to_string=True)
depth_string = 4 * ' '
thread = gdb.inferiors()[0].threads()[0]
# Function addresses that have already been disassembled.
disassembled_functions = set()
# Function addresses whose path does not match the filter regex.
function_blacklist = set()
while True:
    path_filter_re_matches = path_filter_re.search(source_path)
    frame = gdb.selected_frame()

    if not path_filter_re_matches:
        pass
        # TODO

    stack_depth = 0
    f = frame
    while f:
        stack_depth += 1
        f = f.older()

    # Not present for files without debug symbols.
    source_path = '???'
    symtab = frame.find_sal().symtab
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

        if path_filter_re_matches:
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
                    # like https://github.com/aquynh/capstone which allows to extract
                    # the opcode without parsing.
                    instruction_parts = instruction['asm'].split()
                    opcode = instruction_parts[0]
                    if opcode == 'callq':
                        # fails for instructions that start with *, basically rip (could be resolved to an address statically)
                        # or rax (must be broken upon every time since we don't know where it will jump to).
                        try:
                            target_address = int(instruction_parts[1][2:], 16)
                        except ValueError:
                            target_address = None
                        if not (target_address and target_address in function_blacklist):
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
