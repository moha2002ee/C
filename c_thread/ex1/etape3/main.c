#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
    char nomFichier[40];    // Nom du fichier
    char motRecherche[40];  // Mot à rechercher
} ParametresThread;

// Fonction que chaque thread va exécuter
void* fonction(void *p);

int main(void)
{
    pthread_t threads[4]; // Tableau pour stocker les threads
    int* resultats[4];    // Tableau pour stocker les résultats de chaque thread

    // Paramètres pour chaque thread : fichier et mot à rechercher
    ParametresThread parametres[4] = {
        { "text1.txt", "plage" }, 
        { "text1.txt", "maison" },     
        { "text1.txt", "voiture" },       
        { "text1.txt", "video" }       
    };

    // Créer les threads
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, fonction, &parametres[i]);
    }

    // Attendre que tous les threads finissent et récupérer leurs résultats
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], (void**) &resultats[i]);
    }

    // Afficher les résultats
    printf("\nRésultats :\n");
    for (int i = 0; i < 4; i++) {
        printf("Thread %d (%s, \"%s\"): %d occurrences\n", i + 1, parametres[i].nomFichier, parametres[i].motRecherche, *resultats[i]);
        free(resultats[i]); // Libérer la mémoire allouée
    }

    return 0;
}

// Fonction qui va compter les occurrences du mot dans le fichier
void* fonction(void *p)
{
    ParametresThread *parametre = (ParametresThread*) p; // Récupérer les paramètres
    int *compteur = (int*)malloc(sizeof(int)); // Créer une variable pour stocker le nombre d'occurrences
    *compteur = 0; // Initialiser à 0

    // Ouvrir le fichier
    int fichier = open(parametre->nomFichier, O_RDONLY);
    if (fichier == -1) {
        perror("Erreur d'ouverture du fichier");
        pthread_exit(compteur);
    }

    // Obtenir la taille du fichier
    int tailleFichier = lseek(fichier, 0, SEEK_END);
    close(fichier); // Fermer le fichier après avoir obtenu la taille

    // Réouvrir le fichier pour lire le contenu
    fichier = open(parametre->nomFichier, O_RDONLY);
    if (fichier == -1) {
        perror("Erreur d'ouverture du fichier pour lecture");
        pthread_exit(compteur);
    }

    char mot[40]; // Tableau pour stocker le mot à comparer
    int tailleMot = strlen(parametre->motRecherche); // Longueur du mot à rechercher

    // Lire chaque caractère du fichier et comparer
    for (int i = 0; i < tailleFichier - tailleMot; i++) {
        lseek(fichier, i, SEEK_SET); // Positionner le curseur à la position i
        read(fichier, mot, tailleMot); // Lire une portion du fichier

        mot[tailleMot] = '\0'; // Ajouter un caractère de fin de chaîne

        // Si le mot trouvé est égal au mot recherché, augmenter le compteur
        if (strcmp(mot, parametre->motRecherche) == 0) {
            (*compteur)++;
        }
    }

    close(fichier); // Fermer le fichier

    pthread_exit(compteur); // Retourner le nombre d'occurrences trouvé
}
