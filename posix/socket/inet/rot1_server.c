/*
Server that reads a message up to a newline from a client.

Reply by incrementing each byte by one (ROT-1 cypher), newline terminated.

Close connection.

Loop.

Usage:

    ./executable [<port>]

Default port: 12345

If a second client comes while the first one is talking, it hangs until the first one stops.

A forking server is the way to solve this.
*/

#define _XOPEN_SOURCE 700

#include <stdio.h> /* printf, puts, getline */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */

#include "common.h"

int main(int argc, char **argv) {
    FILE *client_sockf;
    char *client_input = NULL;
    char protoname[] = "tcp";
    int client_input_len;
    int client_sockfd;
    int i;
    int server_sockfd;
    size_t client_input_getline_size = 0;
    socklen_t client_len;
    struct sockaddr_in client_address;
    unsigned short server_port = 12345u;

    if (argc > 1) {
        server_port = strtol(argv[1], NULL, 10);
    }
    server_sockfd = listen_port(protoname, server_port);
    while (1) {
        client_len = sizeof(client_address);
        puts("waiting for client");
        client_sockfd = accept(
            server_sockfd,
            (struct sockaddr*)&client_address,
            &client_len
        );
        if (client_sockfd < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        print_client_address(client_sockfd);
        client_sockf = fdopen(client_sockfd, "r");
        while (1) {
            client_input_len = getline(&client_input, &client_input_getline_size, client_sockf);
            if (client_input_len == -1)
                break;
            puts("received:");
            printf("%s", client_input);
            for (i = 0; i < client_input_len - 1; i++)
                client_input[i]++;
            printf("%s", client_input);
            write(client_sockfd, client_input, client_input_len);
            puts("");
        }
        close(client_sockfd);
    }
    close(server_sockfd);
    return EXIT_SUCCESS;
}
