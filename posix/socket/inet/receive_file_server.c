/*
Receive a file over a socket.

Saves it to output.tmp by default.

Interface:

    ./executable [<output-file> [<port>]]

TODO factor out with other servers.
*/

#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char protoname[] = "tcp";
    char buffer[BUFSIZ];
    char *file_path = "output.tmp";
    struct protoent *protoent;
    int enable = 1;
    int i;
    int filefd;
    int client_sockfd;
    int server_sockfd;
    socklen_t client_len;
    ssize_t read_return;
    struct sockaddr_in client_address, server_address;
    unsigned short server_port = 12345u;

    if (argc > 1) {
        file_path = argv[1];
        if (argc > 2) {
            server_port = strtol(argv[2], NULL, 10);
        }
    }

    /* Listen. */
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
        filefd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        client_len = sizeof(client_address);
        puts("waiting for client");
        client_sockfd = accept(
            server_sockfd,
            (struct sockaddr*)&client_address,
            &client_len
        );
        do {
            read_return = read(client_sockfd, buffer, BUFSIZ);
            if (read_return == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            if (write(filefd, buffer, read_return) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        } while (read_return > 0);
        close(filefd);
        close(client_sockfd);
    }
    return EXIT_SUCCESS;
}
