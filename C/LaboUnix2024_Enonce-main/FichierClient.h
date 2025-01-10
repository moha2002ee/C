#define FICHIER_UTILISATEURS "clients.dat"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
typedef struct 
{
    char nom[20];
    int mdpHash;
}CLIENT;

int ilEstDispo(const char *nom);
int hashMdp(const char *mdpHash);
int verifMDP(int position, const char *mdp);
int listClient(CLIENT *l);
void ajoutClient(const char* nom , const char *mdp);
