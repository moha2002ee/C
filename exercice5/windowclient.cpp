#include "windowclient.h"
#include "ui_windowclient.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

extern WindowClient *w;

#include "protocole.h" // contient la cle et la structure d'un message

extern char nomClient[40];
int idQ; // identifiant de la file de message
MESSAGE requete; 

void HandlerSIGUSR1(int sig);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowClient::WindowClient(QWidget *parent):QMainWindow(parent),ui(new Ui::WindowClient)
{
  ui->setupUi(this);
  setWindowTitle(nomClient);

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(CLIENT %s %d) Recuperation de l'id de la file de messages\n",nomClient,getpid());
  // TO DO (etape 2)
  if((idQ = msgget(CLE, 0)) == -1)
  {
    perror("Erreur lors de la récuperations de la file de message 1234\n");
  }

  // Envoi d'une requete d'identification
  requete.type = 1;
  strcpy(requete.texte, "Authentification !");
  requete.expediteur = getpid();

 if (msgsnd(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
 {
    fprintf(stderr, "Erreur msgsnd client pid: %d, message non envoyé\n", getpid());
    perror("Détail de l'erreur");
    fprintf(stderr, "Structure:\t\ntype: %ld\ntexte: %s\nexpediteur: %d\nsizeofMessage: %ld\nsizeofMessage - long: %ld\nValeur de la clé: %d\n", 
      requete.type ,requete.texte, requete.expediteur, sizeof(MESSAGE), (sizeof(MESSAGE) - sizeof(long)), CLE);
 }

  // Armement du signal SIGUSR1
   struct sigaction A;
   A.sa_handler = HandlerSIGUSR1;
   sigemptyset(&A.sa_mask);
   A.sa_flags = 0;
   
   if (sigaction(SIGUSR1,&A,NULL) ==-1)
   {
     perror("Erreur de sigaction");
     exit(1);
   }
}

WindowClient::~WindowClient()
{
  delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setRecu(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditRecu->clear();
    return;
  }
  ui->lineEditRecu->setText(Text);
}

void WindowClient::setAEnvoyer(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditEnvoyer->clear();
    return;
  }
  ui->lineEditEnvoyer->setText(Text);
}

const char* WindowClient::getAEnvoyer()
{
  if (ui->lineEditEnvoyer->text().size())
  { 
    strcpy(aEnvoyer,ui->lineEditEnvoyer->text().toStdString().c_str());
    return aEnvoyer;
  }
  return NULL;
}

const char* WindowClient::getRecu()
{
  if (ui->lineEditRecu->text().size())
  { 
    strcpy(recu,ui->lineEditRecu->text().toStdString().c_str());
    return recu;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_pushButtonEnvoyer_clicked()
{
  fprintf(stderr,"Clic sur le bouton Envoyer\n");
  // TO DO (etapes 2, 3, 4)
  requete.type = 1;
  strcpy(requete.texte, getAEnvoyer());
  requete.expediteur = getpid();

 if (msgsnd(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
 {
    fprintf(stderr, "Erreur msgsnd client pid: %d, message non envoyé\n", getpid());
    perror("Détail de l'erreur");
    fprintf(stderr, "Structure:\t\ntype: %ld\ntexte: %s\nexpediteur: %d\nsizeofMessage: %ld\nsizeofMessage - long: %ld\nValeur de la clé: %d\n", 
      requete.type ,requete.texte, requete.expediteur, sizeof(MESSAGE), (sizeof(MESSAGE) - sizeof(long)), CLE);
 }

}

void WindowClient::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  exit(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 4)
void HandlerSIGUSR1(int sig)
{
  fprintf(stderr, "(SIGUSR1) signal recu: %d", sig);
  while (1)
{
    int ret;

    ret = msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), getpid(), 0);
    
    if (ret == -1) 
    {
        perror("Erreur de réception (CLIENT)");
        w->setRecu("ERREUR");
        break; 
    } 
    else if (ret > 0) {
        fprintf(stderr, "Message reçu avec succès\n");
        w->setRecu(requete.texte);
        break; // Sortir de la boucle après réception du message
    }
}

}

