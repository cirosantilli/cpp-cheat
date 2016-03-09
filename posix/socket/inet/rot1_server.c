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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/* http://stackoverflow.com/questions/2064636/getting-the-source-address-of-an-incoming-socket-connection */
void print_client_address(int sockfd) {
    socklen_t len;
    struct sockaddr_storage addr;
    char ipstr[INET6_ADDRSTRLEN];
    int port;

    len = sizeof addr;
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

int main(int argc, char **argv) {
    FILE *client_sockf;
    char *client_input;
    char protoname[] = "tcp";
    struct protoent *protoent;
    int enable = 1;
    int i;
    int client_sockfd;
    int client_input_len;
    int server_sockfd;
    socklen_t client_len;
    ssize_t nbytes_read;
    size_t client_input_getline_size;
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
        puts("waiting for client");
        client_sockfd = accept(
            server_sockfd,
            (struct sockaddr*)&client_address,
            &client_len
        );
        print_client_address(client_sockfd);
        client_sockf = fdopen(client_sockfd, "r");
        do {
            client_input_len = getline(&client_input, &client_input_getline_size, client_sockf);
            puts("received:");
            printf("%s", client_input);
            for (i = 0; i < client_input_len - 1; i++)
                client_input[i]++;
            printf("%s", client_input);
            write(client_sockfd, client_input, client_input_len);
            puts("");
        } while (client_input_len != -1);
        close(client_sockfd);
    }
    return EXIT_SUCCESS;
}
