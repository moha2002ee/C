#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    char nom[20];
    int nbSecondes;
} DONNEE;

DONNEE data[] = {
    {"MATAGNE", 15},
    {"WILVERS", 10},
    {"WAGNER", 17},
    {"QUETTIER", 8},
    {"", 0}
};

// Déclaration du mutex
pthread_mutex_t mutexParam;

void *fonctionThread(void *arg) {
    DONNEE *param = (DONNEE *)arg;

    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    printf("Thread %d.%lu lancé\n", pid, tid);
    printf("Nom : %s\n", param->nom);

    struct timespec ts = {param->nbSecondes, 0};
    nanosleep(&ts, NULL);

    printf("Thread %d.%lu se termine\n", pid, tid);

    free(param); // Libération de la mémoire
    pthread_exit(NULL);
}

int main() {
    int i = 0;
    pthread_t threads[sizeof(data) / sizeof(data[0])];

    // Initialisation du mutex
    pthread_mutex_init(&mutexParam, NULL);

    for (i = 0; data[i].nbSecondes != 0; i++) {
        // Allouer dynamiquement la mémoire pour chaque thread
        DONNEE *param = malloc(sizeof(DONNEE));
        if (param == NULL) {
            perror("Erreur malloc");
            exit(EXIT_FAILURE);
        }

        // Copier les données de manière sécurisée
        pthread_mutex_lock(&mutexParam);
        memcpy(param, &data[i], sizeof(DONNEE));
        pthread_mutex_unlock(&mutexParam);

        // Créer le thread avec le paramètre unique
        pthread_create(&threads[i], NULL, fonctionThread, (void *)param);
    }

    for (int j = 0; j < i; j++) {
        pthread_join(threads[j], NULL);
    }

    // Destruction du mutex
    pthread_mutex_destroy(&mutexParam);

    printf("Tous les threads sont terminés.\n");

    return 0;
}
