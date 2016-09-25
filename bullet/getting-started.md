# Getting started

    make imgs

does the following:

-   compile the C++ files

-   run them, and save their output to `.dat` files. That is the integrated solution to the physical problem.

-   plot the `.dat` files into `.png` files.

Each line of the `.dat` files has the format:

    <tick number> <point id> <x> <y> <z> <speed-x> <speed-y> <speed-z> \
    <rot-x> <rot-y> <rot-z> <rot-angle> <rot-speed-x> <rot-speed-y> <rot-speed-z> [<events>]

Note that for the rotation, only 3 parameters are required, but we use 4 as that is easier to view:

-   one vector to give the direction on 3 parameters.

    This could be done with 2 angles because this vector can be chosen normal, and thus looses a degree of freedom.

-   one angle to turn around the vector with right hand rule

The color convention of the graph lines is:

-   `r`: `x`, mnemonic: first of RGB.

-   `g`: `y`

-   `b`: `z`

-   `y`: rotation angle. No mnemonic, color chosen randomly.

    We always divide the rotation angle by 2 pi, so that is restricted to `[-1,1]`.
