#include <iostream>
#include <time.h>
using namespace std;

#include "Professor.h"
#include "Group.h"
#include "Classroom.h"

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();
void Essai5();

int main(int argc,char* argv[])
{
  int choix;
  bool fini = false;
  
  while(!fini)
  {
    if (argc == 2) { choix = atoi(argv[1]); fini = true; }
    else choix = Menu();
    switch(choix)
    {
      case 1 : Essai1(); break;
      case 2 : Essai2(); break;
      case 3 : Essai3(); break;
      case 4 : Essai4(); break;
      case 5 : Essai5(); break;
      default : fini = true ; break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "----------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 4 ----------------------------------------------------------" << endl;
  cout << "----------------------------------------------------------------------------" << endl;
  cout << " 1. Test de la classe Professor" << endl;
  cout << " 2. Test de la classe Group" << endl;
  cout << " 3. Test de la classe Classroom" << endl;
  cout << " 4. Heritage et virtualite : Test des methodes virtuelles toString() et tuple()" << endl;
  cout << " 5. Test du downcasting et du dynamic-cast" << endl;
  cout << " 6. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/***********************************************************************************************/
// A FAIRE : la classe abstraite Schedulable qui contient les methodes VIRTUELLES PURES toString() et tuple()
//           la classe Professor qui herite de Schedulable et qui contient le lastName (string) et le firstName (string) d'un Professor
//           l'operateur << de Professor
//           l'operateur d'affectation (=) de Professor
void Essai1()
{
  cout << endl << "----- 1.1 Test du constructeur par defaut de Professor ------------------------" << endl;
  Professor p1;
  cout << "--> Voici p1 : " << p1 << endl;
 
  cout << endl << "----- 1.2 Test du constructeur d'initialisation de Professor ------------------" << endl;
  Professor p2(4,"Wagner","Jean-Marc");
  cout << "--> Voici p2 : " << p2 << endl;

  cout << endl << "----- 1.3 Test du constructeur de copie de Professor --------------------------" << endl;
  Professor p3(p2);
  cout << "--> Voici p3 : " << p3 << endl;

  cout << endl << "----- 1.4 Test des getXXX() et setXXX() de Professor --------------------------" << endl;
  p3.setLastName("Quettier");
  p3.setFirstName("Patrick");
  cout << "Last name  : " << p3.getLastName() << endl;
  cout << "First name : " << p3.getFirstName() << endl;
  cout << "id         : " << p3.getId() << endl;

  cout << endl << "----- 1.5 Test des methodes virtuelles de Professor ---------------------------" << endl;
  cout << "toString() --> " << p3.toString() << endl;
  cout << "tuple()    --> " << p3.tuple() << endl;

  cout << endl << "----- 1.6 Test de l'operateur = de Professor ----------------------------------" << endl;
  p1 = p3;
  cout << "--> Voici p1 (apres affectation) : " << p1 << endl;
}

/***********************************************************************************************/
// A FAIRE : la classe Group qui herite de Schedulable, contenant en plus un name (string)
//           les methodes virtuelles toString() et tuple()
//           l'operateur << de Group
//           l'operateur d'affectation (=) de Group

void Essai2()
{
  cout << endl << "----- 2.1 Test du constructeur par defaut --------------------------------------" << endl;
  Group g1;
  cout << "--> Voici g1 : " << g1 << endl;

  cout << endl << "----- 2.2 Test du constructeur d'initialisation de Group ----------------------" << endl;
  Group g2(2,"INFO2 D201");
  cout << "--> Voici g2 : " << g2 << endl;

  cout << endl << "----- 2.3 Test du constructeur de copie de Group ------------------------------" << endl;
  Group g3(g2);
  cout << "--> Voici g3 : " << g3 << endl;

  cout << endl << "----- 2.4 Test des getXXX() et setXXX() de Group ------------------------------" << endl;
  g3.setName("INFO2 R202");
  cout << "Name : " << g3.getName() << endl;
  cout << "id   : " << g3.getId() << endl;

  cout << endl << "----- 2.5 Test des methodes virtuelles de Group -------------------------------" << endl;
  cout << "toString() --> " << g3.toString() << endl;
  cout << "tuple()    --> " << g3.tuple() << endl;

  cout << endl << "----- 2.6 Test de l'operateur = de Group --------------------------------------" << endl;
  g1 = g3;
  cout << "--> Voici g1 (apres affectation) : " << g1 << endl;
}

/***********************************************************************************************/
// A FAIRE : la classe Classroom qui herite de Schedulable, contenant en plus un name (string) et une seatingCapacity (int)
//           les methodes virtuelles toString() et tuple()
//           l'operateur << de Classroom
//           l'operateur d'affectation (=) de Classroom

void Essai3()
{
  cout << endl << "----- 3.1 Test du constructeur par defaut --------------------------------------" << endl;
  Classroom c1;
  cout << "--> Voici c1 : " << c1 << endl;

  cout << endl << "----- 3.2 Test du constructeur d'initialisation de Classroom -----------------------" << endl;
  Classroom c2(11,"AN",100);
  cout << "--> Voici c2 : " << c2 << endl;

  cout << endl << "----- 3.3 Test du constructeur de copie de Classroom -------------------------------" << endl;
  Classroom c3(c2);
  cout << "--> Voici c3 : " << c3 << endl;

  cout << endl << "----- 3.4 Test des getXXX() et setXXX() de Classroom -------------------------------" << endl;
  c3.setName("PV3");
  c3.setSeatingCapacity(35);
  cout << "Name : " << c3.getName() << endl;
  cout << "getSeatingCapacity : " << c3.getSeatingCapacity() << endl;
  cout << "id   : " << c3.getId() << endl;

  cout << endl << "----- 3.5 Test des methodes virtuelles de Classroom --------------------------------" << endl;
  cout << "toString() --> " << c3.toString() << endl;
  cout << "tuple()    --> " << c3.tuple() << endl;

  cout << endl << "----- 3.6 Test de l'operateur = de Classroom ---------------------------------------" << endl;
  c1 = c3;
  cout << "--> Voici c1 (apres affectation) : " << c1 << endl;
}

/******************************************************************************************/
// A FAIRE : normalement rien...
//           juste comprendre et tester le code ci-dessous

void Essai4()
{
  srand((unsigned)time(NULL));

  cout << endl << "----- 4.1 Allocation dynamique de Schedulables ---------------------------------" << endl;
  Schedulable* schedulables[10];

  for (int i=0 ; i<10 ; i++)   // Tracez vos constructeurs !!!
  {
    cout << "schedulables[" << i << "] : ";
    int n = rand()%3;
    switch(n)
    {
      case 0 : schedulables[i] = new Professor(1,"Leonard","Anne");
               cout << "Professor" << endl;
               break;

      case 1 : schedulables[i] = new Group(2,"INFO2 I201");
               cout << "Group" << endl;
               break;

      case 2 : schedulables[i] = new Classroom(3,"LE0",40);
               cout << "Classroom" << endl;
               break;
    }
  }

  cout << endl << "----- 4.2 Test des methodes VIRTUELLE toString() et tuple() --------------------" << endl;
  for (int i=0 ; i<10 ; i++)
    cout << "schedulables[" << i << "] : " << schedulables[i]->toString() << " -- " << schedulables[i]->tuple() << endl;
  
  cout << endl << "----- 4.3 Liberation memoire ---------------------------------------------------" << endl;
  for (int i=0 ; i<10 ; i++) delete schedulables[i];  // Tout se passe-t-il comme vous voulez ?
  // Pour etre plus precis, quid des destructeurs et de la virtualite ?
}

/*********************************************************************************************/
// A FAIRE : normalement rien dans vos classes...
//           juste comprendre et tester le code ci-dessous

void Essai5()
{
  srand((unsigned)time(NULL));

  cout << endl << "----- 5.1 Allocation dynamique de Schedulables ---------------------------------" << endl;
  Schedulable* schedulables[10];

  for (int i=0 ; i<10 ; i++)   // Tracez vos constructeurs !!!
  {
    cout << "schedulables[" << i << "] : ";
    int n = rand()%3;
    switch(n)
    {
      case 0 : schedulables[i] = new Professor(1,"Leonard","Anne");
               cout << "Professor" << endl;
               break;

      case 1 : schedulables[i] = new Group(2,"INFO2 I202");
               cout << "Group" << endl;
               break;

      case 2 : schedulables[i] = new Classroom(3,"PV11",25);
               cout << "Classroom" << endl;
               break;
    }
  }

  cout << endl << "----- 5.2 Test du downcasting et dynamic-cast ----------------------------------" << endl;
  for (int i=0 ; i<10 ; i++)
  {
    cout << "schedulables[" << i << "] ";
    Professor* pProfessor = dynamic_cast<Professor*>(schedulables[i]);
    if (pProfessor != nullptr) cout << "est un Professor : " << pProfessor->getLastName() << " " << pProfessor->getFirstName() << endl;
    Group* pGroup = dynamic_cast<Group*>(schedulables[i]);
    if (pGroup != nullptr) cout << "est un Group : " << pGroup->getName() << endl;
    Classroom* pClassroom = dynamic_cast<Classroom*>(schedulables[i]);
    if (pClassroom != nullptr) cout << "est un Classroom : " << pClassroom->getName() << endl;
  }

  cout << endl << "----- 5.3 Liberation memoire ---------------------------------------------------" << endl;
  for (int i=0 ; i<10 ; i++) delete schedulables[i];
}
