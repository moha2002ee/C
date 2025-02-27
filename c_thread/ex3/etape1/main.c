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

void *fonctionThread(void *arg) {
    DONNEE *param = (DONNEE *)arg;

    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    printf("Thread %d.%lu lancé\n", pid, tid);
    printf("Nom : %s\n", param->nom);

    struct timespec ts = {param->nbSecondes, 0};
    nanosleep(&ts, NULL);

    printf("Thread %d.%lu se termine\n", pid, tid);

    pthread_exit(NULL);
}

int main() {
    int i = 0;
    pthread_t threads[sizeof(data) / sizeof(data[0])];

    for (i = 0; data[i].nbSecondes != 0; i++) {
        pthread_create(&threads[i], NULL, fonctionThread, (void *)&data[i]);
    }

    for (int j = 0; j < i; j++) {
        pthread_join(threads[j], NULL);
    }

    printf("Tous les threads sont terminés.\n");

    return 0;
}