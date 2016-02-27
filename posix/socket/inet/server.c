/*
Run a simple server that:

- reads one character from a client
- increments it
- returns the incremented value
- closes the conection
*/

#define _XOPEN_SOURCE 700

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include "unistd.h"

#define DEBUG(msg) fprintf(stderr, "debug: " msg "\n")

int main(int argc, char **argv) {
    unsigned short server_port = 12345u;
    char ch;
    socklen_t client_len;
    int server_sockfd, client_sockfd;
    int enable = 1;
    struct sockaddr_in client_address, server_address;
	struct protoent *protoent;
	char protoname[] = "tcp";
    /*char protoname[] = "udp";*/

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

    /*
    # SO_REUSEADDR

        If we dind't use this, then:

        - bind here on the server,
        - connect once with a client
        - kill server
        - try to restart server
        - bind fails, because the connection still exists on TIME-WAIT

        This allows the bind to happen even it TIME-WAIT is going on.

        See also:

        - http://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr
        - http://serverfault.com/questions/329845/how-to-forcibly-close-a-socket-in-time-wait
        - http://stackoverflow.com/questions/10619952/how-to-completely-destroy-a-socket-connection-in-c
    */
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    /*
    #s_addr server

        on server, this is which addresses it will accept connections from

    #INADDR_ANY

        special ch that tells server to accept connections from anyone
    */
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

    while (1) {
        client_len = sizeof(client_address);
        DEBUG("accept");
        client_sockfd = accept(
            server_sockfd,
            (struct sockaddr*)&client_address,
            &client_len
        );
        DEBUG("read");
        read(client_sockfd, &ch, 1);
        printf("received: %c\n", ch);
        ch++;
        DEBUG("write");
        write(client_sockfd, &ch, 1);
        DEBUG("close");
        close(client_sockfd);
    }
    return EXIT_SUCCESS;
}
