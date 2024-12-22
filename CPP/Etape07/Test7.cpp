#include <iostream>
using namespace std;

#include "Time.h"
#include "Timing.h"
#include "Event.h"
using namespace planning;
#include "Classroom.h"
#include "XmlFileSerializer.hpp"

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();
void Essai5();
void Essai6();

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
      case 6 : Essai6(); break;
      default : fini = true ; break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 7 ---------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Test en ecriture du template XmlFileSerializer avec des entiers" << endl;
  cout << " 2. Test en lecture du template XmlFileSerializer avec des entiers" << endl;
  cout << " 3. Test du template XmlFileSerializer avec des objets Time" << endl;
  cout << " 4. Test du template XmlFileSerializer avec des objets Timing" << endl;
  cout << " 5. Test du template XmlFileSerializer avec des objets Event" << endl;
  cout << " 6. Test du template XmlFileSerializer avec des objets Classroom" << endl;
  cout << " 7. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/*******************************************************************************************************/
void Essai1()
{
  cout << "----- 1. Test en écriture du template XmlFileSerializer avec des entiers --------------------" << endl;
  cout << "----- 1.1 Creation du fichier ---------------------------------------------------------------" << endl;
  XmlFileSerializer<int> fsw("integers.xml",XmlFileSerializer<int>::WRITE,"integers");
  cout << "Filename = " << fsw.getFilename() << endl;
  cout << "Collection name  = " << fsw.getCollectionName() << endl;
  cout << "Readable = " << fsw.isReadable() << endl;
  cout << "Writable = " << fsw.isWritable() << endl << endl;

  cout << "----- 1.2 Ecriture dans le fichier ----------------------------------------------------------" << endl;
  for (int i=1 ; i<15 ; i+=2) {
    cout << i << endl;
    fsw.write(i);
  }

  cout << "----- 1.3 Tentative de lecture dans le fichier ouvert en écriture ---------------------------" << endl;
  try {
    int val = fsw.read();
    cout << "val = " << val << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }
}

/*******************************************************************************************************/
void Essai2()
{
  cout << "----- 2. Test en lecture du template XmlFileSerializer avec des entiers ---------------------" << endl;
  cout << "----- 2.1 Test d'ouverture d'un fichier non existant ----------------------------------------" << endl;
  try {
    XmlFileSerializer<int> fsr("XXX.xml",XmlFileSerializer<int>::READ);
    cout << "Filename = " << fsr.getFilename() << endl;
    cout << "Collection name = " << fsr.getCollectionName() << endl;
    cout << "Readable = " << fsr.isReadable() << endl;
    cout << "Writable = " << fsr.isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl << endl;
  }

  cout << "----- 2.2 Tentative d'écriture dans le fichier ouvert en lecture ----------------------------" << endl;
  try {
    XmlFileSerializer<int> fsr("integers.xml",XmlFileSerializer<int>::READ);
    cout << "Filename = " << fsr.getFilename() << endl;
    cout << "Collection name = " << fsr.getCollectionName() << endl;
    cout << "Readable = " << fsr.isReadable() << endl;
    cout << "Writable = " << fsr.isWritable() << endl << endl;
    fsr.write(17); // !!!
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  cout << "----- 2.3 Lecture dans le fichier -----------------------------------------------------------" << endl;
  XmlFileSerializer<int> *fsr = nullptr;
  try {
    fsr = new XmlFileSerializer<int>("integers.xml",XmlFileSerializer<int>::READ);
    cout << "Filename = " << fsr->getFilename() << endl;
    cout << "Collection name = " << fsr->getCollectionName() << endl;
    cout << "Readable = " << fsr->isReadable() << endl;
    cout << "Writable = " << fsr->isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  if (fsr != nullptr) {
    cout << "Debut de lecture..." << endl;
    bool end = false;
    while (!end) {
      try {
        int val = fsr->read();
        cout << "Lu : " << val << endl;
      } catch(const XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::END_OF_FILE) { 
          end = true;
          cout << "Fin de fichier atteinte." << endl;
        } else {
          cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
        }
      }
    }
    cout << "Fin de lecture." << endl;
    delete fsr;
  }
}

/*******************************************************************************************************/
void Essai3()
{
  cout << "----- 3. Test du template XmlFileSerializer avec des objets Time ----------------------------" << endl;
  cout << "----- 3.1 Creation du fichier ---------------------------------------------------------------" << endl;
  XmlFileSerializer<Time> *fsw = new XmlFileSerializer<Time>("times.xml",XmlFileSerializer<Time>::WRITE,"times");
  cout << "Filename = " << fsw->getFilename() << endl;
  cout << "Collection name = " << fsw->getCollectionName() << endl;
  cout << "Readable = " << fsw->isReadable() << endl;
  cout << "Writable = " << fsw->isWritable() << endl << endl;

  cout << "----- 3.2 Ecriture dans le fichier ----------------------------------------------------------" << endl;
  Time t(8,45);
  for (int i=0 ; i<6 ; i++, t++) {
    cout << t.toString() << endl;
    fsw->write(t);
  }
  delete fsw; // pour forcer la fermeture du fichier

  cout << "----- 3.3 Lecture dans le fichier -----------------------------------------------------------" << endl;
  XmlFileSerializer<Time> *fsr = nullptr;
  try {
    fsr = new XmlFileSerializer<Time>("times.xml",XmlFileSerializer<Time>::READ);
    cout << "Filename = " << fsr->getFilename() << endl;
    cout << "Collection name = " << fsr->getCollectionName() << endl;
    cout << "Readable = " << fsr->isReadable() << endl;
    cout << "Writable = " << fsr->isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  if (fsr != nullptr) {
    cout << "Debut de lecture..." << endl;
    bool end = false;
    while (!end) {
      try {
        Time val = fsr->read();
        cout << "Lu : " << val.toString() << endl;
      } catch(const XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::END_OF_FILE) { 
          end = true;
          cout << "Fin de fichier atteinte." << endl;
        } else {
          cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
        }
      }
    }
    cout << "Fin de lecture." << endl;
    delete fsr;
  }
}

/*******************************************************************************************************/
void Essai4()
{
  cout << "----- 4. Test du template XmlFileSerializer avec des objets Timing --------------------------" << endl;
  cout << "----- 4.1 Creation du fichier ---------------------------------------------------------------" << endl;
  XmlFileSerializer<Timing> *fsw = new XmlFileSerializer<Timing>("timings.xml",XmlFileSerializer<Timing>::WRITE,"timings");
  cout << "Filename = " << fsw->getFilename() << endl;
  cout << "Collection name = " << fsw->getCollectionName() << endl;
  cout << "Readable = " << fsw->isReadable() << endl;
  cout << "Writable = " << fsw->isWritable() << endl << endl;

  cout << "----- 4.2 Ecriture dans le fichier ----------------------------------------------------------" << endl;
  Timing t1("Lundi",Time(8,30),Time(120));
  fsw->write(t1);
  cout << t1.toString() << endl;
  Timing t2("Mardi",Time(10,30),Time(90));
  fsw->write(t2);
  cout << t2.toString() << endl;
  Timing t3("Jeudi",Time(13,30),Time(120));
  fsw->write(t3);
  cout << t3.toString() << endl;
  Timing t4("Vendredi",Time(8,30),Time(240));
  fsw->write(t4);
  cout << t4.toString() << endl;
  delete fsw; // pour forcer la fermeture du fichier

  cout << "----- 4.3 Lecture dans le fichier -----------------------------------------------------------" << endl;
  XmlFileSerializer<Timing> *fsr = nullptr;
  try {
    fsr = new XmlFileSerializer<Timing>("timings.xml",XmlFileSerializer<Timing>::READ);
    cout << "Filename = " << fsr->getFilename() << endl;
    cout << "Collection name = " << fsr->getCollectionName() << endl;
    cout << "Readable = " << fsr->isReadable() << endl;
    cout << "Writable = " << fsr->isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  if (fsr != nullptr) {
    cout << "Debut de lecture..." << endl;
    bool end = false;
    while (!end) {
      try {
        Timing val = fsr->read();
        cout << "Lu : " << val.toString() << endl;
      } catch(const XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::END_OF_FILE) { 
          end = true;
          cout << "Fin de fichier atteinte." << endl;
        } else {
          cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
        }
      }
    }
    cout << "Fin de lecture." << endl;
    delete fsr;
  }
}

/*******************************************************************************************************/
void Essai5()
{
  cout << "----- 5. Test du template XmlFileSerializer avec des objets Event ---------------------------" << endl;
  cout << "----- 5.1 Creation du fichier ---------------------------------------------------------------" << endl;
  XmlFileSerializer<Event> *fsw = new XmlFileSerializer<Event>("events.xml",XmlFileSerializer<Event>::WRITE,"events");
  cout << "Filename = " << fsw->getFilename() << endl;
  cout << "Collection name = " << fsw->getCollectionName() << endl;
  cout << "Readable = " << fsw->isReadable() << endl;
  cout << "Writable = " << fsw->isWritable() << endl << endl;

  cout << "----- 5.2 Ecriture dans le fichier ----------------------------------------------------------" << endl;
  Event e1(1,"Theorie C++");
  e1.setTiming(Timing("Lundi",Time(8,30),Time(120)));
  fsw->write(e1);
  cout << e1.toString() << endl;

  Event e2(4,"Labo C/Linux");
  e2.setTiming(Timing("Mardi",Time(10,30),Time(90)));
  fsw->write(e2);
  cout << e2.toString() << endl;

  Event e3(9,"Theorie Java");
  fsw->write(e3);
  cout << e3.toString() << endl;

  Event e4(17,"Labo C++");
  e4.setTiming(Timing("Jeudi",Time(13,30),Time(120)));
  fsw->write(e4);
  cout << e4.toString() << endl;

  Event e5(3,"Seminaire EVS");
  e5.setTiming(Timing("Vendredi",Time(8,30),Time(240)));
  fsw->write(e5);
  cout << e5.toString() << endl;
  delete fsw; // pour forcer la fermeture du fichier

  cout << "----- 5.3 Lecture dans le fichier -----------------------------------------------------------" << endl;
  XmlFileSerializer<Event> *fsr = nullptr;
  try {
    fsr = new XmlFileSerializer<Event>("events.xml",XmlFileSerializer<Event>::READ);
    cout << "Filename = " << fsr->getFilename() << endl;
    cout << "Collection name = " << fsr->getCollectionName() << endl;
    cout << "Readable = " << fsr->isReadable() << endl;
    cout << "Writable = " << fsr->isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  if (fsr != nullptr) {
    cout << "Debut de lecture..." << endl;
    bool end = false;
    while (!end) {
      try {
        Event val = fsr->read();
        cout << "Lu : " << val.toString() << endl;
      } catch(const XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::END_OF_FILE) { 
          end = true;
          cout << "Fin de fichier atteinte." << endl;
        } else {
          cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
        }
      }
    }
    cout << "Fin de lecture." << endl;
    delete fsr;
  }
}

/*******************************************************************************************************/
void Essai6()
{
  cout << "----- 6. Test du template XmlFileSerializer avec des objets Classroom -----------------------" << endl;
  cout << "----- 6.1 Creation du fichier ---------------------------------------------------------------" << endl;
  XmlFileSerializer<Classroom> *fsw = new XmlFileSerializer<Classroom>("classrooms.xml",XmlFileSerializer<Classroom>::WRITE,"classrooms");
  cout << "Filename = " << fsw->getFilename() << endl;
  cout << "Collection name = " << fsw->getCollectionName() << endl;
  cout << "Readable = " << fsw->isReadable() << endl;
  cout << "Writable = " << fsw->isWritable() << endl << endl;

  cout << "----- 6.2 Ecriture dans le fichier ----------------------------------------------------------" << endl;
  Classroom c1(3,"AN",110);
  fsw->write(c1);
  cout << c1.toString() << endl;

  Classroom c2(9,"PV11",25);
  fsw->write(c2);
  cout << c2.toString() << endl;

  Classroom c3(7,"LP02",15);
  fsw->write(c3);
  cout << c3.toString() << endl;
  delete fsw; // pour forcer la fermeture du fichier

  cout << "----- 6.3 Lecture dans le fichier -----------------------------------------------------------" << endl;
  XmlFileSerializer<Classroom> *fsr = nullptr;
  try {
    fsr = new XmlFileSerializer<Classroom>("classrooms.xml",XmlFileSerializer<Classroom>::READ);
    cout << "Filename = " << fsr->getFilename() << endl;
    cout << "Collection name = " << fsr->getCollectionName() << endl;
    cout << "Readable = " << fsr->isReadable() << endl;
    cout << "Writable = " << fsr->isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  if (fsr != nullptr) {
    cout << "Debut de lecture..." << endl;
    bool end = false;
    while (!end) {
      try {
        Classroom val = fsr->read();
        cout << "Lu : " << val.toString() << endl;
      } catch(const XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::END_OF_FILE) { 
          end = true;
          cout << "Fin de fichier atteinte." << endl;
        } else {
          cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
        }
      }
    }
    cout << "Fin de lecture." << endl;
    delete fsr;
  }
}
