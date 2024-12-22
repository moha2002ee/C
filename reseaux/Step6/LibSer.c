#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */
#include "LibSer.h"

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int ReservationHV(char* NomFichier,int Reference ,int Quantite )
{
    int fd;
    int nRef = 0;
    struct VehiculeHV UnRecord;
    fd = open(NomFichier, O_RDWR );
    if ( fd == -1 )
        {
         fprintf(stderr,"Echec Ouverture\n") ;
         exit(0) ;
        }
    else
    {
        fprintf(stderr,"Ouverture reussie VehiculeHV \n") ;
     
        fprintf(stderr,"ReservationHV>\n");
        
        while (Reference != UnRecord.Reference)
        {
          read(fd, &UnRecord, sizeof(struct VehiculeHV));
            if(Reference != nRef+1){
            fprintf(stderr, "Reference lue %d et Position actuelle dans le fichier %ld \n", nRef+1, lseek(fd, 0, SEEK_CUR));
            }
            nRef += 1;
        }
        fprintf(stderr,"ReservationHV<\n");
        
        fprintf(stderr, "%-4s %-30s %-30s %-10s %-10s\n", 
        "Ref", "Constructeur", "Modele", "Quantite", "Couleur");

        fprintf(stderr, "%-4d %-30s %-30s %-10d %-10s\n", UnRecord.Reference,UnRecord.Constructeur,
            UnRecord.Modele,UnRecord.Quantite,UnRecord.Couleur);
        printf("\n") ;
        UnRecord.Quantite -= Quantite;
        lseek(fd, -sizeof(struct VehiculeHV), SEEK_CUR);

        write(fd, &UnRecord, sizeof(struct VehiculeHV));
        printf("Record ecrit %d \n", Quantite);

        close(fd) ;
        return 1;
    }
    return -1;
}
int FacturationHV(char NomFichier[80], char NomClient[60], time_t Date,int Quantite,int Reference)
{
    int fd;
    int nbOctet = 0;
    struct FactureHV UnRecord, tmpRecord;

    fd = open(NomFichier, O_RDWR|O_APPEND);
    if ( fd == -1 )
        {
         fprintf(stderr,"Echec Ouverture\n") ;
         exit(0) ;
        }
    else
    {
     
        fprintf(stderr,"FacturationHV>\n");
        fprintf(stderr,"Ouverture reussie FacturationHV \n") ;
        lseek(fd, -sizeof(struct FactureHV), SEEK_END);
        nbOctet = read(fd, &tmpRecord, sizeof(struct FactureHV));
        if (nbOctet > 0) {
            UnRecord.NumeroFacturation = tmpRecord.NumeroFacturation + 1;
        } else {
            UnRecord.NumeroFacturation = 1;
        }
        strcpy(UnRecord.Acheteur, NomClient);
        UnRecord.DateFacturation = Date;
        UnRecord.Quantite = Quantite;
        UnRecord.Reference = Reference;

        write(fd, &UnRecord, sizeof(struct FactureHV));

        fprintf(stderr,"FacturationHV<\n");
        fprintf(stderr,"mise a jour FacturationHV reussie\n");
        close(fd) ;
        return 1;
    }
    return -1;
}