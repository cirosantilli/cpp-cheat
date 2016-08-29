# Getting started

It is a bit hard to see the beauty of physics engines without a complicated backend.

In our quest for minimalism, we are outputting calculated object positions to stdout, and they can be plotted, e.g. with Gnuplot.

So for each `.cpp` script, there should be a `.gnuplot` script.

You can run the program, and plot it's data with:

    ./plot gravity
    ./plot gravity.cpp

Or you can plot all graphs at once to PNG files with:

    ./plot

Each line of the output format is of type:

    <tick number> <point id> <x> <y> <z> [<events>]
