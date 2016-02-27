/*
Server that reads a message up to a newline from a client.

Reply by incrementing each byte by one (ROT-1 cypher), newline terminated.

Close connection.

Loop.

Usage:

    ./server [<port>]

Default port: 12345

If a second client comes while the first one is talking, it hangs until the first one stops.

A forking server is the way to solve this.
*/

#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
	char buffer[BUFSIZ];
	char protoname[] = "tcp";
	struct protoent *protoent;
    int enable = 1;
    int i;
    int newline_found = 0;
    int server_sockfd, client_sockfd;
    socklen_t client_len;
    ssize_t nbytes_read;
    struct sockaddr_in client_address, server_address;
    unsigned short server_port = 12345u;

    if (argc > 1) {
        server_port = strtol(argv[1], NULL, 10);
    }

	protoent = getprotobyname(protoname);
	if (protoent == NULL) {
        perror("getprotobyname");
        exit(EXIT_FAILURE);
	}

    server_sockfd = socket(
        AF_INET,
        SOCK_STREAM,
        protoent->p_proto
        /* 0 */
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
    server_address.sin_port = htons(server_port);
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
    fprintf(stderr, "listening on port %d\n", server_port);

    while (1) {
        client_len = sizeof(client_address);
        client_sockfd = accept(
            server_sockfd,
            (struct sockaddr*)&client_address,
            &client_len
        );
        while ((nbytes_read = read(client_sockfd, buffer, BUFSIZ)) > 0) {
            printf("received:\n");
            write(STDOUT_FILENO, buffer, nbytes_read);
            if (buffer[nbytes_read - 1] == '\n')
                newline_found;
            for (i = 0; i < nbytes_read - 1; i++)
                buffer[i]++;
            write(client_sockfd, buffer, nbytes_read);
            if (newline_found)
                break;
        }
        close(client_sockfd);
    }
    return EXIT_SUCCESS;
}
