#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>  // Pour open, O_RDONLY
#include <unistd.h> // Pour read, lseek, close

#include <time.h>
#include "data.h"

void AProposServeurHV(char *Version, char *Nom1, char *Nom2);
int RechercheHV(char *NomFichier, int Reference, struct VehiculeHV *UnRecord);
