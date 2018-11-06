# Getting started

If the program `string.c` has a corresponding `string.gdb` file, you can run it with with:

    make
    ./run string
    ./run string.
    ./run string.c
    ./run string.gdb

We have started automating some tests with pexpect:

    make
    ./test

This semi-duplicates what the GDB tree does with expect :-)
