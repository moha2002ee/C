#include <iostream>
using namespace std;

#include "Timetable.h"

int  Menu();
void Essai1();
void Essai2();
void Essai3();

int main(int argc,char* argv[])
{
  // Creation de l'horaire
  // inutile !

  // Ajout de locaux
  Timetable::getInstance().addClassroom("LP01",35);                  // id = 1
  Timetable::getInstance().addClassroom("AN",110);                   // id = 2
  Timetable::getInstance().addClassroom("PV12",20);                  // id = 3
  Timetable::getInstance().addClassroom("PV11",20);                  // id = 4
  Timetable::getInstance().addClassroom("LE0",25);                   // id = 5

  // Ajout de professeurs
  Timetable::getInstance().addProfessor("Wagner","Jean-Marc");       // id = 6
  Timetable::getInstance().addProfessor("Quettier","Patrick");       // id = 7
  Timetable::getInstance().addProfessor("Leonard","Anne");           // id = 8
  Timetable::getInstance().addProfessor("Matagne","Xavier");         // id = 9

  // Ajout de groupes
  Timetable::getInstance().addGroup("INFO2_D201");                   // id = 10
  Timetable::getInstance().addGroup("INFO2_R202");                   // id = 11
  Timetable::getInstance().addGroup("INFO2_I201");                   // id = 12
  Timetable::getInstance().addGroup("INFO2_D202");                   // id = 13
  Timetable::getInstance().addGroup("INFO2_I202");                   // id = 14
  Timetable::getInstance().addGroup("INFO2_R201");                   // id = 15

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
      default : fini = true ; break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 8b --------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Tests du conteneur d'objets Classroom de la classe Timetable" << endl;
  cout << " 2. Tests du conteneur d'objets Professor de la classe Timetable" << endl;
  cout << " 3. Tests du conteneur d'objets Group de la classe Timetable" << endl;
  cout << " 4. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/*******************************************************************************************************/
void Essai1()
{
  cout << "////////// Avant ///////////////////////////////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayClassrooms();

  cout << "////////// Recherches //////////////////////////////////////////////////////////////////" << endl;
  cout << "Classroom d'indice 3 = " << Timetable::getInstance().findClassroomByIndex(3).toString() << endl;
  cout << "Classroom d'id 1     = " << Timetable::getInstance().findClassroomById(1).toString() << endl;
  cout << endl;

  cout << "////////// Suppression par indice (1) //////////////////////////////////////////////////" << endl;
  Timetable::getInstance().deleteClassroomByIndex(1);

  cout << "////////// Apres suppression par indice (1) ////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayClassrooms();

  cout << "////////// Suppression par id //////////////////////////////////////////////////////////" << endl;
  cout << "--> Suppression Classroom id=4" << endl << endl;
  Timetable::getInstance().deleteClassroomById(4);

  cout << "////////// Apres suppression par id ////////////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayClassrooms();
}

/*******************************************************************************************************/
void Essai2()
{
  cout << "////////// Avant ///////////////////////////////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayProfessors();

  cout << "////////// Recherches //////////////////////////////////////////////////////////////////" << endl;
  cout << "Professor d'indice 3 = " << Timetable::getInstance().findProfessorByIndex(3).toString() << endl;
  cout << "Professor d'id 7     = " << Timetable::getInstance().findProfessorById(7).toString() << endl;
  cout << endl;

  cout << "////////// Suppression par indice (1) //////////////////////////////////////////////////" << endl;
  Timetable::getInstance().deleteProfessorByIndex(1);

  cout << "////////// Apres suppression par indice (1) ////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayProfessors();

  cout << "////////// Suppression par id //////////////////////////////////////////////////////////" << endl;
  cout << "--> Suppression Professor id=7" << endl << endl;
  Timetable::getInstance().deleteProfessorById(7);

  cout << "////////// Apres suppression par id ////////////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayProfessors();
}

/*******************************************************************************************************/
void Essai3()
{
  cout << "////////// Avant ///////////////////////////////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayGroups();

  cout << "////////// Recherches //////////////////////////////////////////////////////////////////" << endl;
  cout << "Group d'indice 3  = " << Timetable::getInstance().findGroupByIndex(3).toString() << endl;
  cout << "Professor d'id 14 = " << Timetable::getInstance().findGroupById(14).toString() << endl;
  cout << endl;

  cout << "////////// Suppression par indice (1) //////////////////////////////////////////////////" << endl;
  Timetable::getInstance().deleteGroupByIndex(1);

  cout << "////////// Apres suppression par indice (1) ////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayGroups();

  cout << "////////// Suppression par id //////////////////////////////////////////////////////////" << endl;
  cout << "--> Suppression Group id=14" << endl << endl;
  Timetable::getInstance().deleteGroupById(14);

  cout << "////////// Apres suppression par id ////////////////////////////////////////////////////" << endl;
  Timetable::getInstance().displayGroups();
}
