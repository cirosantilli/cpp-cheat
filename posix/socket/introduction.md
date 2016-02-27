# Introduction

Sockets are similar to pipes but:

- allow communication across different systems and are thus a base for networks local sockets also exist.
- allow bidirectional communication
- allow multiple clients to connect to a single server (the concepts of client and server are clearly defined)

## What POSIX sockets can do

POSIX sockets allows to implement any networking Application layer program, and thus to implement things like web browsers, crawlers or `wget` like utilities.

It seems however that POSIX does not support lower level layer control, for example making an ICMP echo <http://www.microhowto.info/howto/send_an_arbitrary_ipv4_datagram_using_a_raw_socket_in_c.html>

For those functionalities it seems that Linux specific functionalities must be used, for example raw sockets: <http://www.pdbuchan.com/rawsock/rawsock.html>

## Socket params

Sockets are characterized by three parameters:

- domain
- type
- protocol

This are exactly the 3 parameters that the `socket` call receives.

### Domain

-   `AF_UNIX`: local sockets for single machine usage.

    UNIX domain sockets are uniquely identified on the filesystem like pipes or other special files.

-   `AF_INET`: internet IP protocol, regular local networks or the internet.

    This is one of the few stream like resources that are not put into the filesystem because TODO

-   `AF_INET6`: IPv6

### Type

-   `SOCK_STREAM`: connexion works like a file stream to the program.

    In `AF_INET` this is automatically done via TCP/IP.

    Delivery and ordering is guaranteed by TCP/IP.

    A connection is maintained while data is being sent.

-   `SOCK_DGRAM`: datagram.

    Lower level protocol.

    Does not establish connection.

    No automatic delivery guarantee.

    Data must be manually split into packages of a maximum width.

    In `AF_INET` this is UDP.

Certain domains may have different types:

- `AF_UNIX` has a single type: `SOCK_STREAM`.

- `AF_INET` has the following types: TODO

### Protocol

Sometimes it is possible to choose different protocols for a given type:

- `0` uses the default protocol

## Local socket

Is inserted into the filesystem.
