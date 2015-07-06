"""
## read_var

Get the current value of a variable as a Value object.

To loop over all variables, use blocks.
"""

gdb.execute('file read_var_py.out', to_string=True)
gdb.execute('start', to_string=True)
frame = gdb.selected_frame()
print(frame.read_var('i'))
print(frame.read_var('g'))
print(frame.read_var('f'))
print()
for i in range(5):
    gdb.execute('next', to_string=True)
print(frame.read_var('i'))
print(frame.read_var('g'))
print(frame.read_var('f'))
