#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include "LibSer.h"
#include "Requete.h"
#include "LibSerHV.h"
#include "data.h"
#define RCVBUFSIZE 32 /* Size of receive buffer */

void HandleTCPClient(int clntSocket)
{
    struct Requete uneRequeteR; // Requête reçue
    struct Requete uneRequeteE; // Requête envoyée
    struct VehiculeHV UnRecord; // Structure utilisée pour la recherche
    int rc;

    // Réception initiale de la requête
    if ((rc = recv(clntSocket, &uneRequeteR, sizeof(uneRequeteR), 0)) <= 0)
    {
        perror("recv() failed");
        close(clntSocket);
        return;
    }

    printf("Bytes received: %d\n", rc);
    AfficheRequete(stderr, uneRequeteR);

    // Boucle pour traiter les requêtes
    while (rc > 0)
    {
        // Gestion des différents types de requêtes
        switch (uneRequeteR.Type)
        {
        case Question:
            // Rechercher un véhicule dans "VehiculesHV"
            rc = RechercheHV("VehiculesHV", uneRequeteR.Reference, &UnRecord);
            fprintf(stderr, "res : %d Reference : %s %s\n", rc, UnRecord.Constructeur, UnRecord.Modele);

            // Préparer la réponse
            memset(&uneRequeteE, 0, sizeof(struct Requete));
            if (rc == 1)
            {
                // Si trouvé, remplir les champs de la réponse
                uneRequeteE.Reference = uneRequeteR.Reference;
                strncpy(uneRequeteE.Constructeur, UnRecord.Constructeur, sizeof(uneRequeteE.Constructeur));
                strncpy(uneRequeteE.Modele, UnRecord.Modele, sizeof(uneRequeteE.Modele));
                uneRequeteE.Type = OK;
            }
            else
            {
                // Si non trouvé
                uneRequeteE.Type = Fail;
            }

            // Envoyer la réponse au client
            rc = send(clntSocket, &uneRequeteE, sizeof(struct Requete), 0);
            if (rc == -1)
            {
                perror("SendDatagram:");
            }
            else
            {
                printf("Bytes written: %d\n", rc);
            }
            break;

        default:
            fprintf(stderr, "Code incorrect %d\n", uneRequeteR.Type);
            break;
        }

        // Réception de la prochaine requête
        if ((rc = recv(clntSocket, &uneRequeteR, sizeof(struct Requete), 0)) < 0)
        {
            DieWithError("recv() failed");
        }
        else if (rc > 0)
        {
            printf("Bytes received: %d\n", rc);
            AfficheRequete(stderr, uneRequeteR);
        }
        else
        {
            printf("Fermeture de connexion\n");
        }
    }

    close(clntSocket);
}