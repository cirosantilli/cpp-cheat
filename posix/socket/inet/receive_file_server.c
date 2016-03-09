/*
Receive a file over a socket.

Saves it to output.tmp by default.

Interface:

    ./executable [<output_file> [<port>]]

Defaults:

- output_file: output.tmp
- port: 12345
*/

#define _XOPEN_SOURCE 700

#include <stdio.h> /* printf, puts, getline */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */

#include <fcntl.h> /* open, close */

#include "common.h"

int main(int argc, char **argv) {
    char *file_path = "output.tmp";
    char buffer[BUFSIZ];
    char protoname[] = "tcp";
    int client_sockfd;
    int filefd;
    int server_sockfd;
    socklen_t client_len;
    ssize_t read_return;
    struct sockaddr_in client_address;
    unsigned short server_port = 12345u;

    if (argc > 1) {
        file_path = argv[1];
        if (argc > 2) {
            server_port = strtol(argv[2], NULL, 10);
        }
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
        print_client_address(client_sockfd);
        filefd = open(file_path,
                O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        while (1) {
            read_return = read(client_sockfd, buffer, BUFSIZ);
            if (read_return == 0)
                break;
            if (read_return == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            if (write(filefd, buffer, read_return) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
        close(filefd);
        close(client_sockfd);
    }
    close(server_sockfd);
    return EXIT_SUCCESS;
}
