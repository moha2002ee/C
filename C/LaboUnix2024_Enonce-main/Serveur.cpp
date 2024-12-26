#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "protocole.h"  // Contient la clé et la structure d'un message

int idQ, idShm, idSem;
int fdPipe[2];
TAB_CONNEXIONS *tab;

void afficheTab();
int verifierLogin(const char* nom, const char* motDePasse);  // Prototype de la fonction

int main()
{
    // Création des ressources
    fprintf(stderr, "(SERVEUR %d) Création de la file de messages\n", getpid());
    if ((idQ = msgget(CLE, IPC_CREAT | IPC_EXCL | 0600)) == -1) {
        perror("(SERVEUR) Erreur de msgget");
        exit(1);
    }

    // Initialisation du tableau de connexions
    tab = (TAB_CONNEXIONS*) malloc(sizeof(TAB_CONNEXIONS)); 
    for (int i = 0; i < 6; i++) {
        tab->connexions[i].pidFenetre = 0;
        strcpy(tab->connexions[i].nom, "");
        tab->connexions[i].pidCaddie = 0;
    }
    tab->pidServeur = getpid();
    tab->pidPublicite = 0;

    afficheTab();

    MESSAGE m;
    MESSAGE reponse;

    while (1) {
        fprintf(stderr, "(SERVEUR %d) Attente d'une requête...\n", getpid());
        if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), 1, 0) == -1) {
            perror("(SERVEUR) Erreur de msgrcv");
            msgctl(idQ, IPC_RMID, NULL);
            exit(1);
        }

        switch (m.requete) {
            case CONNECT:
                fprintf(stderr, "(SERVEUR %d) Requête CONNECT reçue de %d\n", getpid(), m.expediteur);
                // Logique pour gérer la connexion
                for (int i = 0; i < 6; i++) {
                    if (tab->connexions[i].pidFenetre == 0) {
                        tab->connexions[i].pidFenetre = m.expediteur;
                        break;
                    }
                }
                break;

            case DECONNECT:
                fprintf(stderr, "(SERVEUR %d) Requête DECONNECT reçue de %d\n", getpid(), m.expediteur);
                // Logique pour gérer la déconnexion
                for (int i = 0; i < 6; i++) {
                    if (tab->connexions[i].pidFenetre == m.expediteur) {
                        tab->connexions[i].pidFenetre = 0;
                        strcpy(tab->connexions[i].nom, "");
                        break;
                    }
                }
                break;

            case LOGIN:
                fprintf(stderr, "(SERVEUR %d) Requête LOGIN reçue de %d : --%d--%s--%s--\n", getpid(), m.expediteur, m.data1, m.data2, m.data3);
                // Vérification des informations de login
                int loginSuccess = verifierLogin(m.data2, m.data3);  // Renommé pour éviter conflit avec la macro LOGOUT
                if (loginSuccess) {
                    // Ajouter l'utilisateur dans la table des connexions
                    for (int i = 0; i < 6; i++) {
                        if (tab->connexions[i].pidFenetre == m.expediteur) {
                            strcpy(tab->connexions[i].nom, m.data2);  // Nom de l'utilisateur
                            break;
                        }
                    }
                    reponse.data1 = 1;  // Login réussi
                    strcpy(reponse.data4, "Login réussi");
                } else {
                    reponse.data1 = 0;  // Login échoué
                    strcpy(reponse.data4, "Nom d'utilisateur ou mot de passe incorrect");
                }
                // Répondre au client
                reponse.expediteur = getpid();
                reponse.requete = LOGIN;
                msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);
                break;

            case LOGOUT:
                fprintf(stderr, "(SERVEUR %d) Requête LOGOUT reçue de %d\n", getpid(), m.expediteur);
                // Logique pour gérer le logout
                for (int i = 0; i < 6; i++) {
                    if (tab->connexions[i].pidFenetre == m.expediteur) {
                        tab->connexions[i].pidFenetre = 0;
                        strcpy(tab->connexions[i].nom, "");
                        break;
                    }
                }
                break;

            default:
                fprintf(stderr, "(SERVEUR %d) Requête inconnue reçue de %d\n", getpid(), m.expediteur);
                break;
        }

        afficheTab();
    }

    return 0;
}

void afficheTab()
{
    fprintf(stderr, "Pid Serveur   : %d\n", tab->pidServeur);
    fprintf(stderr, "Pid Publicite : %d\n", tab->pidPublicite);
    fprintf(stderr, "Pid AccesBD   : %d\n", tab->pidAccesBD);
    for (int i = 0; i < 6; i++)
        fprintf(stderr, "%6d -%20s- %6d\n", tab->connexions[i].pidFenetre,
                                                        tab->connexions[i].nom,
                                                        tab->connexions[i].pidCaddie);
    fprintf(stderr, "\n");
}

// Fonction fictive de vérification du login
int verifierLogin(const char* nom, const char* motDePasse) {
    // Pour l'exemple, un login de base
    if (strcmp(nom, "wagner") == 0 && strcmp(motDePasse, "123") == 0)
        return 1;  // Succès
    return 0;  // Échec
}
