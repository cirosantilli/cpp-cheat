# netdb.h

Network information (NETwork DataBase).

## getaddrinfo

## getnameinfo

Make `gethostbyname` and `gethostbyaddr` obsolete. TODO example.

## getprotobyname

The system must implement a database that links protocol names to protocol identifier numbers.

Interface:

    struct protoent *getprotobyname(const char *name);

`protoent` must contain at least the following fields:

    char   *p_name     Official name of the protocol.
    char  **p_aliases  A pointer to an array of pointers to
                        alternative protocol names, terminated by
                        a null pointer.
    int     p_proto    The protocol number.

## htons

Host TO Network Short.

Takes a short (2 bytes), and converts it to the correct byte ordering expected by the network.

You must do this, or else e.g. the network won't look at the right port.

Versions:

- `htons`
- `htonl` (long, 4 bytes)
- `ntohs` (inverse)
- `ntohl`

TODO example.
