/*
# main function

    # Call main from the program

        Seems legal:
        http://stackoverflow.com/questions/13948562/recursion-using-main-function#comment19237980_13948579

        Illegal in C++ however.

    # main signature

        - http://stackoverflow.com/questions/204476/what-should-main-return-in-c-and-c
        - http://stackoverflow.com/questions/4207134/what-is-the-proper-declaration-of-main

        Valid signatures: either:

            int main()

        or:

            int main(int argc, char *argv[])

        Or equivalent ones to the above:

        argc array vs pointer: (TODO why equivalent)

            int main(int argc, char **argv)

        Default return type `int` (C89 only):

            main()

        Explicit `void` prototype:

            int main(void)
*/

#include "common.h"

int main() {
    /*
    # main return

        Valid returns are:

        - `EXIT_SUCCESS` or `0` to indicate success
        - `EXIT_FAILURE`        to indicate failure

        C99: return is optional. If omited a `return 0` is added to the program.

        But just always return to be C89 compatible.
        TODO I think that in C89 it is legal to not use return like for any other function,
        but it leads to UB.
    */
    {
        return EXIT_SUCCESS;
        return EXIT_FAILURE;
    }
}
