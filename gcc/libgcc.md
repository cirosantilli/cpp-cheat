# libgcc

# libgcc_s.so

# libgcc.a

The GCC compiler may generate functions which are present on `libgcc` if the platform does not have a hardware implementation. 

Like any other built-ins, the function call may be chosen instead of the inlining to make the output shorter.

The most common cause of generating symbols in libgcc are arithmetic operations which the hardware does not support natively, e.g. `long long` operations in a 32-bit machine.

- <http://unix.stackexchange.com/questions/1812/what-does-libgcc-s-so-contain>
- <http://stackoverflow.com/questions/9414625/do-i-really-need-libgcc>
- <http://stackoverflow.com/questions/7811962/difference-between-libgcc-a-and-libgcc-s-a>
- <http://stackoverflow.com/questions/4547384/difference-between-lgcc-s-and-gcc>

## libgcc_eh.a

Contains `__gcc_personality_v0` and `_Unwind_Resume`, which are contained in `libgcc_s.so` but not `libgcc.a`.

Used only when compiling with `-static` in GCC 4.8: it seems therefore to replace `libgcc_s.so` in the static case.
