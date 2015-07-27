"""
## rbreak all files in a directory

This method is dirty because it uses the gdb-only command to do the job, but works.

http://stackoverflow.com/questions/29437138/can-gdb-set-break-at-every-function-inside-a-directory
"""

import os

class RbreakDir(gdb.Command):
    def __init__(self):
        super().__init__(
            'rbreak-dir',
            gdb.COMMAND_BREAKPOINTS,
            gdb.COMPLETE_NONE,
            False
        )
    def invoke(self, arg, from_tty):
        for root, dirs, files in os.walk(arg):
            for basename in files:
                path = os.path.abspath(os.path.join(root, basename))
                gdb.execute('rbreak {}:.'.format(path), to_string=True)
RbreakDir()

gdb.execute('file multifile/main.out', to_string=True)
gdb.execute('rbreak-dir multifile/d')
gdb.execute('info breakpoints')
