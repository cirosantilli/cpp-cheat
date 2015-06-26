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

## How to read C and C++ cheatsheets

If a subject is better explained with code, we tend to put it into code files like `.c` and `.cpp` to make it runnable, and intermingle explanations in comments.

### General cheatsheet format

The general format of C and C++ files is:

    /*
    # Subject

        General introduction.
    */

    #include "somthing.h"


    /* This is how you declare a function. */
    int f() {}

    int main() {
        /*
        # function

            A function is a reusable piece of code.
        */
        {
            /* This is how you call a function */
            f();
        }
    }

First read the initial comment, and then jump to the main function. We wish we could put the `main` function first to make it easier to read, but then there would be undefined identifiers and compilation would fail.

As you read through `main`, jump back to function definitions as they are called. the `main` method contains:

- most important comments
- the optimal reading order. Definitions may be out of order.

### Searching for keywords

Keywords are marked like markdown headers:

    # function

    # variable

    # overload

So you can grep for key concepts like:

    grep -R '# concept'

### Markers

- `ERROR`: leads to a compilation error. The code below will be commented out.
- `WARN`: leads to a compilation warning
- `BAD`: does not lead to a warning, but is almost always not what you want to do.
