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
    pause();  // Attente d'un signal (ne sera jamais reçu car SIGINT est masqué)
    printf("Thread Slave %lu: J'ai reçu un signal, je me termine.\n", tid);
    pthread_exit(NULL);
}

// Fonction exécutée par le thread Master
void* master_thread(void* arg) {
    pthread_t tid = pthread_self();
    printf("Thread Master %lu: Je suis le seul à pouvoir recevoir SIGINT.\n", tid);

    while (1) {
        printf("Thread Master %lu: J'attends un signal...\n", tid);
        pause();  // Attente d'un signal
    }

    pthread_exit(NULL);
}

// Handler pour le signal SIGINT
void sigint_handler(int sig) {
    pthread_t tid = pthread_self();
    printf("Thread Master %lu: J'ai reçu le signal SIGINT, je me termine.\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t slaves[4];
    pthread_t master;
    struct sigaction sa;
    sigset_t mask;

    // Configuration du handler pour SIGINT
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);

    // Masquage du signal SIGINT dans tous les threads sauf le thread Master
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    // Masquage de SIGINT dans le thread principal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);

    // Création du thread Master
    pthread_create(&master, NULL, master_thread, NULL);

    // Démasquage de SIGINT dans le thread Master
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);

    // Création des threads Slaves
    for (int i = 0; i < 4; i++) {
        pthread_create(&slaves[i], NULL, slave_thread, NULL);
    }

    // Le thread principal masque également SIGINT
    printf("Thread Principal: Je masque SIGINT et je vais attendre.\n");
    pause();  // Le thread principal ne recevra jamais SIGINT

    // Le thread principal se termine
    printf("Thread Principal: Je me termine.\n");
    pthread_exit(NULL);
}