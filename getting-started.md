# Getting started

## Dependencies

Most builds require:

- `make` (POSIX)
- `gcc` >= 4.7
- `g++` >= 4.7

Even though we use GNU tools by default, great attention is paid to portability of portable subjects like ANSI C, which should compile in any compiler.

In addition, each directory may have their own extra dependencies as stated in their README.

You can install dependencies on latest LTS Ubuntus with:

    ./configure

Other system install are not going to be supported as that would lead to too much maintenance overhead. If you don't have Ubuntu, consider using our [Vagrantfile](Vagrantfile).

## Usage

When there are multiple files compiled, e.g.:

    c.c -> c
    cpp.cpp -> cpp

run a given file by specifying the basename without extension:

    make run=c
    make run=cpp

The `=` sign is *not* optional!

Doing just `make run` in those cases will run the default file: `main`.
