# crt1

<https://en.wikipedia.org/wiki/Crt0>

Stands for C runtime.

`crt1.o` contains the `_start`, which then calls `main`.

In Ubuntu 14.04, we can confirm this with:

    nm /usr/lib/x86_64-linux-gnu/crt1.o

In Ubuntu 14.04 it is part of the `libc6-dev` package, which also contains `libc.so`. It is provided by `glibc` as well.

The linker links with it by default. This can be seen from:

    gcc -v main.c

which shows that the linker command is of type:

     /usr/lib/gcc/x86_64-linux-gnu/4.8/collect2 /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crt1.o /tmp/ccaVhizy.o [...]

The `_start` symbol is at `sysdeps/x86_64/start.S`, which later gets renamed to `crt1.o`.

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

Present directly under `sysdeps/x86_64`.

## crtbegin

## crtend

TODO
