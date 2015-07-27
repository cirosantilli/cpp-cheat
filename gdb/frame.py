"""
## Frame

Exploring the frame class.
"""

gdb.execute('file call_graph_py.out', to_string=True)
gdb.execute('set confirm off')
gdb.execute('rbreak .', to_string=True)
gdb.execute('start', to_string=True)
thread = gdb.inferiors()[0].threads()[0]
while thread.is_valid():
    print()
    frame = gdb.selected_frame()
    symtab = frame.find_sal().symtab
    if symtab:
        print(symtab.fullname())
    # TODO why can this be None even if frame.name() is not?
    print(frame.function())
    print(frame.name())
    gdb.execute('continue', to_string=True)
