Simple C and C++ programs, cheats and mini projects.

Larger projects may be in separate dirs.

There may be other compiled languages here for which we don't have much material for a separate dir, specially when we interface that language with C. Ex: Fortran.

Non-portable features shall be clearly separated from portable ones in either:

- ifdef blocks
- separate files
- separate directories
- separate repositories

# Bestof

The most useful sections are currently:

- [c/c.c](c/c.c): C cheatsheet.
- [c/cpp.cpp](c/cpp.cpp): C++ cheatsheet.
- `makefile.*`: makefiles that take care of a ton of possibilities.

Other reasonably useful cheats can be found under:

- [opengl/](opengl/)
- [kde/](kde/)

# Cheatsheets

Everything that can be checked in an assertion will be checked, and will not get printed.

For exemple, a C addition operator `+` test should be done as:

    assert(1 + 1 == 2);

and *never*:

    printf("%d\n", 1 + 1);

so that all can be verified automatically.

Features which yield unpredictable outputs can print results to stdout. For example, `time(NULL)`

    printf("%d\n", 1 + 1);

Features that:

- require user input such as C `scanf`
- make programs wait for perceptible amounts of time

shall be put inside a block analogous to a `if (0){ ... }` to be turned on only when users want to test those specific features.

Cheat source comments are writen in markdown *indented by headers* and commented out.

Every important keyword that one might search for in the feature has a hash before it, e.g. `#function`, `#include`, `#printf`, etc.

# Contributing

If you find any factual error, or want to include new information, you are more than welcome to send a PR!
