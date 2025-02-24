#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


// Fonction exécutée par les threads Slaves
void* slave_thread(void* arg) {
    pthread_t tid = pthread_self();
    printf("Thread Slave %lu: Je vais attendre un signal...\n", tid);
    pause();  // Attente d'un signal
    printf("Thread Slave %lu: J'ai reçu un signal, je me termine.\n", tid);
    pthread_exit(NULL);
}

// Handler pour le signal SIGINT
void sigint_handler(int sig) {
    pthread_t tid = pthread_self();
    printf("Thread %lu: J'ai reçu le signal SIGINT, je me termine.\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t slaves[4];
    struct sigaction sa;

    // Configuration du handler pour SIGINT
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);

    // Création des threads Slaves
    for (int i = 0; i < 4; i++) {
        pthread_create(&slaves[i], NULL, slave_thread, NULL);
    }

    // Le thread principal attend un signal
    printf("Thread Principal: Je vais attendre un signal...\n");
    pause();

    // Le thread principal se termine
    printf("Thread Principal: J'ai reçu un signal, je me termine.\n");
    pthread_exit(NULL);  // ou exit(0);
}