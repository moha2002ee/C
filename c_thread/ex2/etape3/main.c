#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void sigusr1_handler(int sig) {
    pthread_t tid = pthread_self();
    printf("Thread %lu received SIGUSR1\n", (unsigned long) tid);
    pthread_exit(NULL);
}

void sigint_handler(int sig) {
    // Message de débogage
    printf("Master received SIGINT, sending SIGUSR1 to itself...\n");
    kill(getpid(), SIGUSR1);  // Master thread sends SIGUSR1 to itself
}

void* slave_thread(void* arg) {
    // Configuration du gestionnaire pour SIGUSR1
    struct sigaction sa;
    sa.sa_handler = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    // Attente du signal SIGUSR1
    pause();
    return NULL;
}

void* master_thread(void* arg) {
    // Configuration du gestionnaire pour SIGINT
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    // Attente du signal SIGINT (qui déclenchera SIGUSR1)
    pause();
    return NULL;
}

int main() {
    pthread_t master, slaves[4];
    sigset_t mask;

    // Masquer SIGUSR1 dans le thread principal
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);

    // Créer le thread maître
    pthread_create(&master, NULL, master_thread, NULL);

    // Créer les threads slaves
    for (int i = 0; i < 4; i++) {
        pthread_create(&slaves[i], NULL, slave_thread, NULL);
    }

    // Attendre que les threads slaves se terminent
    for (int i = 0; i < 4; i++) {
        pthread_join(slaves[i], NULL);
    }

    // Attendre que le thread maître se termine
    pthread_join(master, NULL);

    return 0;
}
