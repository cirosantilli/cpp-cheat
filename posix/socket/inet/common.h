#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/* http://stackoverflow.com/questions/2064636/getting-the-source-address-of-an-incoming-socket-connection */
void print_client_address(int sockfd) {
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);
    char ipstr[INET6_ADDRSTRLEN];
    int port;

    getpeername(sockfd, (struct sockaddr*)&addr, &len);
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&addr;
        port = ntohs(s->sin_port);
        inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
    } else {
        /* AF_INET6 */
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
        port = ntohs(s->sin6_port);
        inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
    }
    printf("client connected from: %s:%d\n", ipstr, port);
    return;
}

/* Return a socket that is being listened on. */
int listen_port(char *protoname, unsigned int port) {
    int enable = 1;
    int server_sockfd;
    struct protoent *protoent;
    struct sockaddr_in server_address;

    protoent = getprotobyname(protoname);
    if (protoent == NULL) {
        perror("getprotobyname");
        exit(EXIT_FAILURE);
    }
    server_sockfd = socket(
        AF_INET,
        SOCK_STREAM,
        protoent->p_proto
    );
    if (server_sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);
    if (bind(
            server_sockfd,
            (struct sockaddr*)&server_address,
            sizeof(server_address)
        ) == -1
    ) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_sockfd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "listening on port %d\n", port);
    return server_sockfd;
}

/* Return the socket of a server. */
int connect_server(char *protoname, char *server_hostname, unsigned int port) {
	struct protoent *protoent;
    struct hostent *hostent;
    in_addr_t in_addr;
    struct sockaddr_in sockaddr_in;
    int sockfd;
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
    sockaddr_in.sin_port = htons(port);
    /* Do the actual connection. */
    if (connect(sockfd, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
        perror("connect");
        return EXIT_FAILURE;
    }
    return sockfd;
}

#endif
