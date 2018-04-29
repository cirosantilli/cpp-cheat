# Default

    cd src0

    scons
    ./main.out
    # => No such file or directory.
    ../src1/main.out
    # => 1

    scons ..
    ./main.out
    # => 0
    ../src1/main.out
    # => 1

By default, SCons builds all targets under the current directory and descendants.

If `Default()` is given, it change that default to the given programs.

You can always go back to recurse under a given directory with `scons path/to/dir`.
