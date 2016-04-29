# cflow

Make static call graphs.

GNU.

Not perfect nor ultra-powerful, but comes in handy when reading code.

<https://en.wikipedia.org/wiki/GNU_cflow>

<http://www.gnu.org/software/cflow/>

Usage:

    cflow main.c

Sample output:

    main() <int main () at main.c:49>:
        printA()
        printMain() <void printMain () at main.c:40>:
            printf()
        printf()

TODO C++ method? Does not seem to work.

TODO ignore `#include` / other files. Otherwise too much stdlib trash. `-d` may help... Can't even find a thread for that.
