/*
Fetches a web page and print it to stdout.

example.com:

    wget

Given page:

    wget google.com

IP: TODO
*/

#define _XOPEN_SOURCE 700

#include "assert.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include "unistd.h"

int main(int argc, char** argv) {
    enum CONSTEXPR { MAX_REQUEST_LEN = 1024};
    char *hostname = "example.com";
    unsigned short server_port = 80;
	char request_template[] = "GET / HTTP/1.1\r\nHost: %s\r\n\r\n";
	char request[MAX_REQUEST_LEN];
    int request_len;
    in_addr_t in_addr;
    int socket_file_descriptor;
    struct sockaddr_in sockaddr_in;
	struct protoent *protoent;
	char buffer[BUFSIZ];
    struct hostent *hostent;
    ssize_t nbytes_total, nbytes_last;

    if (argc > 1)
        hostname = argv[1];

    request_len = snprintf(request, MAX_REQUEST_LEN, request_template, hostname);
    if (request_len >= MAX_REQUEST_LEN) {
        fprintf(stderr, "request length large: %d\n", request_len);
        exit(EXIT_FAILURE);
    }

    /* Build the socket. */
    protoent = getprotobyname("tcp");
    if (protoent == NULL) {
        perror("getprotobyname");
        exit(EXIT_FAILURE);
    }
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
    if (socket_file_descriptor == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Build the address. */
    hostent = gethostbyname(hostname);
    if (hostent == NULL) {
        fprintf(stderr, "error: gethostbyname(\"%s\")\n", hostname);
        exit(EXIT_FAILURE);
    }
    in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
    if (in_addr == (in_addr_t)-1) {
        fprintf(stderr, "error: inet_addr(\"%s\")\n", *(hostent->h_addr_list));
        exit(EXIT_FAILURE);
    }
    sockaddr_in.sin_addr.s_addr = in_addr;
    sockaddr_in.sin_family = AF_INET;
    sockaddr_in.sin_port = htons(server_port);

    /* Actually connect. */
    if (connect(socket_file_descriptor, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    /* Send HTTP request. */
    nbytes_total = 0;
    while (nbytes_total < request_len) {
        nbytes_last = write(socket_file_descriptor, request + nbytes_total, request_len - nbytes_total);
        if (nbytes_last == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        nbytes_total += nbytes_last;
    }

    /*
    Read the response. TODO: for example.com, the second read hangs for a few seconds.
    Why? Does the connection keep open until I close it? Must I parse the returned string to see if the HTTP response is over,
    and close it then?
    curl example.com does not lag at all.
    */
    while ((nbytes_total = read(socket_file_descriptor, buffer, BUFSIZ)) > 0) {
        write(STDOUT_FILENO, buffer, nbytes_total);
    }
    if (nbytes_total == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    close(socket_file_descriptor);
    exit(EXIT_SUCCESS);
}
