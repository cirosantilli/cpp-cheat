"""
## Brekapoint

Create breakpoints from the python API.

TODO: create a breakpoint with the python API without ouputting anyting to stdout?
"""

gdb.execute('file big_function.out', to_string=True)

# Noisy.
gdb.Breakpoint('main')
gdb.Breakpoint('main', internal=True)

# Noisy.
class Breakpoint0(gdb.Breakpoint):
    def stop (self):
        """
        Action to take when the breakpoint is reached.
        """
        gdb.write('0\n')
        # Continue automatically.
        return False
        # Actually stop.
        return True
Breakpoint0('main')

gdb.execute('run')
gdb.execute('continue')
