#include <stdio.h>      /* Bibliothèque pour les fonctions d'entrée/sortie comme printf() et fprintf() */
#include <sys/socket.h> /* Bibliothèque pour les fonctions de socket comme socket(), bind(), et connect() */
#include <arpa/inet.h>  /* Bibliothèque pour sockaddr_in et inet_ntoa() */
#include <stdlib.h>     /* Bibliothèque pour atoi() (conversion chaîne → entier) et exit() */
#include <string.h>     /* Bibliothèque pour memset() */
#include <unistd.h>     /* Bibliothèque pour close() */

#define MAXPENDING 5    /* Nombre maximal de connexions en attente dans la file d'attente */

#include "LibSer.h"         /* Fichier d'en-tête pour les fonctions de gestion des erreurs */
#include "HandleTCPClient.h" /* Fichier d'en-tête pour la fonction de gestion des clients TCP */
#include "LibSerHV.h"       /* Fichier d'en-tête pour les fonctionnalités spécifiques à HV */

/* Fonction principale */
int main(int argc, char *argv[])
{
    int servSock;                    /* Descripteur de socket pour le serveur */
    int clntSock;                    /* Descripteur de socket pour le client */
    struct sockaddr_in echoServAddr; /* Structure contenant l'adresse locale */
    struct sockaddr_in echoClntAddr; /* Structure contenant l'adresse du client */
    unsigned short echoServPort;     /* Port du serveur */
    unsigned int clntLen;            /* Taille de la structure d'adresse du client */
    char *servIP;                    /* Adresse IP du serveur (en notation pointée) */
    char host[100];                  /* Nom d'hôte du client */
    char port[100];                  /* Numéro de port du client */

    /* Vérifie que le nombre d'arguments est correct */
    if (argc != 3)
    {
        fprintf(stderr, "Usage:  %s <Server IP> <Server Port>\n", argv[0]); /* Affiche la syntaxe correcte */
        exit(1); /* Quitte le programme avec un code d'erreur */
    }

    servIP = argv[1];                 /* Premier argument : adresse IP du serveur */
    echoServPort = atoi(argv[2]);     /* Deuxième argument : port du serveur */

    /* Crée un socket pour les connexions entrantes */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed"); /* Quitte si la création du socket échoue */
    else
        printf("socket() Ok\n"); /* Indique que la création du socket a réussi */
      
    /* Initialise la structure d'adresse locale */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Met tous les champs de la structure à zéro */
    echoServAddr.sin_family = AF_INET;                /* Famille d'adresses Internet (IPv4) */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP); /* Définit l'adresse IP du serveur */
    echoServAddr.sin_port = htons(echoServPort);      /* Définit le port local (conversion hôte → réseau) */

    /* Lie le socket à l'adresse locale */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed"); /* Quitte si l'association échoue */
    else
        printf("bind() Ok\n"); /* Indique que le bind a réussi */

    /* Met le socket en mode écoute */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed"); /* Quitte si listen() échoue */
    else
        printf("listen() Ok\n"); /* Indique que le socket est prêt à écouter */

    /* Boucle infinie pour gérer les connexions */
    for (;;)
    {
        /* Définit la taille de la structure d'adresse du client */
        clntLen = sizeof(echoClntAddr);

        /* Attend qu'un client se connecte */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
            DieWithError("accept() failed"); /* Quitte si accept() échoue */
        else
            printf("accept() Ok\n"); /* Indique qu'une connexion a été acceptée */

        /* Récupère des informations sur le client connecté */
        getpeername(servSock, (struct sockaddr*)&echoClntAddr, &clntLen); /* Récupère l'adresse et le port du client */
        getnameinfo((struct sockaddr*)&echoClntAddr, clntLen,
                    host, 10, /* Stocke le nom d'hôte dans le tableau `host` */
                    port, 10, /* Stocke le port dans le tableau `port` */
                    MAXPENDING); /* Indique les options pour la résolution */

        /* Affiche l'adresse IP et le port du client */
        printf("Client connecté --> Adresse IP: %s -- Port: %s\n", host, port);

        /* Affiche l'adresse IP du client sous forme de chaîne */
        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        /* Appelle la fonction pour gérer le client */
        HandleTCPClient(clntSock);
    }

    /* Code jamais atteint car le serveur tourne en boucle infinie */
    /* NOT REACHED */
}
