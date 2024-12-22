#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
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
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    int numero;

    struct Requete UneRequete;

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
        /* Create a reliable, stream socket using TCP */
        if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            DieWithError("socket() failed");

        /* Construct the server address structure */
        memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
        echoServAddr.sin_family      = AF_INET;             /* Internet address family */
        echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
        echoServAddr.sin_port        = htons(echoServPort); /* Server port */

        /* Establish the connection to the echo server */
        if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
            DieWithError("connect() failed");


        /* Send the string to the server */
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
        case 2:
        exit(0);
    }
}
