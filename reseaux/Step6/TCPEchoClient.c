#include <stdio.h>      /* for printf() and fprintf() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <netdb.h>      /* for getaddrinfo() */
#include "Requete.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
} 

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct addrinfo hints, *res;     /* For getaddrinfo */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    int numero;

    struct Requete UneRequete;
    int status;

    if ((argc < 3) || (argc > 3))    /* Test for correct number of arguments */
    {
       fprintf(stderr, "Usage: %s <Server IP> <Echo Port> \n",
               argv[0]);
       exit(1);
    }

    servIP = argv[1];             /* First arg: server IP address (dotted quad) */
    echoServPort = atoi(argv[2]);   /* Second arg: server Port */

    printf("(1) Faire une Recherche\n");
    printf("(2) Exit\n");
    scanf("%d", &numero);
    switch(numero)
    {
        case 1:
            printf("Saisir la reference:");
            scanf("%d", &numero);
            UneRequete.Reference = numero;
            UneRequete.Type = Question;
            UneRequete.NumeroFacture = 0;
            strcpy(UneRequete.NomClient, "");

            /* Initialize hints for getaddrinfo */
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_UNSPEC;      /* Allow IPv4 or IPv6 */
            hints.ai_socktype = SOCK_STREAM; /* TCP socket */
            
            /* Resolve the address and port */
            if ((status = getaddrinfo(servIP, argv[2], &hints, &res)) != 0) {
                fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
                exit(1);
            }

            /* Create socket */
            if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
                DieWithError("socket() failed");

            /* Establish the connection to the server */
            if (connect(sock, res->ai_addr, res->ai_addrlen) < 0)
                DieWithError("connect() failed");

            /* Send the structure to the server */
            ssize_t bytesSent = write(sock, &UneRequete, sizeof(struct Requete));
            if (bytesSent != sizeof(struct Requete))
                DieWithError("send() sent a different number of bytes than expected");

            printf("Bytes sent: %ld\n", bytesSent);

            /* Receive the same structure back from the server */
            printf("Received: ");                /* Setup to print the echoed string */

            ssize_t bytesReceived = read(sock, &UneRequete, sizeof(struct Requete));
            if (bytesReceived <= 0)
                DieWithError("recv() failed or connection closed prematurely");

            printf("Bytes received: %ld\n", bytesReceived);

            AfficheRequete(stderr, UneRequete);
            printf("Constructeur, Modele: %s, %s", UneRequete.Constructeur, UneRequete.Modele);
            printf("\n");                         /* Print a final linefeed */

            close(sock);
            break;

        case 2:
            exit(0);
            break;
    }
}
