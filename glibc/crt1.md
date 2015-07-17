# crt1

<https://en.wikipedia.org/wiki/Crt0>

Stands for C runtime.

Major functions:

- contains the `_start` symbol, which is the conventional symbol entry point (can be customized on ELF header)
- prepares the values of `argc`, `argv` and `environ`
- calls `main`
- passes the return value of main back to an `exit` system call

Present in:

- the source at `sysdeps/x86_64/start.S`
- the build under `csu/`, which seems to start for C Start Up
- the install under `lib/`

In Ubuntu 14.04, we can confirm this with:

    nm /usr/lib/x86_64-linux-gnu/crt1.o

In Ubuntu 14.04 it is part of the `libc6-dev` package, which also contains `libc.so`. It is provided by `glibc` as well.

GCC makes the linker link with it by default. This can be seen from:

    gcc -v main.c

which shows that the linker command is of type:

     /usr/lib/gcc/x86_64-linux-gnu/4.8/collect2 /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crt1.o /tmp/ccaVhizy.o [...]

A raw `ld` call however does not do this: you need to pass those files to the linker as well.

you can tell GCC not to add those files with `-nostartfiles`.

`_start` does arch specific initializations and then the common `__libc_start_main` in `csu/libc-start.c`.

This then calls:

    result = main (argc, argv, __environ MAIN_AUXVEC_PARAM);

and:

    exit(result);

## crt0

<http://stackoverflow.com/questions/2709998/crt0-o-and-crt1-o-whats-the-difference>

## crti

## crtn

Also linked by default by GCC.

## crtbegin

## crtend

Part of GCC, so not documented here.

Just to let you know that not all `crt` are glibc libraries.

Come from `libgcc/crtstuff.c`.

## Mcrt1

## Scrt1

<http://stackoverflow.com/questions/16436035/whats-the-usage-of-mcrt1-o-and-scrt1-o>

## init-first

TODO. This actually seems to be the actual initial code that is run, *not* `_start`, even though `_start` is set at the ELF header as the entry point. What is going on?

Just try to do `b _init` on `gdb`.

## Bibliography

- <http://dbp-consulting.com/tutorials/debugging/linuxProgramStartup.html>
