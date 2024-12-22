#include <iostream>
using namespace std;

#include "Timetable.h"

int  Menu();
void Essai1(Timetable&);
void Essai2(Timetable&);
void Essai3(Timetable&);

int main(int argc,char* argv[])
{
  // Creation de l'horaire
  Timetable t;

  // Ajout de locaux
  t.addClassroom("LP01",35);                  // id = 1
  t.addClassroom("AN",110);                   // id = 2
  t.addClassroom("PV12",20);                  // id = 3
  t.addClassroom("PV11",20);                  // id = 4
  t.addClassroom("LE0",25);                   // id = 5

  // Ajout de professeurs
  t.addProfessor("Wagner","Jean-Marc");       // id = 6
  t.addProfessor("Quettier","Patrick");       // id = 7
  t.addProfessor("Leonard","Anne");           // id = 8
  t.addProfessor("Matagne","Xavier");         // id = 9

  // Ajout de groupes
  t.addGroup("INFO2_D201");                   // id = 10
  t.addGroup("INFO2_R202");                   // id = 11
  t.addGroup("INFO2_I201");                   // id = 12
  t.addGroup("INFO2_D202");                   // id = 13
  t.addGroup("INFO2_I202");                   // id = 14
  t.addGroup("INFO2_R201");                   // id = 15

  int choix;
  bool fini = false; 
  while(!fini)
  {
    if (argc == 2) { choix = atoi(argv[1]); fini = true; }
    else choix = Menu();
    switch(choix)
    {
      case 1 : Essai1(t); break;
      case 2 : Essai2(t); break;
      case 3 : Essai3(t); break;
      default : fini = true ; break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 8a --------------------------------------------------------" << endl;
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
void Essai1(Timetable& t)
{
  cout << "////////// Avant ///////////////////////////////////////////////////////////////////////" << endl;
  t.displayClassrooms();

  cout << "////////// Recherches //////////////////////////////////////////////////////////////////" << endl;
  cout << "Classroom d'indice 3 = " << t.findClassroomByIndex(3).toString() << endl;
  cout << "Classroom d'id 1     = " << t.findClassroomById(1).toString() << endl;
  cout << endl;

  cout << "////////// Suppression par indice (1) //////////////////////////////////////////////////" << endl;
  t.deleteClassroomByIndex(1);

  cout << "////////// Apres suppression par indice (1) ////////////////////////////////////////////" << endl;
  t.displayClassrooms();

  cout << "////////// Suppression par id //////////////////////////////////////////////////////////" << endl;
  cout << "--> Suppression Classroom id=4" << endl << endl;
  t.deleteClassroomById(4);

  cout << "////////// Apres suppression par id ////////////////////////////////////////////////////" << endl;
  t.displayClassrooms();
}

/*******************************************************************************************************/
void Essai2(Timetable& t)
{
  cout << "////////// Avant ///////////////////////////////////////////////////////////////////////" << endl;
  t.displayProfessors();

  cout << "////////// Recherches //////////////////////////////////////////////////////////////////" << endl;
  cout << "Professor d'indice 3 = " << t.findProfessorByIndex(3).toString() << endl;
  cout << "Professor d'id 7     = " << t.findProfessorById(7).toString() << endl;
  cout << endl;

  cout << "////////// Suppression par indice (1) //////////////////////////////////////////////////" << endl;
  t.deleteProfessorByIndex(1);

  cout << "////////// Apres suppression par indice (1) ////////////////////////////////////////////" << endl;
  t.displayProfessors();

  cout << "////////// Suppression par id //////////////////////////////////////////////////////////" << endl;
  cout << "--> Suppression Professor id=7" << endl << endl;
  t.deleteProfessorById(7);

  cout << "////////// Apres suppression par id ////////////////////////////////////////////////////" << endl;
  t.displayProfessors();
}

/*******************************************************************************************************/
void Essai3(Timetable& t)
{
  cout << "////////// Avant ///////////////////////////////////////////////////////////////////////" << endl;
  t.displayGroups();

  cout << "////////// Recherches //////////////////////////////////////////////////////////////////" << endl;
  cout << "Group d'indice 3  = " << t.findGroupByIndex(3).toString() << endl;
  cout << "Professor d'id 14 = " << t.findGroupById(14).toString() << endl;
  cout << endl;

  cout << "////////// Suppression par indice (1) //////////////////////////////////////////////////" << endl;
  t.deleteGroupByIndex(1);

  cout << "////////// Apres suppression par indice (1) ////////////////////////////////////////////" << endl;
  t.displayGroups();

  cout << "////////// Suppression par id //////////////////////////////////////////////////////////" << endl;
  cout << "--> Suppression Group id=14" << endl << endl;
  t.deleteGroupById(14);

  cout << "////////// Apres suppression par id ////////////////////////////////////////////////////" << endl;
  t.displayGroups();
}
