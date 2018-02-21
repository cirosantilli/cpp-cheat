# Invocation

## Makefile filename case

- http://stackoverflow.com/questions/12669367/should-i-name-makefile-or-makefile

GNU Make tries the following names, in order: `GNUmakefile`, `makefile` and `Makefile`.

`Makefile` has the advantages:

- appears at the top of ls by default because ASCII uppercase comes before ASCII lowercase
- more conventional

`makefile` has the advantages:

- sticks to the other widespread convention of naming everything lowercase

You can also chose the file explicitly with `-f`.

## File extension

We often need pieces of makefiles that will be included in other make files.

The most common naming pattern for those is:

    include.mk

`.mk` is recognized as makefile by most editors.

## f

Chose a makefile explicitly:

    make -f anything.mk

## j

Let make run in 5 threads:

    make -j5

*Be warned*: this will make standard output of all threads mix up so the stdout will be meaningless.

Also, this *may break your makefiles*, since in a rule like:

    all: a b c

`a`, `b`, and `c` are run in parallel, it it might be the case that `c` *must* run only after `a` and `b`.
