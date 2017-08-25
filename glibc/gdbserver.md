# gdbserver

Vs GDB: compiling on a slow dev board may be too slow. Then your source is on the host, so `gdb` on the dev board can't see it. If only we could embed source in debug information... <https://stackoverflow.com/questions/2511018/how-does-objdump-manage-to-display-source-code-with-the-s-option>

Restart program: <https://stackoverflow.com/questions/75255/how-do-you-start-running-the-program-over-again-in-gdb-with-target-remote/44161527#44161527>

`show args`: <https://sourceware.org/bugzilla/show_bug.cgi?id=21980>

Redirect stdout to host: <https://stackoverflow.com/questions/35082005/how-can-i-reach-stdin-stdout-through-a-gdbserver-session>

Change environment variables and working directory with `--multi`: <https://stackoverflow.com/questions/45149858/how-to-modify-the-environment-variables-of-gdbserver-without-restarting-it>
