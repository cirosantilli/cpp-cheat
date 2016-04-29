# Benchmark

Micro-benchmark two versions of the same function.

Run as:

    make run ARGS='1000000 100'

Requires POSIX for `getrusage`, which actually measures system time with microsecond resolution.

There is no ANSI C analogue AFAIK.
