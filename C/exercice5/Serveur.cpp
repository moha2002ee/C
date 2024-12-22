#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "protocole.h" // contient la cle et la structure d'un message

void HandlerSIGINT(int sig);
int Authentification(int id, MESSAGE requete, int dest, int flg);

int idQ;
int pid1, pid2;
int ret;

int main()
{
  MESSAGE requete;
  pid_t destinataire;

  // Armement du signal SIGINT
  struct sigaction A;
  A.sa_handler = HandlerSIGINT;
  sigemptyset(&A.sa_mask);
  A.sa_flags = 0;

  if (sigaction(SIGINT, &A, NULL) == -1)
  {
    perror("Erreur de sigaction");
    exit(1);
  }
  else
    fprintf(stderr, "(SERVEUR) Signal SIGINT armé\n");

  // Vérification de l'existence de la file avant création
  fprintf(stderr, "(SERVEUR) Création de la file de messages\n");
  idQ = msgget(CLE, 0600); // Vérifier si la file existe déjà

  if (idQ == -1) {
    // La file n'existe pas, on la crée
    if ((idQ = msgget(CLE, IPC_CREAT | 0600)) == -1) {
      perror("Erreur de création de la file de messages");
      exit(1);
    }
    fprintf(stderr, "(SERVEUR) Nouvelle file de messages créée.\n");
  } else {
    fprintf(stderr, "(SERVEUR) File de messages déjà existante.\n");
  }

  // Attente de connexion de 2 clients
  fprintf(stderr, "(SERVEUR) Attente de connexion du premier client...\n");
  if ((pid1 = Authentification(idQ, requete, 1, 0)) == -1)
  {
    fprintf(stderr, "(SERVEUR) Échec d'authentification du client 1\n");
  }

  fprintf(stderr, "(SERVEUR) Attente de connexion du second client...\n");
  if ((pid2 = Authentification(idQ, requete, 1, 0)) == -1)
  {
    fprintf(stderr, "(SERVEUR) Échec d'authentification du client 2\n");
  }

  while (1)
  {
    char signature[10] = "(SERVEUR)";
    char buffer[80];

    // Attente d'une requête
    fprintf(stderr, "(SERVEUR) Attente d'une requête...\n");
    if ((ret = msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0)) == -1)
    {
      perror("Erreur de réception : msgrcv");
      continue; // Reprendre l'attente si msgrcv échoue
    }

    fprintf(stderr, "(SERVEUR) Requête reçue de %d : --%s--\n", requete.expediteur, requete.texte);

    // Préparation de la réponse
    sprintf(buffer, "%s%s", signature, requete.texte);
    destinataire = requete.expediteur;
    requete.expediteur = getpid();  // Mettre le pid du serveur comme expéditeur
    strcpy(requete.texte, buffer);

    // Choisir le destinataire en fonction de l'expéditeur
    if (destinataire == pid1)
    {
      requete.type = pid2;
      destinataire = pid2;
    }
    else
    {
      requete.type = pid1;
      destinataire = pid1;
    }

    fprintf(stderr, "(SERVEUR) Envoi de la réponse à %d\n", destinataire);

    if (msgsnd(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 0) == -1)
    {
      perror("Erreur d'envoi du message (SERVEUR)");
    }

    // Envoi du signal pour notifier le client
    kill(destinataire, SIGUSR1);
  }
}

int Authentification(int id, MESSAGE requete, int dest, int flg)
{
  while (1)
  {
    ret = msgrcv(id, &requete, sizeof(MESSAGE) - sizeof(long), dest, flg);

    if (ret == -1)
    {
      perror("(SERVEUR) Échec d'authentification");
      break;
    }
    else if (ret > 0)
    {
      fprintf(stderr, "(SERVEUR) Authentification validée !\n");
      return requete.expediteur;
    }
  }

  return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Handlers de signaux /////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HandlerSIGINT(int sig)
{
  fprintf(stderr, "(HandlerSIGINT) Signal reçu : %d\n", sig);

  // Suppression de la file de messages
  if ((ret = msgctl(idQ, IPC_RMID, NULL)) == -1)
  {
    perror("(HandlerSIGINT) ERREUR : file de messages non supprimée");
  }
  else
  {
    fprintf(stderr, "(HandlerSIGINT) File de messages supprimée avec succès\n");
  }

  fprintf(stderr, "(HandlerSIGINT) On sort du HandlerSIGINT\n");
  exit(0);
}
