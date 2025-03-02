#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "GrilleSDL.h"
#include "Ressources.h"

// Dimensions de la grille de jeu
#define NB_LIGNE 21
#define NB_COLONNE 17

// Macros utilisees dans le tableau tab
#define VIDE 0
#define MUR 1
#define PACMAN 2
#define PACGOM 3
#define SUPERPACGOM 4
#define BONUS 5
#define FANTOME 6

// Autres macros
#define LENTREE 15
#define CENTREE 8

typedef struct
{
  int L;
  int C;
  int couleur;
  int cache;
} S_FANTOME;

typedef struct
{
  int presence;
  pthread_t tid;
} S_CASE;

S_CASE tab[NB_LIGNE][NB_COLONNE];
////////////////////////////////////////////
// Variables globales
////////////////////////////////////////////
pthread_t tidPacMan;
pthread_t tidFantome[4];
pthread_t tidBonus;
pthread_t tidEvent;
pthread_t tidPacGom;
int L = LENTREE;
int C = CENTREE;
int dir = GAUCHE;
int delai = 300; // Initial delay in milliseconds
int nbPacGom = 0;
int score = 0;
int niveau = 1;
pthread_mutex_t mutexTab = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexNbPacGom = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condNbPacGom = PTHREAD_COND_INITIALIZER;

/////////////////////
// Fonctions a coder
/////////////////////
void *PacMan(void *arg);
void *Event(void *arg);
void *PacGom(void *arg);
void DessineGrilleBase();
void Attente(int milli);
void setTab(int l, int c, int presence = VIDE, pthread_t tid = 0);
void DeplacePacMan(int direction);
void handler_SIGINT(int sig);
void handler_SIGHUP(int sig);
void handler_SIGUSR1(int sig);
void handler_SIGUSR2(int sig);

///////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  sigset_t mask;
  struct sigaction sigAct;

  srand((unsigned)time(NULL));

  // Ouverture de la fenetre graphique
  printf("(MAIN %p) Ouverture de la fenetre graphique\n", pthread_self());
  fflush(stdout);
  if (OuvertureFenetreGraphique() < 0)
  {
    printf("Erreur de OuvrirGrilleSDL\n");
    fflush(stdout);
    exit(1);
  }

  DessineGrilleBase();

  pthread_create(&tidPacGom, NULL, PacGom, NULL);
  pthread_create(&tidPacMan, NULL, PacMan, NULL);
  pthread_create(&tidEvent, NULL, Event, NULL);

  pthread_join(tidEvent, NULL);

  // Fermeture de la fenetre
  printf("(MAIN %p) Fermeture de la fenetre graphique...", pthread_self());
  fflush(stdout);
  FermetureFenetreGraphique();
  printf("OK\n");
  fflush(stdout);

  exit(0);
}

//*********************************************************************************************
void Attente(int milli)
{
  struct timespec del;
  del.tv_sec = milli / 1000;
  del.tv_nsec = (milli % 1000) * 1000000;
  nanosleep(&del, NULL);
}

//*********************************************************************************************
void setTab(int l, int c, int presence, pthread_t tid)
{
  tab[l][c].presence = presence;
  tab[l][c].tid = tid;
}

//*********************************************************************************************
void DessineGrilleBase()
{
  int t[NB_LIGNE][NB_COLONNE] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
                                 {1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
                                 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                 {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
                                 {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
                                 {1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
                                 {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                 {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
                                 {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
                                 {1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
                                 {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                                 {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
                                 {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
                                 {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
                                 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  for (int l = 0; l < NB_LIGNE; l++)
    for (int c = 0; c < NB_COLONNE; c++)
    {
      if (t[l][c] == VIDE)
      {
        setTab(l, c);
        EffaceCarre(l, c);
      }
      if (t[l][c] == MUR)
      {
        setTab(l, c, MUR);
        DessineMur(l, c);
      }
    }
}

//*********************************************************************************************
void *PacMan(void *arg)
{
  struct sigaction sa;
  sigset_t mask, oldmask;

  // Armer les signaux
  sa.sa_handler = handler_SIGINT;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);

  sa.sa_handler = handler_SIGHUP;
  sigaction(SIGHUP, &sa, NULL);

  sa.sa_handler = handler_SIGUSR1;
  sigaction(SIGUSR1, &sa, NULL);

  sa.sa_handler = handler_SIGUSR2;
  sigaction(SIGUSR2, &sa, NULL);

  while (1)
  {
    // Bloquer les signaux pendant l'attente
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    pthread_sigmask(SIG_BLOCK, &mask, &oldmask);

    // Attente de 0,3 secondes
    pthread_mutex_lock(&mutexTab);
    int localDelai = delai;
    pthread_mutex_unlock(&mutexTab);
    Attente(localDelai);

    // Débloquer les signaux et vérifier s'il y a des signaux en attente
    pthread_sigmask(SIG_SETMASK, &oldmask, NULL);

    pthread_mutex_lock(&mutexTab);

    // Vérifie si Pac-Man peut se déplacer dans la direction actuelle
    int newL = L;
    int newC = C;
    switch (dir)
    {
    case GAUCHE:
      if (tab[L][C - 1].presence != MUR)
        newC--;
      break;
    case DROITE:
      if (tab[L][C + 1].presence != MUR)
        newC++;
      break;
    case HAUT:
      if (tab[L - 1][C].presence != MUR)
        newL--;
      break;
    case BAS:
      if (tab[L + 1][C].presence != MUR)
        newL++;
      break;
    }

    // Efface l'ancienne position de Pac-Man
    EffaceCarre(L, C);
    setTab(L, C, VIDE);

    // Met à jour la position de Pac-Man si elle a changé
    if (newL != L || newC != C)
    {
      L = newL;
      C = newC;
    }

    // Vérifie si Pac-Man mange un pac-gom ou un super pac-gom
    if (tab[L][C].presence == PACGOM)
    {
      score += 1;
      nbPacGom--;
      pthread_cond_signal(&condNbPacGom);
    }
    else if (tab[L][C].presence == SUPERPACGOM)
    {
      score += 5;
      nbPacGom--;
      pthread_cond_signal(&condNbPacGom);
    }

    // Dessine Pac-Man à la nouvelle position
    DessinePacMan(L, C, dir);
    setTab(L, C, PACMAN);

    pthread_mutex_unlock(&mutexTab);
  }

  return NULL;
}

//*********************************************************************************************
void *Event(void *arg)
{
  EVENT_GRILLE_SDL event;
  int ok = 0;

  while (!ok)
  {
    event = ReadEvent();
    if (event.type == CROIX)
    {
      ok = 1;
      pthread_exit(NULL);
    }
    if (event.type == CLAVIER)
    {
      switch (event.touche)
      {
      case 'q':
        ok = 1;
        break;
      case KEY_RIGHT:
        printf("Fleche droite !\n");
        pthread_kill(tidPacMan, SIGHUP);
        break;
      case KEY_LEFT:
        printf("Fleche gauche !\n");
        pthread_kill(tidPacMan, SIGINT);
        break;
      case KEY_UP:
        printf("Fleche haut !\n");
        pthread_kill(tidPacMan, SIGUSR1);
        break;
      case KEY_DOWN:
        printf("Fleche bas !\n");
        pthread_kill(tidPacMan, SIGUSR2);
        break;
      }
    }
  }

  return NULL;
}

//*********************************************************************************************
void handler_SIGINT(int sig) {
  dir = GAUCHE;
}

void handler_SIGHUP(int sig) {
  dir = DROITE;
}

void handler_SIGUSR1(int sig) {
  dir = HAUT;
}

void handler_SIGUSR2(int sig) {
  dir = BAS;
}

//*********************************************************************************************
void DeplacePacMan(int direction)
{
  pthread_mutex_lock(&mutexTab);

  // Efface l'ancienne position de Pac-Man
  EffaceCarre(L, C);
  setTab(L, C, VIDE);

  // Met à jour la position de Pac-Man en fonction de la direction
  switch (direction)
  {
  case GAUCHE:
    if (tab[L][C - 1].presence != MUR)
      C--;
    break;
  case DROITE:
    if (tab[L][C + 1].presence != MUR)
      C++;
    break;
  case HAUT:
    if (tab[L - 1][C].presence != MUR)
      L--;
    break;
  case BAS:
    if (tab[L + 1][C].presence != MUR)
      L++;
    break;
  }

  // Dessine Pac-Man à la nouvelle position
  DessinePacMan(L, C, direction);
  setTab(L, C, PACMAN);

  pthread_mutex_unlock(&mutexTab);
}

//*********************************************************************************************
void *PacGom(void *arg)
{
  while (1)
  {
    pthread_mutex_lock(&mutexTab);
    nbPacGom = 0;

    // Remplir la grille de pac-goms
    for (int l = 0; l < NB_LIGNE; l++)
    {
      for (int c = 0; c < NB_COLONNE; c++)
      {
        if ((l == 15 && c == 8) || (l == 8 && c == 8) || (l == 9 && c == 8))
          continue;

        if (tab[l][c].presence == VIDE)
        {
          setTab(l, c, PACGOM);
          DessinePacGom(l, c);
          nbPacGom++;
        }
      }
    }

    // Placer les super pac-goms
    setTab(2, 1, SUPERPACGOM);
    DessineSuperPacGom(2, 1);
    setTab(2, 15, SUPERPACGOM);
    DessineSuperPacGom(2, 15);
    setTab(15, 1, SUPERPACGOM);
    DessineSuperPacGom(15, 1);
    setTab(15, 15, SUPERPACGOM);
    DessineSuperPacGom(15, 15);
    nbPacGom += 4;

    pthread_mutex_unlock(&mutexTab);

    // Attendre que tous les pac-goms soient mangés
    pthread_mutex_lock(&mutexNbPacGom);
    while (nbPacGom > 0)
    {
      pthread_cond_wait(&condNbPacGom, &mutexNbPacGom);
      DessineChiffre(12, 22, nbPacGom / 100);
      DessineChiffre(12, 23, (nbPacGom / 10) % 10);
      DessineChiffre(12, 24, nbPacGom % 10);
    }
    pthread_mutex_unlock(&mutexNbPacGom);

    // Incrémenter le niveau et mettre à jour la fenêtre graphique
    niveau++;
    DessineChiffre(14, 22, niveau);

    // Doubler la vitesse de Pac-Man
    pthread_mutex_lock(&mutexTab);
    delai /= 2;
    pthread_mutex_unlock(&mutexTab);
  }

  return NULL;
}