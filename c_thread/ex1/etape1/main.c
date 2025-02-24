#include <stdio.h>  // Inclusion des bibliothèques nécessaires
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define MOT_CIBLE "maison"  // Mot que l'on cherche dans le fichier
#define LONGUEUR_MOT 6       // Longueur du mot cible
#define CHEMIN_FICHIER "text1.txt"  // Nom du fichier à analyser

// Fonction exécutée par le thread pour compter les occurrences du mot cible
void* compter_occurrences(void* arg) {
    int compteur = 0;  // Initialise le compteur d'occurrences
    char tampon[LONGUEUR_MOT + 1];  // Tampon pour stocker les caractères lus
    
    // Ouvre le fichier en mode lecture seule
    int fichier = open(CHEMIN_FICHIER, O_RDONLY);
    if (fichier == -1) {  // Vérifie si l'ouverture du fichier a échoué
        perror("Erreur lors de l'ouverture du fichier");
        pthread_exit(NULL);  
    }

    ssize_t octets_lus;
    // Boucle pour lire le fichier par morceaux de la taille du mot cible
    while ((octets_lus = read(fichier, tampon, LONGUEUR_MOT)) == LONGUEUR_MOT) {
      tampon[LONGUEUR_MOT] = '\0';  // Ajoute un caractère de fin de chaîne
        if (strcmp(tampon, MOT_CIBLE) == 0) {  // Compare avec le mot cible
            compteur++;  // Incrémente le compteur si une occurrence est trouvée
        }
        // Reculer de (LONGUEUR_MOT - 1) caractères pour ne pas sauter des possibilités
        lseek(fichier, -LONGUEUR_MOT + 1, SEEK_CUR);
    }

    close(fichier);  // Ferme le fichier après lecture

    // Alloue dynamiquement la mémoire pour stocker le résultat
    int* resultat = (int*)malloc(sizeof(int));
    if (resultat == NULL) {  // Vérifie si l'allocation a échoué
        perror("Erreur d'allocation mémoire");
        pthread_exit(NULL);
    }
    *resultat = compteur;  // Stocke le résultat dans la mémoire allouée
    pthread_exit(resultat);  // Retourne le résultat via pthread_exit
}

int main() {
    pthread_t thread;  // Déclare un thread
    int* resultat;  // Pointeur pour récupérer le résultat du thread

    // Création du thread qui exécute la fonction compter_occurrences
    if (pthread_create(&thread, NULL, compter_occurrences, NULL) != 0) {
        perror("Erreur lors de la création du thread");
        return 1;
    }

    // Attend que le thread termine et récupère le résultat
    if (pthread_join(thread, (void**)&resultat) != 0) {
        perror("Erreur lors de la jointure du thread");
        return 1;
    }

    // Affiche le nombre d'occurrences trouvé
    printf("\nNombre d'occurrences : %d\n", *resultat);
    free(resultat);  // Libère la mémoire allouée dynamiquement

    return 0;  // Indique que le programme s'est terminé avec succès
}
