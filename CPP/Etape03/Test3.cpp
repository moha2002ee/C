//#include <stdlib.h>
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
void Essai5();
void Essai6();
void Essai7();

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
      case 7 : Essai7(); break;
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
  cout << "--- JEU DE TESTS 3 -------------------------------------------------------------------" << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << " 1. Tests de l'operateur = de la classe Time" << endl;
  cout << " 2. Tests de l'operateur + de la classe Time" << endl;
  cout << " 3. Tests de l'operateur - de la classe Time" << endl;
  cout << " 4. Tests des operateurs < > == de la classe Time" << endl;
  cout << " 5. Test des operateurs << et >> de la classe Time" << endl;
  cout << " 6. Tests des operateurs de pre/post in(de)crementation de la classe Time" << endl;
  cout << " 7. Tests des operateurs < > == de la classe Timing" << endl;
  cout << " 8. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/*******************************************************************************************************/
/*** Tests des operateurs = de la classe Time **********************************************************/
/*******************************************************************************************************/
void Essai1()
{
  cout << "********************************************************************" << endl;
  cout << "(1) ***** Test de l'operateur d'affectation de Time ****************" << endl;
  cout << "********************************************************************" << endl;
  {
    Time h1(8,20);
    cout << "h1 (avant affectation) : ";
    h1.display();
    Time h2;
    cout << endl << ">>>>> h2 = h1;" << endl;
    h2 = h1;
    cout << "h2 : ";
    h2.display();
    cout << endl << "h1 (apres affectation) : ";
    h1.display();
    cout << endl;
  }
}

/*******************************************************************************************************/
/*** Tests des operateurs + de la classe Time **********************************************************/
/*******************************************************************************************************/
void Essai2()
{
  cout << endl << "********************************************************************" << endl;
  cout <<         "(1) ***** Test de l'operateur (Time + int) *************************" << endl;
  cout <<         "********************************************************************" << endl;
  {
    Time h(13,30);
    cout << "h (avant) : ";
    h.display();
    Time h2;
    cout << endl << ">>>>> h2 = h + 10;" << endl;
    h2 = h + 10;
    cout << "h2 : ";
    h2.display();
    cout << endl << ">>>>> h2 = h2 + 30;" << endl;
    h2 = h2 + 30;
    cout << "h2 : ";
    h2.display();
    cout << endl << "h (apres) : "; // h ne doit pas etre modifie !!!!
    h.display();
    cout << endl;
  }

  cout << endl << "********************************************************************" << endl;
  cout <<         "(2) ***** Test de l'operateur (int + Time) *************************" << endl;
  cout <<         "********************************************************************" << endl;
  {
    Time h(13,30);
    cout << "h (avant) : ";
    h.display();
    Time h2;
    cout << endl << ">>>>> h2 = 10 + h;" << endl;
    h2 = 10 + h;
    cout << "h2 : ";
    h2.display();
    cout << endl << ">>>>> h2 = 30 + h2;" << endl;
    h2 = 30 + h2;
    cout << "h2 : ";
    h2.display();
    cout << endl << "h (apres) : "; // h ne doit pas etre modifie !!!!
    h.display();
    cout << endl;
  }

  cout << endl << "********************************************************************" << endl;
  cout <<         "(3) ***** Test de l'operateur (Time + Time) ************************" << endl;
  cout <<         "********************************************************************" << endl;
  {
    Time start(13,30);
    cout << "start : ";
    start.display();
    Time inter;
    cout << endl << ">>>>> inter = start + Time(90);" << endl;
    inter = start + Time(90);
    cout << "inter : ";
    inter.display();
    Time end;
    cout << endl << ">>>>> end = inter + Time(1,20);" << endl;
    end = inter + Time(1,20);
    cout << "end : ";
    end.display();
    cout << endl;
  }
}

/*******************************************************************************************************/
/*** Tests de l'operateur - de la classe Time **********************************************************/
/*******************************************************************************************************/
void Essai3()
{
  cout << endl << "********************************************************************" << endl;
  cout <<         "(1) ***** Test de l'operateur (Time - int) *************************" << endl;
  cout <<         "********************************************************************" << endl;
  {
    Time h(16,50);
    cout << "h (avant) : ";
    h.display();
    Time h2;
    cout << endl << ">>>>> h2 = h - 30;" << endl;
    h2 = h - 30;
    cout << "h2 : ";
    h2.display();
    cout << endl << ">>>>> h2 = h2 - 70;" << endl;
    h2 = h2 - 70;
    cout << "h2 : ";
    h2.display();
    cout << endl << "h (apres) : "; // h ne doit pas etre modifie !!!!
    h.display();
    cout << endl;
  }

  cout << endl << "********************************************************************" << endl;
  cout <<         "(2) ***** Test de l'operateur (int - Time) *************************" << endl;
  cout <<         "********************************************************************" << endl;
  {
    Time d(1,20);
    cout << "d : ";
    d.display();
    Time duration;
    cout << endl << ">>>>> duration = 120 - d;" << endl;
    duration = 120 - d;
    cout << "duration : ";
    duration.display();
    cout << endl;
  }

  cout << endl << "********************************************************************" << endl;
  cout <<         "(3) ***** Test de l'operateur (Time - Time) ************************" << endl;
  cout <<         "********************************************************************" << endl;
  {
    Time start(10,20);
    Time end(12,10);
    cout << "start : ";
    start.display();
    cout << endl << "end   : ";
    end.display();
    Time duration;
    cout << endl << ">>>>> duration = end - start;" << endl;
    duration = end - start;
    cout << "duration : ";
    duration.display();
    cout << endl;
  }
}

/*******************************************************************************************************/
/*** Test des operateurs < > == de la classe Time ******************************************************/
/*******************************************************************************************************/
void Essai4()
{
  cout << "**********************************************************************" << endl;
  cout << "***** Test des operateurs < > == de la classe Time *******************" << endl;
  cout << "**********************************************************************" << endl;

  Time h1(12,35);
  cout << "h1 : ";
  h1.display();

  Time h2(10,20);
  cout << endl << "h2 : ";
  h2.display();

  cout << "Comparaison des heures : ";
  if (h1 < h2) cout << "h1 < h2" << endl;
  if (h1 > h2) cout << "h1 > h2" << endl;
  if (h1 == h2) cout << "h1 == h2" << endl;
  cout << endl;
}

/*******************************************************************************************************/
/*** Test des operateurs << et >> de la classe Time ****************************************************/
/*******************************************************************************************************/
void Essai5()
{
  cout << "**********************************************************************" << endl;
  cout << "********* Test des operateurs << et >> de la classe Time *************" << endl;
  cout << "**********************************************************************" << endl;
  Time h;
  cout << "Saisissez une heure : ";
  cin >> h;
  cout << endl << "Voici l'heure que vous avez encodee : " << h << endl;
  cout << endl;
}

/*******************************************************************************************************/
/*** Tests des operateurs de pre/post in(de)crementation de la classe Time *****************************/
/*******************************************************************************************************/
void Essai6()
{
  cout << "**********************************************************************" << endl;
  cout << "(1) ***** Test de l'operateur de pre-incrementation ******************" << endl;
  cout << "**********************************************************************" << endl;
  Time h1(8,50);
  cout << "h1   : " << h1 << endl;
  cout << "++h1 : " << ++h1 << endl;  // Si tout va bien, h1 est incremente avant d'etre affiche !
  cout << "h1   : " << h1 << endl << endl;

  cout << "**********************************************************************" << endl;
  cout << "(2) ***** Test de l'operateur de post-incrementation *****************" << endl;
  cout << "**********************************************************************" << endl;
  Time h2(14,40);
  cout << "h2   : " << h2 << endl;
  cout << "h2++ : " << h2++ << endl;  // Si tout va bien, h2 est incremente apres avoir ete affiche !
  cout << "h2   : " << h2 << endl << endl;

  cout << "**********************************************************************" << endl;
  cout << "(3) ***** Test de l'operateur de pre-decrementation ******************" << endl;
  cout << "**********************************************************************" << endl;
  Time h3(10,20);
  cout << "h3   : " << h3 << endl;
  cout << "--h3 : " << --h3 << endl;  // Si tout va bien, h3 est decremente avant d'etre affiche !
  cout << "h3   : " << h3 << endl << endl;

  cout << "**********************************************************************" << endl;
  cout << "(4) ***** Test de l'operateur de post-decrementation *****************" << endl;
  cout << "**********************************************************************" << endl;
  Time h4(17,10);
  cout << "h4   : " << h4 << endl;
  cout << "h4-- : " << h4-- << endl;  // Si tout va bien, h4 est decremente apres avoir ete affiche !
  cout << "h4   : " << h4 << endl << endl;
}

/*******************************************************************************************************/
/*** Test des operateurs < > == de la classe Timing ****************************************************/
/*******************************************************************************************************/
void Essai7()
{
  cout << "**********************************************************************" << endl;
  cout << "********* Test des operateurs < > == de la classe Timing *************" << endl;
  cout << "**********************************************************************" << endl;
  Timing ref(Timing::WEDNESDAY,Time(10,0),Time(2,0));
  cout << "ref : ";
  ref.display();
  cout << endl << endl;

  Timing h1(Timing::FRIDAY,Time(9,0),Time(1,0));
  cout << "h1  : ";
  h1.display();
  cout << endl;
  if (h1 < ref) cout << "h1 < ref" << endl;
  if (h1 > ref) cout << "h1 > ref" << endl ;
  if (h1 == ref) cout << "h1 == ref" << endl ;
  cout << endl;

  Timing h2(Timing::WEDNESDAY,Time(9,0),Time(2,0));
  cout << "h2  : ";
  h2.display();
  cout << endl;
  if (h2 < ref) cout << "h2 < ref" << endl;
  if (h2 > ref) cout << "h2 > ref" << endl;
  if (h2 == ref) cout << "h2 == ref" << endl;
  cout << endl;

  Timing h3(Timing::WEDNESDAY,Time(10,0),Time(3,0));
  cout << "h3  : ";
  h3.display();
  cout << endl;
  if (h3 < ref) cout << "h3 < ref" << endl;
  if (h3 > ref) cout << "h3 > ref" << endl;
  if (h3 == ref) cout << "h3 == ref" << endl;
  cout << endl;

  Timing h4(Timing::WEDNESDAY,Time(10,0),Time(2,0));
  cout << "h4  : ";
  h4.display();
  cout << endl;
  if (h4 < ref) cout << "h4 < ref" << endl;
  if (h4 > ref) cout << "h4 > ref" << endl;
  if (h4 == ref) cout << "h4 == ref" << endl;
  cout << endl;
}
