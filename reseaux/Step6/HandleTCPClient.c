#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include "LibSer.h"
#include "Requete.h"
#include "LibSerHV.h"
#include "data.h"
#define RCVBUFSIZE 32   /* Size of receive buffer */


void HandleTCPClient(int clntSocket)
{
    int recvMsgSize, res;                    /* Size of received message */
    struct Requete UneRequete ;
    struct VehiculeHV UnRecord;
    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, &UneRequete, sizeof (struct Requete), 0)) < 0)
        DieWithError("recv() failed");
    while(recvMsgSize>0) 
    {
         if((res = RechercheHV("VehiculesHV", UneRequete.Reference, &UnRecord)) == -1)
         {
            printf("Erreur vehicule pas trouve\n");
         }
         else{

            UneRequete.Reference = UnRecord.Reference;
            strcpy(UneRequete.Constructeur, UnRecord.Constructeur);
            strcpy(UneRequete.Modele, UnRecord.Modele);
            UneRequete.Quantite = UnRecord.Quantite;
            strcpy(UneRequete.Couleur, UnRecord.Couleur);
            UneRequete.Type = OK;
            printf("Res : reference : %d %s %s \n", UneRequete.Reference, UneRequete.Constructeur, UneRequete.Modele);
         }
         
    /* Echo message back to client */
    if (write(clntSocket, &UneRequete, recvMsgSize) != recvMsgSize)
            DieWithError("send() failed");
    
    /* See if there is more data to receive */
    if ((recvMsgSize = read(clntSocket, &UneRequete, sizeof (struct Requete))) < 0)
            DieWithError("recv() failed");
    }

    printf("Connexion Closed\n")  ;
    close(clntSocket);    /* Close client socket */
}
