#include "LibSerHV.h"
 
void AProposServeurHV(char *Version,char *Nom1,char* Nom2)
{
printf("Version : %s \n",Version ) ;
printf("Nom1 : %s \n",Nom1 ) ;
printf("Nom2 : %s \n",Nom2 ) ;
}

int RechercheHV(char* NomFichier,int Reference ,struct VehiculeHV *UnRecord)
{
 
    int fd;
    int nRef = 0;

    fd = open(NomFichier, O_RDONLY );
    if ( fd == -1 )
        {
         fprintf(stderr,"Echec Ouverture\n") ;
         exit(0) ;
        }
    else
    {
        fprintf(stderr,"RechercheHV>\n");
        fprintf(stderr,"Ouverture reussie VehiculeHV \n") ;
     
        
        
        while (Reference != UnRecord->Reference)
        {
          read(fd, UnRecord, sizeof(struct VehiculeHV));
            if(Reference != nRef+1){
            fprintf(stderr, "Reference lue %d et Position actuelle dans le fichier %ld \n", nRef+1, lseek(fd, 0, SEEK_CUR));
            }
            nRef += 1;
        }
        fprintf(stderr,"RechercheHV<\n");
        
        fprintf(stderr, "%-4s %-30s %-30s %-10s %-10s\n", 
        "Ref", "Constructeur", "Modele", "Quantite", "Couleur");

    	fprintf(stderr, "%-4d %-30s %-30s %-10d %-10s\n", UnRecord->Reference,UnRecord->Constructeur,
    		UnRecord->Modele,UnRecord->Quantite,UnRecord->Couleur);
     	printf("\n") ;
        close(fd) ;
        return 1;
    }
    return -1;

}


