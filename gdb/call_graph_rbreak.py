"""
## Call graph rbreak

Build a function call graph of the non-dynamic functions of an executable.

This implementation is very slow for very large projects, where `rbreak .` takes forever to complete.

- http://stackoverflow.com/questions/9549693/gdb-list-of-all-function-calls-made-in-an-application
- http://stackoverflow.com/questions/311948/make-gdb-print-control-flow-of-functions-as-they-are-called

What happens on the output:

-   First line is:

        ../csu/init-first.c : _init : argc = 1, argv = 0x7fffffffd728, envp = 0x7fffffffd738

    It actually does get called before the `_start`:
    http://stackoverflow.com/questions/31379422/why-is-init-from-glibcs-csu-init-first-c-called-before-start-even-if-start-i

    I think it has a level deeper than one because the callees are not broke on:
    they are not part of the executable.
"""

gdb.execute('file ./call_graph_py.out', to_string=True)
gdb.execute('set confirm off')
# rbreak before run to ignore dynamically linked stdlib functions which take too long.
# If we do it before, we would also go into stdlib functions, which is often what we don't want,
# since we already understand them.
gdb.execute('rbreak .', to_string=True)
gdb.execute('run', to_string=True)
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
