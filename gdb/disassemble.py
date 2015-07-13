"""
Disassemble some instructions.

https://sourceware.org/gdb/onlinedocs/gdb/Architectures-In-Python.html#Architectures-In-Python
"""

gdb.execute('file big_function.out', to_string=True)
gdb.execute('start', to_string=True)

frame = gdb.selected_frame()
arch = frame.architecture()
print(arch.name())

pc = gdb.selected_frame().pc()

# 1 instruction.
print(arch.disassemble(pc)[0]['asm'])
