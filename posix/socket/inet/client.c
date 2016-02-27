/*
Send a single character to the server, then read a single character as reply, and exit.

Usage:

    ./client [[<ip>] <character>]

Default ip: localhost.

Default character: 'a'

Sample:

    ./client 192.168.0.2 b
*/

#define _XOPEN_SOURCE 700

#include "assert.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include "unistd.h"

#define DEBUG(msg) fprintf(stderr, "debug: " msg "\n")

int main(int argc, char **argv) {
    char *server_hostname = "127.0.0.1";
    unsigned short server_port = 12345;
    in_addr_t server_addr;
    int sockfd;
    /* This is the struct used by INet addresses. */
    struct sockaddr_in sockaddr_in;
    char ch_init = 'a';
    char ch;
	struct protoent *protoent;
	char protoname[] = "tcp";
    /*char protoname[] = "udp";*/
    struct hostent *hostent;
    in_addr_t in_addr;

    if (argc > 1) {
        server_hostname = argv[1];
        if (argc > 2) {
            ch_init = argv[2][0];
        }
    }
    ch = ch_init;

    /* Get socket. */
	protoent = getprotobyname(protoname);
	if (protoent == NULL) {
        perror("getprotobyname");
        exit(EXIT_FAILURE);
	}
    sockfd = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Prepare sockaddr_in. */
    hostent = gethostbyname(server_hostname);
    if (hostent == NULL) {
        fprintf(stderr, "error: gethostbyname(\"%s\")\n", server_hostname);
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

    /* Do the actual connection. */
    DEBUG("connect");
    if (connect(sockfd, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
        perror("connect");
        return EXIT_FAILURE;
    }
    DEBUG("write");
    if (write(sockfd, &ch, 1) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    /*
    According to wireshark, the response is received
    from some random port that the OS assigns to us.
    */
    DEBUG("read");
    if (read(sockfd, &ch, 1) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("received: %c\n", ch);
    DEBUG("close");
    close(sockfd);
    assert(ch == ch_init + 1);
    exit(EXIT_SUCCESS);
}
