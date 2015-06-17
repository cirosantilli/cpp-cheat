# Standard library

## STL vs standard library

The term `STL` is *not* mentioned in the C++ ISO standard.

It seems that it was once a separate library which heavily influenced the C++ ISO standrad when it was created.

<http://stackoverflow.com/questions/5205491/whats-this-stl-vs-c-standard-library-fight-all-about>

Therefore: **never** use that word, unless you are really talking about the non stdlib library which has had most of its functionality implemented on the stdlib.

Write `stdlib` and say "Standard Library" instead.

## stdlib implementations

### GCC libstdc++

GCC comes with an implementation of libstdc++.

It is the main Linux implementation.

Shared object name: `libstdc++.so`.

Website: <http://gcc.gnu.org/libstdc++/>

Get source code: seems to be on the same tree as gcc?

    git clone git://gcc.gnu.org/git/gcc.git

Find the shared library:

    locate libstdc++

Common location on Linux:

    /usr/lib/ARCH-linux-gnu/libstdc++.so.X

Locate the headers

    locate /iostream

Common location:

    /usr/include/c++/4.X/`.

The Ubuntu package is called `libstdc++6.X`. `dpkg -l | grep libstd`.

With `g++` the C++ standard library is linked against automatically. This does not happen when compiling with `gcc`, and is one of the many reasons why you should use `g++` whenever compiling C++ instead of `gcc`.

### Apache C++ Standard Library

Dead.

<https://en.wikipedia.org/wiki/Apache_C%2B%2B_Standard_Library>
