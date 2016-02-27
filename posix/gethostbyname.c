/*
Get the IPs of given hostnames.

# gethostbyname

    Obsoleted by `getaddrinfo` and `getnameinfo`.

    Give a hostname string ("localhost", "john") and get info on that host,
    including its IP.

        struct hostent *gethostbyname(const char *name);

    Return value:

        struct hostent {
            char *h_name;       // name of the host
            char **h_aliases;   // list of aliases (nicknames)
            int h_addrtype;     // address type
            int h_length;       // length in bytes of the address
            char **h_addr_list  // list of address (network order)
        };

    `NULL` on error

# gethostbyaddr

    Obsoleted by `getaddrinfo` and `getnameinfo`.

    Same as gethostbyname but by address.
*/

#include "common.h"

int main() {
    char **addrs;
    char **names;
    enum CONSTEXPR { MAX_HOSTNAME_LENGTH = 256 };
    char hostnames[][MAX_HOSTNAME_LENGTH] = {
        "", /* Wil be set to the localhost. */
        "www.google.com",
        "www.amazon.com"
    };
    enum CONSTEXPR2 { N_HOSTNAMES = sizeof(hostnames) / sizeof(hostnames[0]) };
    struct hostent *hostent;

    if (gethostname(hostnames[0], MAX_HOSTNAME_LENGTH) == -1) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N_HOSTNAMES; i++) {
        hostent = gethostbyname(hostnames[i]);
        if (hostent == NULL) {
            fprintf(stderr, "gethostbyname failed for hostname = %s\n", hostnames[i]);
        } else {
            printf("hostname: %s\n", hostent -> h_name);
            printf("  aliases:\n");
            names = hostent -> h_aliases;
            while (*names) {
                printf("    %s\n", *names);
                names++;
            }
            /* Assert that it is an inet address. */
            if (hostent -> h_addrtype != AF_INET) {
                printf("host is not AF_INET\n");
                exit(EXIT_FAILURE);
            }

            /* Show addresses. */
            printf("  IPs:\n");
            addrs = hostent->h_addr_list;
            while (*addrs) {
                /*
                # inet_ntoa

                    Converts integer representation of ip (4 bytes) to a string.

                    Takes network byte ordering into consideration.
                */
                printf("    %s", inet_ntoa(*(struct in_addr*)*addrs));
                addrs++;
            }
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
