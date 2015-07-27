"""
## Call graph return

Call graph that also shows the return values.

TODO: problematic because it is hard to make a silent breakpoint...
The continue must not have to_string, or else a lof of trash is printed.
"""

class MyFinishBreakpoint(gdb.FinishBreakpoint):
    def __init__(self, frame, indent):
        super().__init__(frame, True)
        self.indent = indent
        # Useless.
        #self.silent = True
    def stop (self):
        gdb.write((self.indent * depth_string) + 'return = {}\n'.format(self.return_value))

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

    # Outermost frame throws.
    try:
        MyFinishBreakpoint(frame, stack_depth)
    except ValueError:
        pass

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
    gdb.execute('continue')
