/*
Send a file over a socket.

Interface:

    ./executable [<input_path> [<sever_hostname> [<port>]]]

Defaults:

- input_path: input.tmp
- server_hostname: 127.0.0.1
- port: 12345
*/

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>

#include "common.h"

int main(int argc, char **argv) {
	char protoname[] = "tcp";
    char *file_path = "input.tmp";
    char *server_hostname = "127.0.0.1";
    char *server_reply = NULL;
    char *user_input = NULL;
    char buffer[BUFSIZ];
    int filefd;
    int sockfd;
    ssize_t read_return;
    unsigned short server_port = 12345;

    if (argc > 1) {
        file_path = argv[1];
        if (argc > 2) {
            server_hostname = argv[2];
            if (argc > 3) {
                server_port = strtol(argv[3], NULL, 10);
            }
        }
    }
    filefd = open(file_path, O_RDONLY);
    if (filefd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    sockfd = connect_server(protoname, server_hostname, server_port);
    while (1) {
        read_return = read(filefd, buffer, BUFSIZ);
        if (read_return == 0)
            break;
        if (read_return == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (write(sockfd, buffer, read_return) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
    free(user_input);
    free(server_reply);
    close(filefd);
    exit(EXIT_SUCCESS);
}
