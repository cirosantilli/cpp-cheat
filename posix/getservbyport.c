/*
POSIX requires that systems must keep a database that given a protocol links:
service name (strings) to their ports and vice versa.

# servent struct

    Represents a service.

    Must contain at least the following fields:

        char   *s_name     Official name of the service.
        char  **s_aliases  A pointer to an array of pointers to
                        alternative service names, terminated by
                        a null pointer.
        int     s_port     The port number at which the service
                        resides, in network byte order.
        char   *s_proto    The name of the protocol to use when
                        contacting the service.

# getservbyport

        struct servent *getservbyport(int port, const char *proto);

    - protocol:  protocol name to look for.

        If `NULL`, match the first service found on that port for any protocol.

# getservbyname

    Same as getservbyport but using the service name itself

        struct servent *getservbyname(const char *name, const char *proto);
*/

#include "common.h"

int main() {
    struct servent *servent;
    int port;
    char proto[] = "tcp";
    char name[] = "http";

    /*
    TODO what is a service? PING, HTTP, etc. application layer stuff?
    How to gete those working then?
    */

    port = 80;
    servent = getservbyport(port, proto);
    if (servent == NULL) {
        fprintf(stderr, "getservbyport(%d, %s) failed\n", port, proto);
    } else {
        printf("getservbyport\n");
        printf("  s_name  = %s\n", servent->s_name);
        printf("  s_proto = %s\n", servent->s_proto);
    }

    servent = getservbyname(name, proto);
    if (servent == NULL) {
        fprintf(stderr, "getservbyname(%s, %s) failed\n", name, proto);
    } else {
        printf("getservbyname\n");
        printf("  s_name  = %s\n", servent->s_name);
        printf("  s_port  = %d\n", servent->s_port);
        printf("  s_proto = %s\n", servent->s_proto);
    }
    return EXIT_SUCCESS;
}
