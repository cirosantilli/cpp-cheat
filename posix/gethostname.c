/*
# gethostname

    Copies name of current host on given string:

        int gethostname(char* hostname, int namelength);

    Name is truncated to namelength if too large
*/

#include "common.h"

int main() {
    const int namelength = 256;
    char hostname[namelength];
    gethostname(hostname, namelength);
    puts(hostname);
    return EXIT_SUCCESS;
}
