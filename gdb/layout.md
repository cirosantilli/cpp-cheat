# layout

# tui modes

Enter very useful curses split windows views, that update automatically as the program state changes:

- `layout src`: show the source code around the current position
- `layout asm`: show the disassembly around the current position
- `layout regs`: show register values, and highlight those that changed from the last instruction

But if you are patient or use a library, you could achieve even better and more customizable views with hooks and `display` in your `.gdbinit`.

All layouts are not mutually exclusive, e.g.:

    layout asm
    layout regs

shows both the disassembly and registers, and it is a nice combo.

`layout src` can be set at invocation time with the `-tui` option.

Leave `layout` modes:

- <http://stackoverflow.com/questions/8409540/how-to-close-layout-src-windows-in-gdb>
- <http://stackoverflow.com/questions/8953720/multiple-problems-with-gdbs-tui-mode>

`Ctrl-x` keyboard shortcuts can be used to enter and leave those modes, but they do not work with `vi` `.inputrc` settings.

Once you enter one of the `tui` modes, a few specific commands are possible: <https://sourceware.org/gdb/onlinedocs/gdb/TUI-Commands.html>

TODO ANSI colors don't work on TUI mode: <https://github.com/longld/peda/issues/23>

TODO Stdout breaks TUI mode, find an issue on some bug tracker.
