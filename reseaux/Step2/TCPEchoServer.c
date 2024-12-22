#include <stdio.h>      /* Bibliothèque pour les fonctions d'entrée/sortie comme printf() et fprintf() */
#include <sys/socket.h> /* Bibliothèque pour les fonctions de socket comme socket(), bind(), et connect() */
#include <arpa/inet.h>  /* Bibliothèque pour les structures sockaddr_in et inet_ntoa() */
#include <stdlib.h>     /* Bibliothèque pour atoi() (conversion chaîne → entier) et exit() */
#include <string.h>     /* Bibliothèque pour memset() et manipulation de chaînes */
#include <unistd.h>     /* Bibliothèque pour close() */

#define MAXPENDING 5    /* Nombre maximal de connexions en attente dans la file d'attente */

#include "LibSer.h"        /* Fichier d'en-tête pour les fonctions de gestion des erreurs */
#include "HandleTCPClient.h" /* Fichier d'en-tête pour la fonction de gestion des clients TCP */
#include "LibSerHV.h"      /* Fichier d'en-tête pour les fonctionnalités spécifiques à HV */

/* Fonction principale */
int main(int argc, char *argv[])
{
    int servSock;                    /* Descripteur de socket pour le serveur */
    int clntSock;                    /* Descripteur de socket pour le client */
    struct sockaddr_in echoServAddr; /* Adresse locale */
    struct sockaddr_in echoClntAddr; /* Adresse du client */
    unsigned short echoServPort;     /* Port du serveur */
    unsigned int clntLen;            /* Taille de la structure d'adresse du client */

    /* Vérifie que le nombre d'arguments est correct */
    if (argc != 2)
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]); /* Affiche la syntaxe correcte */
        exit(1); /* Quitte le programme avec un code d'erreur */
    }

    echoServPort = atoi(argv[1]);  /* Convertit le premier argument en un entier représentant le port local */

    /* Crée un socket pour les connexions entrantes */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed"); /* Affiche une erreur et quitte si la création du socket échoue */
    else
        printf("socket() Ok\n"); /* Indique que la création du socket a réussi */
      
    /* Initialise la structure d'adresse locale */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Met tous les champs à zéro */
    echoServAddr.sin_family = AF_INET;                /* Famille d'adresses Internet */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Accepte les connexions sur toutes les interfaces locales */
    echoServAddr.sin_port = htons(echoServPort);      /* Définit le port local en format réseau */

    /* Lie le socket à l'adresse locale */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed"); /* Quitte si le bind échoue */
    else
        printf("bind() Ok\n"); /* Indique que le bind a réussi */

    /* Met le socket en mode écoute pour accepter les connexions entrantes */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed"); /* Quitte si le listen échoue */
    else
        printf("listen() Ok\n"); /* Indique que le socket est prêt à écouter */

    /* Boucle infinie pour gérer les connexions */
    for (;;)
    {
        /* Détermine la taille de la structure d'adresse du client */
        clntLen = sizeof(echoClntAddr);

        /* Attend qu'un client se connecte */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, 
                               &clntLen)) < 0)
            DieWithError("accept() failed"); /* Quitte si l'acceptation échoue */
        else
            printf("accept() Ok\n"); /* Indique qu'une connexion a été acceptée */

        /* Affiche l'adresse IP du client connecté */
        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        /* Appelle la fonction pour gérer le client */
        HandleTCPClient(clntSock);
    }

    /* Le programme ne devrait jamais atteindre ce point */
    /* NOT REACHED */
}
