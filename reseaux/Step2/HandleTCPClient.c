#include <stdio.h>      /* Bibliothèque pour les fonctions d'entrée/sortie comme printf() et fprintf() */
#include <sys/socket.h> /* Bibliothèque pour les fonctions liées aux sockets comme recv() et send() */
#include <unistd.h>     /* Bibliothèque pour les fonctions de gestion de fichiers et de processus comme close() */
#include <string.h>     /* Bibliothèque pour manipuler les chaînes de caractères */
#include "LibSer.h"     /* Bibliothèque utilisateur pour les fonctionnalités spécifiques (non fournie ici) */
#include "Requete.h"    /* Fichier d'en-tête contenant la définition de la structure Requete (non fourni ici) */
#include "LibSerHV.h"   /* Bibliothèque utilisateur pour gérer les véhicules HV (non fournie ici) */
#include "data.h"       /* Fichier contenant probablement des données ou des constantes globales */
#define RCVBUFSIZE 32   /* Définition de la taille du tampon de réception */

/* Fonction pour gérer un client TCP connecté */
void HandleTCPClient(int clntSocket)
{
    int recvMsgSize, res;                    /* Variables pour la taille des messages reçus et le résultat des opérations */
    struct Requete UneRequete;              /* Structure pour stocker les données reçues du client */
    struct VehiculeHV UnRecord;             /* Structure pour stocker les informations du véhicule correspondant */

    /* Réception d'un message du client */
    if ((recvMsgSize = recv(clntSocket, &UneRequete, sizeof(struct Requete), 0)) < 0)
        DieWithError("recv() failed");      /* Si la réception échoue, afficher une erreur et quitter */
    
    /* Boucle pour traiter les données tant qu'il y a des messages reçus */
    while (recvMsgSize > 0) 
    {
        /* Recherche d'un véhicule dans la base de données */
        if ((res = RechercheHV("VehiculesHV", UneRequete.Reference, &UnRecord)) == -1)
        {
            printf("Erreur vehicule pas trouve\n");  /* Afficher une erreur si le véhicule n'est pas trouvé */
        }
        else
        {
            /* Mise à jour de la structure Requete avec les informations trouvées */
            UneRequete.Reference = UnRecord.Reference;
            strcpy(UneRequete.Constructeur, UnRecord.Constructeur);
            strcpy(UneRequete.Modele, UnRecord.Modele);
            UneRequete.Quantite = UnRecord.Quantite;
            strcpy(UneRequete.Couleur, UnRecord.Couleur);
            UneRequete.Type = OK;  /* Marquer la requête comme réussie */
            printf("Res : reference : %d %s %s \n", 
                UneRequete.Reference, UneRequete.Constructeur, UneRequete.Modele); /* Afficher les détails */
        }

        /* Réenvoyer la réponse au client */
        if (write(clntSocket, &UneRequete, recvMsgSize) != recvMsgSize)
            DieWithError("send() failed");  /* Si l'envoi échoue, afficher une erreur et quitter */

        /* Vérifier si d'autres données sont disponibles à recevoir */
        if ((recvMsgSize = read(clntSocket, &UneRequete, sizeof(struct Requete))) < 0)
            DieWithError("recv() failed"); /* Si la réception échoue, afficher une erreur et quitter */
    }

    printf("Connexion Closed\n"); /* Afficher un message lorsque la connexion est terminée */
    close(clntSocket);            /* Fermer le socket du client */
}
