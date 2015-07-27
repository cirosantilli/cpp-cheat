"""
## Event

Simple event example.

This example shows how to have callbacks on breakpoints
which we did not define with the Breakpoint class.
"""

def stop_handler(event):
    print('stop_handler')
    print('stop_signal = ' + str(event.breakpoints))
gdb.events.stop.connect(stop_handler)

gdb.execute('file hello_world.out')
gdb.execute('break main')
gdb.execute('run')
