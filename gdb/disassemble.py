"""
Disassemble some instructions.

https://sourceware.org/gdb/onlinedocs/gdb/Architectures-In-Python.html
"""

gdb.execute('file big_function.out', to_string=True)
gdb.execute('start', to_string=True)

frame = gdb.selected_frame()
arch = frame.architecture()
print(arch.name())

pc = gdb.selected_frame().pc()

print(arch.disassemble(pc)[0])
