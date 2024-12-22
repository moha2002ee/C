#include <stdio.h>      /* for printf() and fprintf() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <sys/socket.h> /* for socket(), bind(), and listen() */
#include <netdb.h>      /* for getaddrinfo() */
#include <arpa/inet.h>  /* for inet_ntoa() */

#include "LibSer.h"     /* Error handling function */
#include "HandleTCPClient.h"   /* TCP client handling function */
#include "LibSerHV.h"

#define MAXPENDING 5    /* Maximum outstanding connection requests */

int main(int argc, char *argv[]) {
    int servSock, clntSock;           /* Socket descriptors */
    struct addrinfo hints, *res;     /* For getaddrinfo */
    struct sockaddr_storage clntAddr; /* Client address (generic storage) */
    socklen_t clntAddrLen = sizeof(clntAddr); /* Length of client address */
    char host[NI_MAXHOST], port[NI_MAXSERV];  /* Host and port strings */
    int status;

    if (argc != 3) { /* Test for correct number of arguments */
        fprintf(stderr, "Usage: %s <Server IP> <Server Port>\n", argv[0]);
        exit(1);
    }

    const char *servIP = argv[1];  /* Server IP address (or hostname) */
    const char *servPort = argv[2]; /* Server port */

    /* Initialize hints for getaddrinfo */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;      /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* TCP socket */
    hints.ai_flags = AI_PASSIVE;     /* Use the specified IP */

    /* Resolve the address and port */
    if ((status = getaddrinfo(servIP, servPort, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    /* Create socket */
    if ((servSock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
        DieWithError("socket() failed");
    else
        printf("socket() Ok\n");

    /* Bind socket to the resolved address */
    if (bind(servSock, res->ai_addr, res->ai_addrlen) < 0)
        DieWithError("bind() failed");
    else
        printf("bind() Ok\n");

    /* Listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");
    else
        printf("listen() Ok\n");

    /* Free the address info structure */
    freeaddrinfo(res);

    for (;;) { /* Run forever */
        /* Accept a client connection */
        if ((clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntAddrLen)) < 0)
            DieWithError("accept() failed");
        else
            printf("accept() Ok\n");

        /* Retrieve and display client information */
        if (getnameinfo((struct sockaddr *)&clntAddr, clntAddrLen,
                        host, sizeof(host), port, sizeof(port),
                        NI_NUMERICHOST | NI_NUMERICSERV) == 0) {
            printf("Client connected --> Address: %s, Port: %s\n", host, port);
        } else {
            printf("Unable to retrieve client information.\n");
        }

        /* Handle the client connection */
        HandleTCPClient(clntSock);
    }

    /* NOT REACHED */
    close(servSock);
    return 0;
}
