#include "LibSerHV.h"

void AProposServeurHV(char *Version, char *Nom1, char *Nom2)
{
    printf("Version : %s \n", Version);
    printf("Nom1 : %s \n", Nom1);
    printf("Nom2 : %s \n", Nom2);
}

int RechercheHV(char *NomFichier, int Reference, struct VehiculeHV *UnRecord)
{
    int fd;
    int found = 0;
    off_t position;

    printf("RechercheHV>\n");

    // Ouvrir le fichier en mode lecture
    fd = open(NomFichier, O_RDONLY);
    if (fd == -1)
    {
        perror("Erreur ouverture fichier");
        return 0; // Échec d'ouverture
    }

    printf("Ouverture reussie %s\n", NomFichier);

    while (read(fd, UnRecord, sizeof(struct VehiculeHV)) > 0)
    {
        position = lseek(fd, 0, SEEK_CUR);
        printf("Reference lue %d et Position actuelle dans le fichier %ld\n", UnRecord->Reference, position);

        if (UnRecord->Reference == Reference)
        {
            found = 1;
            break;
        }
    }

    // Fermer le fichier
    close(fd);

    printf("RechercheHV<\n");

    return found;
}