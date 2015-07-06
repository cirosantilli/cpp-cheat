# Valgrind

TODO how does it work? Seems to emulate program execution.

More precise than most tools which use sampling, but also much slower.

    vallgrind --tool=callgrind ./a.out
    kcachegrind callgrind.out.6949
