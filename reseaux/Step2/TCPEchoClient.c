#include <stdio.h>      /* Bibliothèque pour les fonctions d'entrée/sortie comme printf() et fprintf() */
#include <sys/socket.h> /* Bibliothèque pour les fonctions de socket comme socket(), connect(), send(), et recv() */
#include <arpa/inet.h>  /* Bibliothèque pour les structures sockaddr_in et inet_addr() */
#include <stdlib.h>     /* Bibliothèque pour atoi() (conversion chaîne → entier) et exit() */
#include <string.h>     /* Bibliothèque pour memset() et manipulation de chaînes */
#include <unistd.h>     /* Bibliothèque pour close() */
#include "Requete.h"    /* Fichier d'en-tête contenant la définition de la structure Requete (non fourni ici) */

#define RCVBUFSIZE 32   /* Taille du tampon de réception */

/* Fonction pour afficher un message d'erreur et quitter le programme */
void DieWithError(char *errorMessage)
{
    perror(errorMessage); /* Affiche le message d'erreur avec la description du dernier appel système */
    exit(1);              /* Quitte le programme avec un code d'erreur */
}

int main(int argc, char *argv[])
{
    int sock;                        /* Descripteur de socket */
    struct sockaddr_in echoServAddr; /* Structure contenant l'adresse du serveur */
    unsigned short echoServPort;     /* Port du serveur */
    char *servIP;                    /* Adresse IP du serveur (format "dotted quad") */
    int numero;                      /* Référence saisie par l'utilisateur */

    struct Requete UneRequete;       /* Structure pour envoyer des données au serveur */

    /* Vérifie que le programme a été appelé avec le bon nombre d'arguments */
    if ((argc < 3) || (argc > 3))
    {
       fprintf(stderr, "Usage: %s <Server IP> <Echo Port>] <Echo Word> \n",
               argv[0]);             /* Affiche la bonne syntaxe en cas d'erreur */
       exit(1);                      /* Quitte le programme avec un code d'erreur */
    }

    servIP = argv[1];                /* Premier argument : adresse IP du serveur */
    echoServPort = atoi(argv[2]);    /* Deuxième argument : port du serveur (converti en entier) */
    printf("Saisir la reference:");  /* Invite l'utilisateur à saisir une référence */
    scanf("%d", &numero);            /* Lecture de la référence saisie */

    /* Initialisation des champs de la structure Requete */
    UneRequete.Reference = numero;  /* Stocke la référence saisie */
    UneRequete.Type = Question;     /* Définit le type de requête (valeur définie dans Requete.h) */
    UneRequete.NumeroFacture = 0;   /* Initialise le numéro de facture à 0 */
    strcpy(UneRequete.NomClient, ""); /* Vide le champ NomClient */

    /* Crée un socket TCP fiable */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed"); /* Quitte si la création du socket échoue */

    /* Initialise la structure d'adresse du serveur */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Met tous les champs à zéro */
    echoServAddr.sin_family      = AF_INET;             /* Famille d'adresses Internet */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Adresse IP du serveur */
    echoServAddr.sin_port        = htons(echoServPort); /* Port du serveur (converti en format réseau) */

    /* Établit une connexion avec le serveur */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed"); /* Quitte si la connexion échoue */

    /* Envoie la structure Requete au serveur */
    if (write(sock, &UneRequete, sizeof(struct Requete)) != sizeof(struct Requete))
        DieWithError("send() sent a different number of bytes than expected"); /* Erreur si les octets envoyés diffèrent */

    /* Reçoit la structure modifiée par le serveur */
    printf("Received: "); /* Prépare à afficher les données reçues */
    
    if ((read(sock, &UneRequete, sizeof(struct Requete))) <= 0)
            DieWithError("recv() failed or connection closed prematurely"); /* Vérifie les erreurs de réception */
    
    /* Affiche les détails de la structure reçue */
    AfficheRequete(stderr, UneRequete); /* Appelle une fonction (non définie ici) pour afficher la structure */
    printf("Constructeur, Modele: %s, %s", UneRequete.Constructeur, UneRequete.Modele); /* Affiche le constructeur et le modèle */
    printf("\n"); /* Ajoute une ligne vide après l'affichage */

    close(sock); /* Ferme la connexion */
    exit(0);     /* Termine le programme avec succès */
}
