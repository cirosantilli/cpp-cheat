/*
Send a message up to a newline to the server.

Read a reply up to a newline and print it to stdout.

Loop.

Usage:

    ./client [<server-address> [<port>]]

Default ip: localhost.

Default port: 12345
*/

#define _XOPEN_SOURCE 700

#include <assert.h>
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
    char *server_hostname = "127.0.0.1";
    char *user_input = NULL;
    in_addr_t in_addr;
    in_addr_t server_addr;
    int sockfd;
    size_t getline_buffer = 0;
    ssize_t nbytes_read, i, user_input_len;
    struct hostent *hostent;
    /* This is the struct used by INet addresses. */
    struct sockaddr_in sockaddr_in;
    unsigned short server_port = 12345;

    if (argc > 1) {
        server_hostname = argv[1];
        if (argc > 2) {
            server_port = strtol(argv[2], NULL, 10);
        }
    }

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
    if (connect(sockfd, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
        perror("connect");
        return EXIT_FAILURE;
    }
    while (1) {
        fprintf(stderr, "enter string (empty to quit):\n");
        user_input_len = getline(&user_input, &getline_buffer, stdin);
        if (user_input_len == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }
        if (user_input_len == 1) {
            close(sockfd);
            break;
        }
        if (write(sockfd, user_input, user_input_len) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        while ((nbytes_read = read(sockfd, buffer, BUFSIZ)) > 0) {
            write(STDOUT_FILENO, buffer, nbytes_read);
            if (buffer[nbytes_read - 1] == '\n') {
                fflush(stdout);
                break;
            }
        }
    }
    free(user_input);

    exit(EXIT_SUCCESS);
}
