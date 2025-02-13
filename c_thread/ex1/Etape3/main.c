#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


typedef struct {
    char filename[20];
    char mot[10];
    int tabulations;
} ThreadParams;


void* OccurenceCountFile(void* arg) {
    ThreadParams* params = (ThreadParams*)arg;


    int fp = open(params->filename, O_RDONLY);
    if (fp == -1) {
        printf("Erreur d'ouverture du fichier %s.\n", params->filename);
        return NULL;
    }


    for (int i = 0; i < params->tabulations; i++) {
        printf("\t");
    }
    printf("*\n");


    char lettre[1];
    int occurence = 0;
    int i = 0;
    int cibleLonger = strlen(params->mot);

    while (read(fp, lettre, 1) > 0) {
        if (params->mot[i] == lettre[0]) {
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


    int* resultat = malloc(sizeof(int));
    *resultat = occurence;
    return resultat;
}

int main() {
    puts("Thread principal demarre");


    ThreadParams params1 = {"text1", "", 0};
    ThreadParams params2 = {"text2", "", 1};
    ThreadParams params3 = {"text3", "", 2};
    ThreadParams params4 = {"text4", "", 3};


    printf("Entrez le mot à rechercher dans text1 : ");
    scanf("%s", params1.mot);
    printf("Entrez le mot à rechercher dans text2 : ");
    scanf("%s", params2.mot);
    printf("Entrez le mot à rechercher dans text3 : ");
    scanf("%s", params3.mot);
    printf("Entrez le mot à rechercher dans text4 : ");
    scanf("%s", params4.mot);

    // Créer les threads
    pthread_t pit1, pit2, pit3, pit4;
    pthread_create(&pit1, NULL, OccurenceCountFile, &params1);
    pthread_create(&pit2, NULL, OccurenceCountFile, &params2);
    pthread_create(&pit3, NULL, OccurenceCountFile, &params3);
    pthread_create(&pit4, NULL, OccurenceCountFile, &params4);

    puts("Threads secondaires lancés !");
    puts("Attente de la fin des threads secondaires");

    // Récupérer les résultats des threads
    int* occurrence1;
    int* occurrence2;
    int* occurrence3;
    int* occurrence4;
    pthread_join(pit1, (void**)&occurrence1);
    pthread_join(pit2, (void**)&occurrence2);
    pthread_join(pit3, (void**)&occurrence3);
    pthread_join(pit4, (void**)&occurrence4);

    // Afficher les résultats
    printf("Thread principal : les threads secondaires ont terminé.\n");
    printf("Le nombre d'occurrences de '%s' dans text1 est : %d\n", params1.mot, *occurrence1);
    printf("Le nombre d'occurrences de '%s' dans text2 est : %d\n", params2.mot, *occurrence2);
    printf("Le nombre d'occurrences de '%s' dans text3 est : %d\n", params3.mot, *occurrence3);
    printf("Le nombre d'occurrences de '%s' dans text4 est : %d\n", params4.mot, *occurrence4);

    // Libérer la mémoire allouée pour les résultats
    free(occurrence1);
    free(occurrence2);
    free(occurrence3);
    free(occurrence4);

    return 0;
}