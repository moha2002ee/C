#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* OccurenceCountFile1(void* arg);
void* OccurenceCountFile2(void* arg);
void* OccurenceCountFile3(void* arg);
void* OccurenceCountFile4(void* arg);

int main() {
    puts("Thread principal demarre");

    pthread_t pit1, pit2, pit3, pit4;
    int resultat = pthread_create(&pit1, NULL, OccurenceCountFile1, NULL);
    if (resultat != 0) {
        printf("Erreur lors de la création du thread !\n");
        return 1;
    }
    puts("*");

    resultat = pthread_create(&pit2, NULL, OccurenceCountFile2, NULL);
    if (resultat != 0) {
        printf("Erreur lors de la création du thread !\n");
        return 1;
    }
    puts("  *");

    resultat = pthread_create(&pit3, NULL, OccurenceCountFile3, NULL);
    if (resultat != 0) {
        printf("Erreur lors de la création du thread !\n");
        return 1;
    }
    puts("      *");

    resultat = pthread_create(&pit4, NULL, OccurenceCountFile4, NULL);
    if (resultat != 0) {
        printf("Erreur lors de la création du thread !\n");
        return 1;
    }
    puts("          *");

    puts("Attente de la fin du thread secondaire");
    int* occurrence1;
    pthread_join(pit1, (void**)&occurrence1);

    puts("Attente de la fin du thread secondaire");
    int* occurrence2;
    pthread_join(pit2, (void**)&occurrence2);

    puts("Attente de la fin du thread secondaire");
    int* occurrence3;
    pthread_join(pit3, (void**)&occurrence3);

    puts("Attente de la fin du thread secondaire");
    int* occurrence4;
    pthread_join(pit4, (void**)&occurrence4);

    printf("Thread principal : le thread secondaire a terminé.\n");
    printf("Le nombre d'occurrences de ce mot dans le texte 1 est : %d\n", *occurrence1);
    printf("Le nombre d'occurrences de ce mot dans le texte 2 est : %d\n", *occurrence2);
    printf("Le nombre d'occurrences de ce mot dans le texte 3 est : %d\n", *occurrence3);
    printf("Le nombre d'occurrences de ce mot dans le texte 4 est : %d\n", *occurrence4);

    free(occurrence1);
    free(occurrence2);
    free(occurrence3);
    free(occurrence4);
    return 0;
}

void* OccurenceCountFile1(void* arg) {
    int fp = open("text1", O_RDONLY);
    if (fp == -1) {
        printf("Erreur d'ouverture du fichier.\n");
        return NULL;
    }

    printf("Entrez le mot que vous désirez trouver le nombre de ses occurrences dans le texte 1: ");
    char mot[10];
    scanf("%s", mot);
    int cibleLonger = strlen(mot);

    char lettre[1];
    int occurence = 0;
    int i = 0;

    while (read(fp, lettre, 1) > 0) {
        if (mot[i] == lettre[0]) {
            i++;
            if (i == cibleLonger) {
                occurence++;
                i = 0;
            }
        } else {
            i = 0;
        }
    }

    close(fp);
    int* resultat = (int*)malloc(sizeof(int));  // Cast explicite ajouté ici
    *resultat = occurence;
    return resultat;
}

void* OccurenceCountFile2(void* arg) {
    int fp = open("text2", O_RDONLY);
    if (fp == -1) {
        printf("Erreur d'ouverture du fichier.\n");
        return NULL;
    }

    printf("Entrez le mot que vous désirez trouver le nombre de ses occurrences dans le texte 2 : ");
    char mot[10];
    scanf("%s", mot);
    int cibleLonger = strlen(mot);

    char lettre[1];
    int occurence = 0;
    int i = 0;

    while (read(fp, lettre, 1) > 0) {
        if (mot[i] == lettre[0]) {
            i++;
            if (i == cibleLonger) {
                occurence++;
                i = 0;
            }
        } else {
            i = 0;
        }
    }

    close(fp);
    int* resultat = (int*)malloc(sizeof(int));  // Cast explicite ajouté ici
    *resultat = occurence;
    return resultat;
}

void* OccurenceCountFile3(void* arg) {
    int fp = open("text3", O_RDONLY);
    if (fp == -1) {
        printf("Erreur d'ouverture du fichier.\n");
        return NULL;
    }

    printf("Entrez le mot que vous désirez trouver le nombre de ses occurrences dans le texte 3: ");
    char mot[10];
    scanf("%s", mot);
    int cibleLonger = strlen(mot);

    char lettre[1];
    int occurence = 0;
    int i = 0;

    while (read(fp, lettre, 1) > 0) {
        if (mot[i] == lettre[0]) {
            i++;
            if (i == cibleLonger) {
                occurence++;
                i = 0;
            }
        } else {
            i = 0;
        }
    }

    close(fp);
    int* resultat = (int*)malloc(sizeof(int));  // Cast explicite ajouté ici
    *resultat = occurence;
    return resultat;
}

void* OccurenceCountFile4(void* arg) {
    int fp = open("text4", O_RDONLY);
    if (fp == -1) {
        printf("Erreur d'ouverture du fichier.\n");
        return NULL;
    }

    printf("Entrez le mot que vous désirez trouver le nombre de ses occurrences dans le texte 4: ");
    char mot[10];
    scanf("%s", mot);
    int cibleLonger = strlen(mot);

    char lettre[1];
    int occurence = 0;
    int i = 0;

    while (read(fp, lettre, 1) > 0) {
        if (mot[i] == lettre[0]) {
            i++;
            if (i == cibleLonger) {
                occurence++;
                i = 0;
            }
        } else {
            i = 0;
        }
    }

    close(fp);
    int* resultat = (int*)malloc(sizeof(int));  // Cast explicite ajouté ici
    *resultat = occurence;
    return resultat;
}