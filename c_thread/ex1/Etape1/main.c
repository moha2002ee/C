#include <stdio.h>    // Inclusion de la bibliothèque standard pour les entrées/sorties
#include <stdlib.h>   // Inclusion de la bibliothèque pour les fonctions de gestion de mémoire
#include <fcntl.h>    // Inclusion de la bibliothèque pour l'ouverture de fichiers
#include <unistd.h>   // Inclusion de la bibliothèque pour la gestion des appels systèmes
#include <string.h>   // Inclusion de la bibliothèque pour les fonctions sur les chaînes de caractères
#include <pthread.h>  // Inclusion de la bibliothèque pour l'utilisation des threads (POSIX)

void* compterOccurrencesDansFichier(void* arg);  // Déclaration de la fonction pour compter les occurrences dans le fichier

int main() {
    puts("Le thread principal démarre.");  // Affichage de l'état du thread principal

    pthread_t thread;  // Déclaration du thread
    int resultat = pthread_create(&thread, NULL, compterOccurrencesDansFichier, NULL);  // Création du thread
    if (resultat != 0) {  // Vérification si le thread a été créé avec succès
        printf("Erreur lors de la création du thread !\n");  // Affichage d'une erreur si le thread n'a pas pu être créé
        return 1;  // Retourne une erreur
    }

    puts("Thread secondaire lancé !");  // Message indiquant que le thread secondaire a démarré
    puts("Attente de la fin du thread secondaire...");  // Message indiquant l'attente de la fin du thread secondaire

    int nombreOccurrences;  // Variable pour stocker le nombre d'occurrences
    pthread_join(thread, (void**)&nombreOccurrences);  // Attente de la fin du thread secondaire et récupération du résultat

    printf("Le thread principal : le thread secondaire a terminé.\n");
    printf("Le nombre d'occurrences du mot dans le texte est : %d\n", nombreOccurrences);  // Affichage du résultat

    return 0;  // Fin du programme principal
}

// Fonction exécutée par le thread secondaire
void* compterOccurrencesDansFichier(void* arg) {
    int descripteurFichier = open("text1", O_RDONLY);  // Ouverture du fichier "text1" en mode lecture seule
    if (descripteurFichier == -1) {  // Si le fichier n'a pas pu être ouvert
        printf("Erreur d'ouverture du fichier.\n");
        return (void*)-1;  // Retourne -1 en cas d'erreur d'ouverture
    }

    if (descripteurFichier == -1) {  // Si le fichier n'a pas pu être ouvert
        printf("Erreur d'ouverture du fichier.\n");
        return NULL;  // Retourne NULL en cas d'erreur d'ouverture
    }

    printf("Entrez le mot que vous souhaitez rechercher : ");
    char motRecherche[10];  // Tableau pour stocker le mot recherché, limité à 9 caractères
    if (scanf("%9s", motRecherche) != 1) {  // Vérification de la lecture du mot
        printf("Erreur lors de la lecture du mot.\n");
        close(descripteurFichier);
        return NULL;  // Retourne NULL si la lecture du mot échoue
    }

    int longueurMotCible = strlen(motRecherche);  // Calcul de la longueur du mot recherché
    char caractere;  // Variable pour lire un caractère du fichier
    int nombreOccurrences = 0;  // Compteur pour le nombre d'occurrences du mot
    int indexMot = 0;  // Index pour parcourir le mot recherché

    // Lecture du fichier caractère par caractère
    while (read(descripteurFichier, &caractere, 1) > 0) {
        if (motRecherche[indexMot] == caractere) {  // Si le caractère correspond au caractère du mot recherché
            indexMot++;  // Avancer l'index du mot recherché
            if (indexMot == longueurMotCible) {  // Si on a trouvé une occurrence complète du mot
                nombreOccurrences++;  // Incrémenter le compteur d'occurrences
                indexMot = 0;  // Réinitialiser l'index pour rechercher une nouvelle occurrence
            }
        } else {
            indexMot = 0;  // Si le caractère ne correspond pas, réinitialiser l'index
        }
    }

    close(descripteurFichier);  // Fermeture du fichier

    // Allocation de mémoire pour retourner le nombre d'occurrences
    int* resultat = (int*)malloc(sizeof(int));
    if (resultat == NULL) {  // Vérification si l'allocation mémoire a échoué
        printf("Erreur d'allocation mémoire.\n");
        return NULL;  // Retourne NULL en cas d'échec de l'allocation mémoire
    }

    *resultat = nombreOccurrences;  // Stocker le nombre d'occurrences dans la variable allouée
    return resultat;  // Retourner le pointeur contenant le nombre d'occurrences
}

/*
** SYNTHÈSE DU PROGRAMME
**
** Le programme est un exemple d'utilisation de threads en C, qui permet de compter le nombre d'occurrences d'un mot dans un fichier texte.
**
** 1. But du programme :
** Le programme a pour objectif de compter le nombre de fois où un mot donné apparaît dans un fichier texte en utilisant deux threads :
** - Le thread principal crée un thread secondaire pour traiter le fichier.
** - Le thread secondaire lit le fichier et cherche le mot spécifié, puis retourne le nombre d'occurrences trouvées.
**
** 2. Déroulement général :
** - Le thread principal démarre et crée un thread secondaire avec la fonction `pthread_create`.
** - Le thread secondaire ouvre un fichier nommé `text1`, lit son contenu et compte le nombre d'occurrences d'un mot donné par l'utilisateur.
** - Le résultat est retourné au thread principal grâce à `pthread_join`.
**
** 3. Pourquoi utiliser des threads ?
** L'utilisation des threads permet de gérer plusieurs tâches en parallèle. Bien que l'exécution d'un seul thread suffise pour ce programme, l'utilisation de threads permet de démontrer la gestion de tâches parallèles.
**
** 4. Gestion des erreurs :
** Le programme gère plusieurs erreurs possibles :
** - Si le fichier ne peut pas être ouvert, une erreur est affichée.
** - Si l'allocation mémoire échoue, une autre erreur est retournée.
** - Si la lecture du mot échoue, une erreur est également signalée.
**
** 5. Conclusion :
** Ce programme permet de démontrer l'utilisation des threads pour effectuer des tâches simultanées. Le thread principal attend la fin du traitement du fichier par le thread secondaire et affiche le nombre d'occurrences trouvées.
*/
