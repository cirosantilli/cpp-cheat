Simple C and C++ programs, cheats and mini projects.

Larger projects may be in separate dirs.

There may be other compiled languages here for which I don't
have much material for a separate dir, specially when I interface
that language with C. Ex: Fortran.

Non-portable features shall be clearly separated from portable ones
in either:

- ifdef blocks
- separate files
- separate directories
- separate repositories

#cheatsheets

For the cheats, everything that can be checked in an assertion will be checked,
will not get printed. For exemple, a C addition operator `+` test should be done as:

    assert(1 + 1 == 2);

and never:

    printf("%d\n", 1 + 1);

so that all can be verified automatically.

Features which yield unpredictable outputs can print results to stdout.
For example, `time(NULL)`

    printf("%d\n", 1 + 1);

Features that require user input such as C `scanf` or that make programs wait
for perceptible ammounts of time shall be put inside a block analogous to a `if (0){ ... }`
to be turned on only when users want to test those specific features.
