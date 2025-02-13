#include <stdio.h>    // Inclusion de la bibliothèque standard pour les entrées/sorties
#include <stdlib.h>   // Inclusion de la bibliothèque pour les fonctions de gestion de mémoire
#include <fcntl.h>    // Inclusion de la bibliothèque pour l'ouverture de fichiers
#include <unistd.h>   // Inclusion de la bibliothèque pour la gestion des appels systèmes
#include <string.h>   // Inclusion de la bibliothèque pour les fonctions sur les chaînes de caractères
#include <pthread.h>  // Inclusion de la bibliothèque pour l'utilisation des threads (POSIX)

void* compterOccurrencesDansFichier1(void* arg);
void* compterOccurrencesDansFichier2(void* arg);
void* compterOccurrencesDansFichier3(void* arg);
void* compterOccurrencesDansFichier4(void* arg);

int main() {
    pthread_t threads[4];  // Déclaration des threads
    int resultat;

    // Création des threads
    resultat = pthread_create(&threads[0], NULL, compterOccurrencesDansFichier1, NULL);
    if (resultat != 0) {
        printf("Erreur lors de la création du thread 1 !\n");
        return 1;
    }

    resultat = pthread_create(&threads[1], NULL, compterOccurrencesDansFichier2, NULL);
    if (resultat != 0) {
        printf("Erreur lors de la création du thread 2 !\n");
        return 1;
    }

    resultat = pthread_create(&threads[2], NULL, compterOccurrencesDansFichier3, NULL);
    if (resultat != 0) {
        printf("Erreur lors de la création du thread 3 !\n");
        return 1;
    }

    resultat = pthread_create(&threads[3], NULL, compterOccurrencesDansFichier4, NULL);
    if (resultat != 0) {
        printf("Erreur lors de la création du thread 4 !\n");
        return 1;
    }

    // Attente de la fin des threads
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Le thread principal : tous les threads secondaires ont terminé.\n");

    return 0;
}

void* compterOccurrencesDansFichier1(void* arg) {
    int descripteurFichier = open("text1", O_RDONLY);
    if (descripteurFichier == -1) {
        printf("Erreur d'ouverture du fichier.\n");
        return (void*)-1;
    }

    printf("*\n");

    // Ajoutez ici le code pour compter les occurrences du mot dans le fichier

    close(descripteurFichier);
    return NULL;
}

void* compterOccurrencesDansFichier2(void* arg) {
    int descripteurFichier = open("text2", O_RDONLY);
    if (descripteurFichier == -1) {
        printf("Erreur d'ouverture du fichier.\n");
        return (void*)-1;
    }

    printf("\t*\n");

    // Ajoutez ici le code pour compter les occurrences du mot dans le fichier

    close(descripteurFichier);
    return NULL;
}

void* compterOccurrencesDansFichier3(void* arg) {
    int descripteurFichier = open("text3", O_RDONLY);
    if (descripteurFichier == -1) {
        printf("Erreur d'ouverture du fichier.\n");
        return (void*)-1;
    }

    printf("\t\t*\n");

    // Ajoutez ici le code pour compter les occurrences du mot dans le fichier

    close(descripteurFichier);
    return NULL;
}

void* compterOccurrencesDansFichier4(void* arg) {
    int descripteurFichier = open("text4", O_RDONLY);
    if (descripteurFichier == -1) {
        printf("Erreur d'ouverture du fichier.\n");
        return (void*)-1;
    }

    printf("\t\t\t*\n");

    // Ajoutez ici le code pour compter les occurrences du mot dans le fichier

    close(descripteurFichier);
    return NULL;
}
