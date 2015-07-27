"""
## Brekapoint silent

A breakpoint that prints something on `stop`,
but only what the breakpoint says, and nothing else that continue would print.
"""

gdb.execute('file hello_world.out', to_string=True)

# Noisy.
gdb.Breakpoint('main')

# Silen.t.
gdb.Breakpoint('main', internal=True)

# Noisy.
class Breakpoint0(gdb.Breakpoint):
    def __init__(self, addr):
        # The internal will silence it at creation time.
        super().__init__(addr, internal=True)
    def stop (self):
        """
        Action to take when the breakpoint is reached.
        """
        gdb.write('STOPPED!\n')
        # Continue automatically.
        return False
        # Actually stop.
        return True
Breakpoint0('main')

gdb.execute('run')

# Cannot be to_string= or else we won't see STOPPED.
gdb.execute('continue')
