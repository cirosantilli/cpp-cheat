"""
## Call graph rbreak directory

rbreak only inside a directory to limit the startup overhead.
"""

import os

# The directory path to break at.
path = u'multifile/d'
depth_string = 4 * ' '
gdb.execute('file multifile/main.out', to_string=True)

for root, dirs, files in os.walk(path):
    for basename in files:
        path = os.path.abspath(os.path.join(root, basename))
        gdb.execute('rbreak {}:.'.format(path), to_string=True)
gdb.execute('run', to_string=True)

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
