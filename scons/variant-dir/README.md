# Variant dir

    scons
    ./build-0/main.out
    # => 0
    scons x=1
    ./build-1/main.out
    # => 1

We could do something more advanced by:

- hash all input arguments like `x` and name the output directory after them
- cat the input arguments to a file in that directory to enable identifying the directories
