/*
Send a message up to a newline to a server.

Read a reply up to a newline and print it to stdout.

Loop.

Usage:

    ./executable [<server-address> [<port>]]

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

#include "common.h"

int main(int argc, char **argv) {
	char protoname[] = "tcp";
    FILE *sockf;
    char *server_hostname = "127.0.0.1";
    char *server_reply = NULL;
    char *user_input = NULL;
    int sockfd;
    size_t server_reply_getline_size = 0;
    size_t user_input_getline_size = 0;
    ssize_t user_input_len;
    unsigned short server_port = 12345;

    if (argc > 1) {
        server_hostname = argv[1];
        if (argc > 2) {
            server_port = strtol(argv[2], NULL, 10);
        }
    }
    sockfd = connect_server(protoname, server_hostname, server_port);
    sockf = fdopen(sockfd, "r");
    while (1) {
        fprintf(stderr, "enter string (empty to quit):\n");
        user_input_len = getline(&user_input, &user_input_getline_size, stdin);
        if (user_input_len == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }
        if (user_input_len == 1) {
            puts("close");
            close(sockfd);
            break;
        }
        if (write(sockfd, user_input, user_input_len) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        user_input_len = getline(&server_reply, &server_reply_getline_size, sockf);
        if (user_input_len == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }
        puts(server_reply);
    }
    free(user_input);
    free(server_reply);
    return EXIT_SUCCESS;
}
