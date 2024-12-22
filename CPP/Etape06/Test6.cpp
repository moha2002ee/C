#include <iostream>
#include <fstream>
using namespace std;

#include "Time.h"
#include "Classroom.h"
#include "Timing.h"
#include "Event.h"

using namespace planning;

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();

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
      default : fini = true ; break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 6 ---------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Sérialisation/Désérialisation d'un objet de la classe Time" << endl;
  cout << " 2. Sérialisation/Désérialisation d'un objet de la classe Classroom" << endl;
  cout << " 3. Sérialisation/Désérialisation d'un objet de la classe Timing" << endl;
  cout << " 4. Sérialisation/Désérialisation d'un objet de la classe Event" << endl;
  cout << " 5. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/*********************************************************************************************/
void Essai1()  // Attention : utilisez les flux texte (<< et >>) !!!!
{
  cout << "----- 1. Sérialisation/Désérialisation d'un objet de la classe Time ------" << endl;
  
  Time h(8,20);
  h.display();
  cout << endl;

  cout << "----- Sauvegarde de l'heure dans le fichier H.xml -----" << endl;
  ofstream fichier1("H.xml",ios::out);
  fichier1 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier1 << h << endl;  // serialisation
  fichier1.close();

  cout << "----- Chargement de l'heure situee dans le fichier H.xml -----" << endl;
  ifstream fichier2("H.xml",ios::in);
  Time t2;
  string tag;
  getline(fichier2,tag);
  fichier2 >> t2;  // deserialisation
  fichier2.close();
  t2.display();
  cout << endl;
}

/*********************************************************************************************/
void Essai2()  // Attention : utilisez les flux texte (<< et >>) !!!!
{
  cout << "----- 2. Sérialisation/Désérialisation d'un objet de la classe Classroom ------" << endl;
  
  Classroom c(2,"Quel bel auditoire !",110);
  cout << "Avant sérialisation : " << c.toString() << endl;

  cout << "----- Sauvegarde du local dans le fichier C.xml -----" << endl;
  ofstream fichier1("C.xml",ios::out);
  fichier1 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier1 << c << endl;
  fichier1.close();

  cout << "----- Chargement du local situe dans le fichier C.xml -----" << endl;
  ifstream fichier2("C.xml",ios::in);
  Classroom c2;
  string tag;
  getline(fichier2,tag);
  fichier2 >> c2;
  fichier2.close();
  cout << "Après sérialisation : " << c.toString() << endl;
}

/*********************************************************************************************/
void Essai3()  // Attention : utilisez les flux texte (<< et >>) !!!!
{
  cout << "----- 3. Sérialisation/Désérialisation d'un objet de la classe Timing ------" << endl;
  
  Timing t("Mardi",Time(8,20),Time(120));
  t.display();
  cout << endl;

  cout << "----- Sauvegarde du timing dans le fichier T.xml -----" << endl;
  ofstream fichier1("T.xml",ios::out);
  fichier1 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier1 << t << endl;
  fichier1.close();

  cout << "----- Chargement du timing situe dans le fichier T.xml -----" << endl;
  ifstream fichier2("T.xml",ios::in);
  string tag;
  Timing t2;
  getline(fichier2,tag);
  fichier2 >> t2;
  fichier2.close();
  t2.display();
  cout << endl;
}

/*********************************************************************************************/
void Essai4()  // Attention : utilisez les flux texte (<< et >>) !!!!
{
  cout << "----- 4. Sérialisation/Désérialisation d'un objet de la classe Event ------" << endl;

  Event e1(17,"Labo C++");
  e1.setTiming(Timing(Timing::TUESDAY,Time(10,30),Time(120)));
  e1.display();
  cout << endl;

  cout << "----- Sauvegarde d'un event avec timing dans le fichier E1.xml -----" << endl;
  ofstream fichier1("E1.xml",ios::out);
  fichier1 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier1 << e1 << endl;
  fichier1.close();

  cout << "----- Chargement de l'event avec timing situe dans le fichier E1.xml -----" << endl;
  ifstream fichier2("E1.xml",ios::in);
  Event e;
  string tag;
  getline(fichier2,tag);
  fichier2 >> e;
  fichier2.close();
  e.display();
  cout << endl << endl;

  Event e2(45,"Theorie C++");
  e2.display();
  cout << endl;

  cout << "----- Sauvegarde d'un event sans timing dans le fichier E2.xml -----" << endl;
  ofstream fichier3("E2.xml",ios::out);
  fichier3 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier3 << e2 << endl;
  fichier3.close();

  cout << "----- Chargement de l'event sans timing situe dans le fichier E2.xml -----" << endl;
  ifstream fichier4("E2.xml",ios::in);
  Event E;
  getline(fichier4,tag);
  fichier4 >> E;
  fichier4.close();
  E.display();
  cout << endl;
}
