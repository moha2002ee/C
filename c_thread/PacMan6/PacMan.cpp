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
pthread_t tidScore;
pthread_t tidCompteurFantomes;
int L = LENTREE;
int C = CENTREE;
int dir = GAUCHE;
int delai = 300; // Initial delay in milliseconds
int nbPacGom = 0;
int score = 0;
int niveau = 1;
bool MAJScore = false;
int nbRouge = 0;
int nbVert = 0;
int nbMauve = 0;
int nbOrange = 0;
pthread_mutex_t mutexNbFantomes = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condNbFantomes = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutexTab = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexNbPacGom = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexScore = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condNbPacGom = PTHREAD_COND_INITIALIZER;
pthread_cond_t condScore = PTHREAD_COND_INITIALIZER;
pthread_key_t fantome_key;

/////////////////////
// Fonctions a coder
/////////////////////
void *PacMan(void *arg);
void *Event(void *arg);
void *PacGom(void *arg);
void *Score(void *arg);
void *Bonus(void *arg);
void *Fantome(void *arg);
void *CompteurFantome(void *arg);
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
  sigAct.sa_handler = handler_SIGINT;
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;
  sigaction(SIGINT, &sigAct, NULL);

  sigAct.sa_handler = handler_SIGHUP;
  sigaction(SIGHUP, &sigAct, NULL);

  sigAct.sa_handler = handler_SIGUSR1;
  sigaction(SIGUSR1, &sigAct, NULL);

  sigAct.sa_handler = handler_SIGUSR2;
  sigaction(SIGUSR2, &sigAct, NULL);
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
  pthread_create(&tidScore, NULL, Score, NULL);
  pthread_create(&tidBonus, NULL, Bonus, NULL); // Ajout du thread Bonus
  pthread_create(&tidCompteurFantomes,NULL,CompteurFantome,NULL);

  pthread_join(tidEvent, NULL);
  pthread_join(tidPacMan, NULL);
  pthread_join(tidPacGom, NULL);
  pthread_join(tidScore, NULL);
  pthread_join(tidBonus, NULL);
  pthread_join(tidCompteurFantomes, NULL);
  

  // Fermeture de la fenetre
  printf("(MAIN %p) Fermeture de la fenetre graphique...", pthread_self());
  pthread_mutex_destroy(&mutexTab);
  pthread_mutex_destroy(&mutexNbPacGom);
  pthread_mutex_destroy(&mutexScore);
  pthread_cond_destroy(&condNbPacGom);
  pthread_cond_destroy(&condScore);
  pthread_key_delete(fantome_key);

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

    // Vérifie si Pac-Man mange un pac-gom, un super pac-gom ou un bonus
    if (tab[L][C].presence == PACGOM)
    {
      pthread_mutex_lock(&mutexScore);
      score += 1;
      nbPacGom--;
      MAJScore = true;
      pthread_cond_signal(&condScore);
      pthread_mutex_unlock(&mutexScore);
      pthread_cond_signal(&condNbPacGom);
    }
    else if (tab[L][C].presence == SUPERPACGOM)
    {
      pthread_mutex_lock(&mutexScore);
      score += 5;
      nbPacGom--;
      MAJScore = true;
      pthread_cond_signal(&condScore);
      pthread_mutex_unlock(&mutexScore);
      pthread_cond_signal(&condNbPacGom);
    }
    else if (tab[L][C].presence == BONUS)
    {
      pthread_mutex_lock(&mutexScore);
      score += 30;
      MAJScore = true;
      pthread_cond_signal(&condScore);
      pthread_mutex_unlock(&mutexScore);
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

//*********************************************************************************************
void *Score(void *arg)
{
  while (1)
  {
    pthread_mutex_lock(&mutexScore);
    while (!MAJScore)
    {
      pthread_cond_wait(&condScore, &mutexScore);
    }

    // Afficher le score dans les cases (16,22), (16,23), (16,24) et (16,25)
    DessineChiffre(16, 22, score / 1000);
    DessineChiffre(16, 23, (score / 100) % 10);
    DessineChiffre(16, 24, (score / 10) % 10);
    DessineChiffre(16, 25, score % 10);

    MAJScore = false;
    pthread_mutex_unlock(&mutexScore);
  }

  return NULL;
}
void *Bonus(void *arg)
{
  while (1)
  {
    // Attente d'un laps de temps aléatoire entre 10 et 20 secondes
    int waitTime = 10000 + rand() % 10000;
    Attente(waitTime);

    pthread_mutex_lock(&mutexTab);

    // Recherche d'une case libre pour déposer le bonus
    int l, c;
    do
    {
      l = rand() % NB_LIGNE;
      c = rand() % NB_COLONNE;
    } while (tab[l][c].presence != VIDE);

    // Dépose le bonus
    setTab(l, c, BONUS);
    DessineBonus(l, c);

    pthread_mutex_unlock(&mutexTab);

    // Attente de 10 secondes
    Attente(10000);

    pthread_mutex_lock(&mutexTab);

    // Vérifie si le bonus est toujours présent
    if (tab[l][c].presence == BONUS)
    {
      // Retire le bonus
      setTab(l, c, VIDE);
      EffaceCarre(l, c);
    }

    pthread_mutex_unlock(&mutexTab);
  }

  return NULL;
}
void *Fantome(void *arg)
{
    if (!arg) {
        fprintf(stderr, "Erreur : pointeur fantôme NULL\n");
        pthread_exit(NULL);
    }
    
    S_FANTOME *fantome = (S_FANTOME *)arg;
    int dir = HAUT;

    printf("Fantôme créé : couleur=%d, position=(%d, %d)\n", fantome->couleur, fantome->L, fantome->C);

    // Stocker la structure du fantôme dans la clé spécifique au thread
    if (pthread_setspecific(fantome_key, fantome) != 0) {
        fprintf(stderr, "Erreur : pthread_setspecific a échoué\n");
        pthread_exit(NULL);
    }

    // Vérifier si les coordonnées du fantôme sont valides
    if (fantome->L < 0 || fantome->L >= NB_LIGNE || fantome->C < 0 || fantome->C >= NB_COLONNE) {
        fprintf(stderr, "Erreur : position initiale du fantôme invalide (%d, %d)\n", fantome->L, fantome->C);
        pthread_exit(NULL);
    }
    
    pthread_mutex_lock(&mutexTab);
    fantome->cache = tab[fantome->L][fantome->C].presence;  // Sauvegarder l'état de la case
    setTab(fantome->L, fantome->C, FANTOME, pthread_self());
    DessineFantome(fantome->L, fantome->C, fantome->couleur, dir);
    pthread_mutex_unlock(&mutexTab);

    while (1) {
        int newL = fantome->L, newC = fantome->C;
        switch (dir) {
            case HAUT:    newL--; break;
            case BAS:     newL++; break;
            case GAUCHE:  newC--; break;
            case DROITE:  newC++; break;
        }

        pthread_mutex_lock(&mutexTab);
        if (newL >= 0 && newL < NB_LIGNE && newC >= 0 && newC < NB_COLONNE && tab[newL][newC].presence != MUR && tab[newL][newC].presence != FANTOME) {
            if (tab[newL][newC].presence == PACMAN) {
                printf("Fantôme a attrapé Pac-Man!\n");
                if (tidPacMan) pthread_cancel(tidPacMan);
                pthread_mutex_unlock(&mutexTab);
                
                pthread_exit(NULL);
            }

            setTab(fantome->L, fantome->C, fantome->cache, 0);
            EffaceCarre(fantome->L, fantome->C);
            if (fantome->cache == PACGOM) {
                DessinePacGom(fantome->L, fantome->C);
            } else if (fantome->cache == BONUS) {
                DessineBonus(fantome->L, fantome->C);
            } else if (fantome->cache == SUPERPACGOM) {
                DessineSuperPacGom(fantome->L, fantome->C);
            }

            fantome->cache = tab[newL][newC].presence;
            fantome->L = newL;
            fantome->C = newC;

            setTab(fantome->L, fantome->C, FANTOME, pthread_self());
            DessineFantome(fantome->L, fantome->C, fantome->couleur, dir);
        } else {
            int directions[4] = {HAUT, BAS, GAUCHE, DROITE};
            int possible_directions[4];
            int count = 0;

            for (int i = 0; i < 4; i++) {
                int testL = fantome->L, testC = fantome->C;
                switch (directions[i]) {
                    case HAUT:    testL--; break;
                    case BAS:     testL++; break;
                    case GAUCHE:  testC--; break;
                    case DROITE:  testC++; break;
                }
                if (testL >= 0 && testL < NB_LIGNE && testC >= 0 && testC < NB_COLONNE && tab[testL][testC].presence != MUR && tab[testL][testC].presence != FANTOME) {
                    possible_directions[count++] = directions[i];
                }
            }
            if (count > 0) {
                dir = possible_directions[rand() % count];
            } else {
                dir = (dir + 2) % 4; // Inverser la direction pour éviter un blocage
            }
        }
        pthread_mutex_unlock(&mutexTab);

        Attente((5 * delai) / 3);
    }
    return NULL;
}
void *CompteurFantome(void *arg){
  while (1) {
    pthread_mutex_lock(&mutexNbFantomes);
    while (nbRouge == 2 && nbVert == 2 && nbMauve == 2 && nbOrange == 2) {
        pthread_cond_wait(&condNbFantomes, &mutexNbFantomes);
    }

    S_FANTOME* fantome = (S_FANTOME*)malloc(sizeof(S_FANTOME));
    fantome->L = 9;
    fantome->C = 8;
    fantome->cache = VIDE;

    if (nbRouge < 2) {
        fantome->couleur = ROUGE;
        nbRouge++;
    } else if (nbVert < 2) {
        fantome->couleur = VERT;
        nbVert++;
    } else if (nbMauve < 2) {
        fantome->couleur = MAUVE;
        nbMauve++;
    } else if (nbOrange < 2) {
        fantome->couleur = ORANGE;
        nbOrange++;
    }

    pthread_t tid;
    pthread_create(&tid, NULL, Fantome, fantome);
    pthread_mutex_unlock(&mutexNbFantomes);
}
return NULL;
}