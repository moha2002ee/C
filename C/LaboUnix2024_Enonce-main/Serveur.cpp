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
#include "protocole.h" // contient la cle et la structure d'un message
#include "FichierClient.h"

int idQ, idShm, idSem;
int fdPipe[2];
TAB_CONNEXIONS *tab;
void handlerSIGINT(int sig);
void afficheTab();
void handlerSIGCHLD(int sig);
char buffer[20];
void envoiRequete(MESSAGE *messageretour);
void lesTablesConnexions(MESSAGE *messageAller, MESSAGE *messageRetour);
void reponseDuLogin(MESSAGE *reponse , int  , int , const char *);
int main()
{
  // Armement des signaux
  // TO DO
  struct sigaction A;
  A.sa_handler = handlerSIGINT;
  A.sa_flags = 0;
  sigemptyset(&A.sa_mask);
  sigaction(SIGINT, &A, NULL);
  struct sigaction B;
  B.sa_handler = handlerSIGCHLD;
  B.sa_flags = 0;
  sigemptyset(&B.sa_mask);
  sigaction(SIGCHLD, &B, NULL);
  if ((idShm = shmget(CLE, 52, IPC_CREAT | IPC_EXCL | 0777)) == -1)
  {
    perror("(SERV) il y a une erreur pour la  creation de memoire partage  ");
    exit(1);
  }

  // Creation des ressources
  // Creation de la file de message
  fprintf(stderr, "(SERVEUR %d) Creation de la file de messages\n", getpid());
  if ((idQ = msgget(CLE, IPC_CREAT | IPC_EXCL | 0600)) == -1) // CLE definie dans protocole.h
  {
    perror("(SERVEUR) Erreur de msgget");
    exit(1);
  }

  // TO BE CONTINUED

  // Creation du pipe
  // TO DO
  if (pipe(fdPipe) == -1)
  {
    perror("(SER) il y a un probleme avec le pipre ");
    exit(1);
  }

  // Initialisation du tableau de connexions
  tab = (TAB_CONNEXIONS *)malloc(sizeof(TAB_CONNEXIONS));

  for (int i = 0; i < 6; i++)
  {
    tab->connexions[i].pidFenetre = 0;
    strcpy(tab->connexions[i].nom, "");
    tab->connexions[i].pidCaddie = 0;
  }
  tab->pidServeur = getpid();
  tab->pidPublicite = 0;

  afficheTab();

  // Creation du processus Publicite (étape 2)
  // TO DO

  // Creation du processus AccesBD (étape 4)
  // TO DO

  MESSAGE m;
  MESSAGE reponse;

  while (1)
  {
    fprintf(stderr, "(SERVEUR %d) Attente d'une requete...\n", getpid());
    if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), 1, 0) == -1)
    {
      perror("(SERVEUR) Erreur de msgrcv");
      msgctl(idQ, IPC_RMID, NULL);
      exit(1);
    }

    switch (m.requete)
    {
    case CONNECT: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete CONNECT reçue de %d\n", getpid(), m.expediteur);
      lesTablesConnexions(&m, &reponse);
      break;

    case DECONNECT: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete DECONNECT reçue de %d\n", getpid(), m.expediteur);
      lesTablesConnexions(&m, &reponse);
      break;
    case LOGIN: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete LOGIN reçue de %d : --%d--%s--%s--\n", getpid(), m.expediteur, m.data1, m.data2, m.data3);
      break;

    case LOGOUT: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete LOGOUT reçue de %d\n", getpid(), m.expediteur);
      break;

    case UPDATE_PUB: // TO DO
      break;

    case CONSULT: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete CONSULT reçue de %d\n", getpid(), m.expediteur);
      break;

    case ACHAT: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete ACHAT reçue de %d\n", getpid(), m.expediteur);
      break;

    case CADDIE: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete CADDIE reçue de %d\n", getpid(), m.expediteur);
      break;

    case CANCEL: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete CANCEL reçue de %d\n", getpid(), m.expediteur);
      break;

    case CANCEL_ALL: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete CANCEL_ALL reçue de %d\n", getpid(), m.expediteur);
      break;

    case PAYER: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete PAYER reçue de %d\n", getpid(), m.expediteur);
      break;

    case NEW_PUB: // TO DO
      fprintf(stderr, "(SERVEUR %d) Requete NEW_PUB reçue de %d\n", getpid(), m.expediteur);
      break;
    }
    afficheTab();
  }
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

void lesTablesConnexions(MESSAGE *messageAller, MESSAGE *messageRetour)
{
  for (int i = 0; i < 6; i++)
  {
    switch (messageAller->requete)
    {
    case CONNECT:
      if (tab->connexions[i].pidFenetre == 0)
      {
        tab->connexions[i].pidFenetre = messageAller->expediteur;
        i = 10;
      }
      break;
    case DECONNECT:
      if (tab->connexions[i].pidFenetre == messageAller->expediteur)
      {
        tab->connexions[i].pidFenetre = 0;

        i = 10;
      }
      break;
    case LOGIN:
      if (tab->connexions[i].pidFenetre == messageAller->expediteur)
      {
        if (messageRetour->data1 == 1)
        {
          strcpy(tab->connexions[i].nom, messageAller->data2);
          messageRetour->expediteur = messageAller->expediteur;
          envoiRequete(messageRetour);
        }
      }
      break;
    case LOGOUT:
      if (tab->connexions[i].pidFenetre == messageAller->expediteur)
      {
        messageRetour->requete = LOGOUT;
        messageRetour->type = tab->connexions[i].pidCaddie;
        if (messageRetour->type != 0)
          envoiRequete(messageRetour);
        strcpy(tab->connexions[i].nom, "");
        i = 10;
      }
      break;
    case UPDATE_PUB:
      break;
    case CONSULT:
      break;
    case ACHAT:
      break;
    case CADDIE:
      break;
    }
  }
}
void envoiRequete(MESSAGE *messageRetour)
{
  if (msgsnd(idQ, messageRetour, sizeof(MESSAGE) - sizeof(long), 0) == -1)
  {
    perror("(SERVEUR)Erreur envoi reponse\n");
    exit(1);
  }
}
void login(MESSAGE *messageAller, MESSAGE *messageRetour)
{
  int pos;
  if (messageAller->data1 == 1)
  {
    if (ilEstDispo(messageAller->data2))
    {
      reponseDuLogin(messageRetour, 0, LOGIN, "il y a deja un client ");
      lesTablesConnexions(messageAller, messageRetour);
    }
    else
    {
      ajoutClient(messageAller->data2, messageAller->data3);
      reponseDuLogin(messageRetour, 1, LOGIN, "Bienvenue");
    }
  }
  else
  {
    pos = ilEstDispo(messageAller->data2);
    if (pos)
    {
      if (verifMDP(pos, messageAller->data3))
      {
        reponseDuLogin(messageRetour, 1, LOGIN, "Re-Bonjour chef ");
        lesTablesConnexions(messageAller, messageRetour);
      }
      else
      {
        reponseDuLogin(messageRetour, 0, LOGIN, "le mot de passe est faux ");
        lesTablesConnexions(messageAller, messageRetour);
      }
    }
    else
    {
      reponseDuLogin(messageRetour, 0, LOGIN, "Vous etes inconnu");
      lesTablesConnexions(messageAller, messageRetour);
    }
  }
}
void reponseDuLogin(MESSAGE *messageRetour, int typecl, int typeRequete, const char *rep)
{
  messageRetour->requete = typeRequete;
  messageRetour->data1 = typecl;
  strcpy(messageRetour->data4, rep);
}
void handlerSIGINT(int sig ){
kill(tab->pidPublicite,SIGINT) ; 
if
}
void handlerSIGCHLD(int sig){
  int id , status ; 
  id =  wait(&status);
  if (WIFEXITED(status)){
    for (int i = 0; i<6;i++){
      if (tab->connexions[i].pidCaddie==id ){
        tab->connexions[i].pidCaddie = 0;
        i=10;
      }
    }
  } 
}