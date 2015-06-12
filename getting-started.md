# Getting started

    ./configure
    cd c
    make test
    cd ../cpp
    make test

## Dependencies

Most builds require:

- `make` (POSIX)
- `gcc` >= 4.7
- `g++` >= 4.7

Those dependencies are installed with the top-level `./configure`.

Each directory may have their own extra dependencies as stated in their README.

`configure` files should work on the latest Ubuntu LTS.

Other system install are not going to be supported as that would lead to too much maintenance overhead.

It should be easy to guess what packages you need for your distribution based on the Ubuntu packages, and you can also use the [Vagrantfile](Vagrantfile).

Great attention is paid to portability and less portable code is clearly separated from more portable code.
