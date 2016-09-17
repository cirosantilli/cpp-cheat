# Getting started

    make imgs

does the following:

- compile the C++ files
- run them, and save their output to `.dat` files. That is the integrated solution to the physical problem.
- plot the `.dat` files

Each line of the `.dat` files has the format:

    <tick number> <point id> <x> <y> <z> <speed-x> <speed-y> <speed-z> [<events>]

It is a bit hard to see the beauty of physics engines without a complicated backend.
