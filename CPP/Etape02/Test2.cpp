#include <stdlib.h>
#include <iostream>
using namespace std;
#include "Time.h"
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

/*******************************************************************************************************/
int Menu()
{
  cout << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TESTS 2 -------------------------------------------------------------------" << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << " 1. Tests de la classe Time" << endl;
  cout << " 2. Tests de la classe Timing (Agregation par valeur avec un objet Time)" << endl;
  cout << " 3. Tests de la classe Event (Agregation par reference avec un objet Timing)" << endl;
  cout << " 4. Tests des variables statiques utiles" << endl;
  cout << " 5. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  return ch;
}

/*******************************************************************************************************/
/*** Tests de la classe Time **************************************************************************/
/*******************************************************************************************************/
void Essai1()
{
  cout << endl << "(1) ***** Test du constructeur par defaut de Time *****************************" << endl;
  {
    Time instant;
    instant.display();
    cout << endl;
  }

  cout << endl << "(2) **** Test des setters/getters **********************************************" << endl;
  {
    Time instant;
    instant.display();
    cout << endl;
    instant.setHour(9);
    instant.setMinute(20);
    instant.display();
    cout << endl << "heure : " << instant.getHour() << endl;
    cout << "Minute : " << instant.getMinute() << endl;
  }

  cout << endl << "(3) ***** Test du constructeur d'initialisation de Time (instant) **************" << endl;
  {
    Time instant(8,5);
    instant.display();
    cout << endl;
  }

  cout << endl << "(4) ***** Test du constructeur d'initialisation de Time (duree) ****************" << endl;
  {
    Time duration(135);
    duration.display();
    cout << endl;
  }

  cout << endl << "(5) ***** Test du constructeur de copie de Time *******************************" << endl;
  {
    Time h1(10,30);
    h1.display();
    cout << endl << "Copie : " ;
    Time h2(h1);
    h2.display();
    cout << endl;
  }
}

/*******************************************************************************************************/
/*** Tests de la classe Timing (Agregation par valeur avec un objet Time) ******************************/
/*******************************************************************************************************/
void Essai2()
{
  cout << endl << "(1) ***** Test du constructeur par defaut de Timing ****************************" << endl;
  {
    Timing t;
    t.display();
    cout << endl;
  }

  cout << endl << "(2) **** Test des setters/getters **********************************************" << endl;
  {
    Timing t;
    t.setDay("Mardi");
    t.setStart(Time(8,20));
    t.setDuration(Time(90));
    t.display();
    cout << endl;
    cout << "Jour  : " << t.getDay() << endl;
    cout << "Debut : ";
    t.getStart().display();
    cout << endl;
    cout << "Duree : ";
    t.getDuration().display();
    cout << endl;
  }

  cout << endl << "(3) ***** Test du constructeur d'initialisation de Timing **********************" << endl;
  {
    Timing t("Vendredi",Time(13,30),Time(120));
    t.display();
    cout << endl;
  }

  cout << endl << "(4) ***** Test du constructeur de copie de Timing ******************************" << endl;
  {
    Time h1(13,0);
    Timing t1("Mercredi",Time(10,30),Time(120));
    cout << "t1 (AVANT) : ";
    t1.display();
    cout << endl;
    {   
      Timing t2(t1);
      cout << "t2 : ";
      t2.display();
      cout << endl;
      t2.setStart(h1);
      cout << "t2 : ";
      t2.display();
      cout << endl;
    }
    cout << "t1 (APRES) : ";
    t1.display();
    cout << endl << endl;
  }
}

/*******************************************************************************************************/
/*** Tests de la classe Event (Agregation par reference d'un objet Timing) *****************************/
/*******************************************************************************************************/
void Essai3()
{
  cout << endl << "(1) ***** Test constructeur par defaut + display *******************************" << endl;
  {
    Event event;
    event.display();
    cout << endl;
  } 

  cout << endl << "(2) ***** Test des setters et getters ******************************************" << endl;
  {
    Event event;
    event.setCode(1);
    event.setTitle("Resto avec Patrick (Merci Patrick :)");
    event.setTiming(Timing("Mardi",Time(20,0),Time(180)));
    event.display();
    cout << endl;
    cout << "Code   = " << event.getCode() << endl;
    cout << "Title  = " << event.getTitle() << endl;
    cout << "Timing = ";
    event.getTiming().display();
    cout << endl;
  }

  cout << endl << "(3) ***** Test du constructeur d'initialisation ********************************" << endl;
  {
    Event event(2,"Cinema avec les potos");
    event.setTiming(Timing("Vendredi",Time(19,30),Time(150)));
    event.display();
    cout << endl;
  }

  cout << endl << "(4) ***** Test du constructeur de copie ****************************************" << endl;
  {
    Event event1(1,"Labo C++");
    event1.setTiming(Timing("Lundi",Time(8,20),Time(90)));
    cout << "event1 (AVANT) : ";
    event1.display();
    cout << endl;
    {   
      Event event2(event1);
      cout << "event2 : ";
      event2.display();
      cout << endl;
      event2.setTiming(Timing("Jeudi",Time(13,30),Time(90)));
      cout << "event2 : ";
      event2.display();
      cout << endl;
    } // de nouveau, les {} assurent que event2 sera detruit avant la suite
    cout << "event1 (APRES) : ";
    event1.display();
    cout << endl << endl;
  }
}

/*******************************************************************************************************/
/*** Tests des variables statiques utiles **************************************************************/
/*******************************************************************************************************/
void Essai4()
{
  cout << endl << "(1) ***** Tests de base des jours de la semaine ********************************" << endl;
  cout << "Premier jour de la semaine : " << Timing::MONDAY << endl;
  // ne pas oublier les autres jours de la semaine...
  cout << "Dernier jour de la semaine : " << Timing::SUNDAY << endl << endl;
  
  cout << endl << "(2) ***** Tests de base de la variable Event::currentCode **********************" << endl;
  cout << "Event::currentCode = " << Event::currentCode << endl;
  Event::currentCode++;
  cout << "Event::currentCode = " << Event::currentCode << endl << endl;

  cout << endl << "(3) ***** Creation d'evenements ************************************************" << endl;
  Event::currentCode = 1;

  Event e1(Event::currentCode,"Theorie C++");
  e1.setTiming(Timing(Timing::TUESDAY,Time(8,20),Time(90)));
  Event::currentCode++;
  cout << "e1 : ";
  e1.display();
  cout << endl;
  cout << "Event::currentCode = " << Event::currentCode << endl;
  cout << "e1.currentCode = " << e1.currentCode << endl << endl;

  Event e2(Event::currentCode,"Labo C++");
  e2.setTiming(Timing(Timing::WEDNESDAY,Time(13,30),Time(120)));
  e2.currentCode++;
  cout << "e2 : ";
  e2.display();
  cout << endl;
  cout << "Event::currentCode = " << Event::currentCode << endl;
  cout << "e1.currentCode = " << e1.currentCode << endl;
  cout << "e2.currentCode = " << e2.currentCode << endl << endl;

  Event e3(Event::currentCode,"Labo UNIX");
  e3.setTiming(Timing(Timing::THURSDAY,Time(10,30),Time(120)));
  Event::currentCode++;
  cout << "e3 : ";
  e3.display();
  cout << endl;
  cout << "Event::currentCode = " << Event::currentCode << endl;
  cout << "e1.currentCode = " << e1.currentCode << endl;
  cout << "e2.currentCode = " << e2.currentCode << endl;
  cout << "e3.currentCode = " << e3.currentCode << endl << endl;
}

