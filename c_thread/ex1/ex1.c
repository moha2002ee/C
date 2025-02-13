#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void* Fct(void* p);

int main() {
    int* retA;
    pthread_t tid;
    pthread_create(&tid, NULL, Fct, NULL);
    pthread_join(tid, (void**)&retA);

    printf("%d\n", *retA);
    free(retA);

    return 0; // Use return 0 for success
}

void* Fct(void* p) {
    char motATrouver[6] = "Papa"; // Initialize directly
    char buffer[5]; // Adjust buffer size
    int fd, nbcaract, i = 0;
    int* pA = (int*)malloc(sizeof(int));
    *pA = 0; // Initialize to 0

    fd = open("FichierALire.txt", O_RDONLY); // Open file ONCE
    if (fd == -1) {
        perror("Erreur ouverture fichier");
        pthread_exit(pA); // Exit thread if file open fails
    }

    while ((nbcaract = read(fd, buffer, 4)) > 0) { // Read until end of file
        buffer[nbcaract] = '\0'; // Null-terminate the buffer

        if (strcmp(motATrouver, buffer) == 0) {
            (*pA)++; // Increment the count
        }
        i++;
    }

    close(fd);
    pthread_exit(pA);
}