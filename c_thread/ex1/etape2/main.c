#include <stdio.h>  // Inclusion des bibliothèques nécessaires
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *occurencesT1(void *arg);
void *occurencesT2(void *arg);
void *occurencesT3(void *arg);
void *occurencesT4(void *arg);

int main() {
    pthread_t thread1, thread2, thread3, thread4;  
    int* resultat1;
    int* resultat2;
    int* resultat3;
    int* resultat4;

    if (pthread_create(&thread1, NULL, occurencesT1, NULL) != 0) {
        perror("Erreur lors de la création du thread");
        return 1;
    }
    if (pthread_create(&thread2, NULL, occurencesT2, NULL) != 0) {
        perror("Erreur lors de la création du thread");
        return 1;
    }
    if (pthread_create(&thread3, NULL, occurencesT3, NULL) != 0) {
        perror("Erreur lors de la création du thread");
        return 1;
    }
    if (pthread_create(&thread4, NULL, occurencesT4, NULL) != 0) {
        perror("Erreur lors de la création du thread");
        return 1;
    }

    if (pthread_join(thread1, (void**)&resultat1) != 0) {
        perror("Erreur lors de la jointure du thread");
        return 1;
    }
    if (pthread_join(thread2, (void**)&resultat2) != 0) {
        perror("Erreur lors de la jointure du thread");
        return 1;
    }
    if (pthread_join(thread3, (void**)&resultat3) != 0) {
        perror("Erreur lors de la jointure du thread");
        return 1;
    }
    if (pthread_join(thread4, (void**)&resultat4) != 0) {
        perror("Erreur lors de la jointure du thread");
        return 1;
    }

    printf("Occurrences trouvées:\n");
    printf("Thread 1: %d\n", *resultat1);
    printf("Thread 2: %d\n", *resultat2);
    printf("Thread 3: %d\n", *resultat3);
    printf("Thread 4: %d\n", *resultat4);

    free(resultat1);
    free(resultat2);
    free(resultat3);
    free(resultat4);

    return 0;
}

void *occurencesT1(void *arg) {
    const char *filename = "text1.txt";
    const char *word = "maison";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        pthread_exit(NULL);
    }

    int count = 0;
    char buffer[256];
    while (fscanf(file, "%255s", buffer) == 1) {
        if (strstr(buffer, word) != NULL) {
            count++;
        }
    }
    printf("*\n");
    fclose(file);

    int *result = (int*)malloc(sizeof(int));
    *result = count;
    pthread_exit(result);
}

void *occurencesT2(void *arg) {
    const char *filename = "text1.txt";
    const char *word = "voiture";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        pthread_exit(NULL);
    }

    int count = 0;
    char buffer[256];
    while (fscanf(file, "%255s", buffer) == 1) {
        if (strstr(buffer, word) != NULL) {
            count++;
        }
    }
    printf("\t*\n");
    fclose(file);

    int *result = (int*)malloc(sizeof(int));
    *result = count;
    pthread_exit(result);
}

void *occurencesT3(void *arg) {
    const char *filename = "text1.txt";
    const char *word = "ordinateur";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        pthread_exit(NULL);
    }

    int count = 0;
    char buffer[256];
    while (fscanf(file, "%255s", buffer) == 1) {
        if (strstr(buffer, word) != NULL) {
            count++;
        }
    }
    printf("\t\t*\n");
    fclose(file);

    int *result = (int*)malloc(sizeof(int));
    *result = count;
    pthread_exit(result);
}

void *occurencesT4(void *arg) {
    const char *filename = "text1.txt";
    const char *word = "telephone";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        pthread_exit(NULL);
    }

    int count = 0;
    char buffer[256];
    while (fscanf(file, "%255s", buffer) == 1) {
        if (strstr(buffer, word) != NULL) {
            count++;
        }
    }
    printf("\t\t\t*\n");
    fclose(file);

    int *result = (int*)malloc(sizeof(int));
    *result = count;
    pthread_exit(result);
}