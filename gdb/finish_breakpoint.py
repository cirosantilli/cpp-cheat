"""
## FinishBreakpoint

Derived from Breakpoint.

https://sourceware.org/gdb/onlinedocs/gdb/Finish-Breakpoints-in-Python.html#Finish-Breakpoints-in-Python
"""

gdb.execute('file ./finish_breakpoint_py.out', to_string=True)
gdb.execute('start', to_string=True)
gdb.execute('break f', to_string=True)
gdb.execute('continue', to_string=True)
gdb.execute('where', to_string=True)

class MyFinishBreakpoint(gdb.FinishBreakpoint):
    def __init__(self):
        super().__init__(gdb.selected_frame(), True)
    def stop (self):
        gdb.write('return_value = {}\n'.format(self.return_value))
b = MyFinishBreakpoint()

# TODOdd
gdb.execute('continue')
