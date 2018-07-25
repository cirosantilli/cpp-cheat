# Threads

Run:

    ./run threads

Inside GDB:

    run

Then:

    Ctrl + C

All threads stop.

## Get backtraces for all threads

https://stackoverflow.com/questions/18391808/how-to-get-the-backtrace-for-all-the-threads-in-gdb

    thread apply all bt

Sample output:

    Thread 3 (Thread 0x7ffff6fee700 (LWP 29344)):
    #0  0x00007ffff78bc30d in nanosleep () at ../sysdeps/unix/syscall-template.S:84
    #1  0x00007ffff78bc25a in __sleep (seconds=0) at ../sysdeps/posix/sleep.c:55
    #2  0x0000000000400839 in thread_1 (arg=0x7fffffffcf0c) at threads.c:33
    #3  0x00007ffff7bc16ba in start_thread (arg=0x7ffff6fee700) at pthread_create.c:333
    #4  0x00007ffff78f741d in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:109

    Thread 2 (Thread 0x7ffff77ef700 (LWP 29343)):
    #0  0x00007ffff78bc30d in nanosleep () at ../sysdeps/unix/syscall-template.S:84
    #1  0x00007ffff78bc25a in __sleep (seconds=0) at ../sysdeps/posix/sleep.c:55
    #2  0x000000000040075b in thread_0 (arg=0x7fffffffcf08) at threads.c:19
    #3  0x00007ffff7bc16ba in start_thread (arg=0x7ffff77ef700) at pthread_create.c:333
    #4  0x00007ffff78f741d in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:109

    Thread 1 (Thread 0x7ffff7fc7700 (LWP 29339)):
    #0  nanosleep () at ../sysdeps/unix/syscall-template.S:85
    #1  0x00007ffff78bc25a in __sleep (seconds=0) at ../sysdeps/posix/sleep.c:55
    #2  0x00000000004008b9 in main () at threads.c:48

So we see that there are three threads:

- `1` which is the `main`
- `2` and `3` which we created ourselves

all of which are very likely inside sleep.

A few more information we can extract:

    LWP 29339

means:

- `LWP`: Light Weight Process
- `29339`: thread ID

If we also get the process ID with <https://stackoverflow.com/questions/36704270/how-does-one-obtain-the-pid-of-the-currently-debugged-process-in-gdb>:

    info inferior

then we can confirm the thread ID under `/proc`:

    ls /proc/<pid>/task/<tid>

The part:

    Thread 0x7ffff77ef700

gives us value of `pthread_t` <https://stackoverflow.com/questions/2188089/pthread-t-to-gdb-thread-id>. This can be confirmed with:

    thread 1
    up 2
    p/x threads

## More basic things

Switch to a thread:

    thread 1

Now the usual commands like `bt`, `info registers`, etc. will apply to that thread.

List all threads:

    info threads

This shows one extra information that `thread apply all bt` does not: the thread name:

    myname1

which defaults to the executable name, but which we have modified for the thread 1 with `pthread_setname_np`, see also: <https://stackoverflow.com/questions/8944236/gdb-how-to-get-thread-name-displayed/27682706#27682706>
