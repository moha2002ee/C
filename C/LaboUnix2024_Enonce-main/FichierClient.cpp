#include "FichierClient.h"

int ilEstDispo(const char *nom)
{
    CLIENT u;
    int position = 0; 
    int fd;
    // j'ouvre le fichier en lecture 
    fd = open(FICHIER_UTILISATEURS, O_RDWR | O_CREAT, 0644);
    if (fd == -1) 
    {
        printf("Le fichier %s ne s'ouvre pas ", FICHIER_UTILISATEURS);
        return -1;
    }
    // je regarde s'il y a l'CLIENT 
    while (read(fd, &u, sizeof(u)) > 0) 
    {
        position++;
        if (strcmp(u.nom, nom) == 0) 
        {
            close(fd);
            return position;
        }
    }

    close(fd);
    return 0;
}

int hashMdp(const char *motDePasse)
{
    int longueur = strlen(motDePasse);
    int hash = 0;

    for (int i = 0; i < longueur; i++) 
    {
        hash += (i + 1) * motDePasse[i];
    }

    return hash % 97;
}

void ajoutClient(const char *nom, const char *motDePasse)
{
    int fd;
    CLIENT u;

    strncpy(u.nom, nom, sizeof(u.nom) - 1);
    u.nom[sizeof(u.nom) - 1] = '\0';
    u.mdpHash = hashMdp(motDePasse);

    fd = open(FICHIER_UTILISATEURS, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) 
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    if (write(fd, &u, sizeof(u)) == -1) 
    {
        perror("Erreur lors de l'écriture dans le fichier");
    }

    close(fd);
    printf("CLIENT '%s' ajouté avec succès.\n", nom);
}

int verifMDP(int pos, const char *motDePasse)
{
    int fd;
    CLIENT u;
    int hasher = hashMdp(motDePasse);

    fd = open(FICHIER_UTILISATEURS, O_RDONLY);
    if (fd == -1) 
    {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    if (lseek(fd, (pos - 1) * sizeof(CLIENT), SEEK_SET) == -1) 
    {
        perror("Erreur lors du déplacement dans le fichier");
        close(fd);
        return -1;
    }

    if (read(fd, &u, sizeof(CLIENT)) != sizeof(CLIENT)) 
    {
        perror("Erreur lors de la lecture de l'CLIENT");
        close(fd);
        return -1;
    }

    close(fd);

    if (u.mdpHash == hasher) 
    {
        return 1; 
    }
    else 
    {
        return 0; 
    }
}


int listClient(CLIENT *vecteur)
{
    int fd;
    int count = 0;
    CLIENT u;

    fd = open(FICHIER_UTILISATEURS, O_RDONLY);
    if (fd == -1) 
    {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    while (read(fd, &u, sizeof(CLIENT)) == sizeof(CLIENT)) 
    {
        vecteur[count] = u;
        count++;
    }

    close(fd);
    return count;
}
