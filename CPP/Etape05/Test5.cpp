#include <iostream>

#include "Time.h"
#include "Timing.h"
#include "Event.h"
#include "TimeException.h"
#include "TimingException.h"
using namespace std;
using namespace planning;

int Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();
void Essai5();
void Essai6();
void Essai7();
void Essai8();
void Essai9();
void Essai10();
void Essai11();

int main(int argc, char *argv[])
{
  int choix;
  bool fini = false;

  while (!fini)
  {
    if (argc == 2)
    {
      choix = atoi(argv[1]);
      fini = true;
    }
    else
      choix = Menu();
    switch (choix)
    {
    case 1:
      Essai1();
      break;
    case 2:
      Essai2();
      break;
    case 3:
      Essai3();
      break;
    case 4:
      Essai4();
      break;
    case 5:
      Essai5();
      break;
    case 6:
      Essai6();
      break;
    case 7:
      Essai7();
      break;
    case 8:
      Essai8();
      break;
    case 9:
      Essai9();
      break;
    case 10:
      Essai10();
      break;
    case 11:
      Essai11();
      break;
    default:
      fini = true;
      break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 5 ---------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Test des constructeurs, setXXX() de la classe Time" << endl;
  cout << " 2. Test de l'operateur (Time + int) de la classe Time" << endl;
  cout << " 3. Test de l'operateur (int + Time) de la classe Time" << endl;
  cout << " 4. Test de l'operateur (Time - int) de la classe Time" << endl;
  cout << " 5. Test de l'operateur (int - Time) de la classe Time" << endl;
  cout << " 6. Test de l'operateur (Time + Time) de la classe Time" << endl;
  cout << " 7. Test de l'operateur (Time - Time) de la classe Time" << endl;
  cout << " 8. Test de l'operateur ++ de la classe Time" << endl;
  cout << " 9. Test de l'operateur -- de la classe Time" << endl;
  cout << "10. Test de la methode setJour() de la classe Timing" << endl;
  cout << "11. Gestion de plusieurs exceptions simultanement" << endl;
  cout << "12. Quitter" << endl
       << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/**********************************************************************************************/
// ATTENTION !!!!
// Les methodes de vos classes NE doivent PAS contenir de TRY{...} CATCH{...} mais
// uniquement des THROW !!! Donc, votre classe lance une exception (une erreur) mais
// ce n'est pas elle qui la traite. C'est l'application qui utilise votre classe
// qui doit traiter les exceptions. C'est donc uniquement dans le main (ou les fonctions appelees)
// que l'on trouve des try...catch
/**********************************************************************************************/
void Essai1()
{
  cout << "----- 1. Test des constructeurs, setXXX() de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {

      int hour, minute;
      cout << "Entrez l'heure h1 :" << endl;
      cout << "Heure  : ";
      cin >> hour;
      cin.ignore();
      cout << "Minute : ";
      cin >> minute;
      cin.ignore();
      Time h1(hour, minute); // !!!
      cout << "--> h1 = " << h1 << endl
           << endl;

      cout << "On modifie l'heure de h1 : " << endl;
      cout << "Nouvelle heure : ";
      cin >> hour;
      h1.setHour(hour); // !!!
      cout << "--> h1 = " << h1 << endl
           << endl;

      cout << "On modifie les minutes de h1 : " << endl;
      cout << "Nouvelles minutes : ";
      cin >> minute;
      h1.setMinute(minute); // !!!
      cout << "--> h1 = " << h1 << endl
           << endl;

      cout << "Entrez la duree d1 : " << endl;
      int minutes;
      cout << "Duree en minutes : ";
      cin >> minutes;
      cin.ignore();
      Time d1(minutes); // !!!
      cout << "--> d1 = " << d1 << endl
           << endl;
    }
    // ...
  }
  catch (TimeException &e)
  {
    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }

  cout << endl;
}

/**********************************************************************************************/
void Essai2()
{
  cout << "----- 2. Test de l'operateur (Time + int) de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {
      Time h(15, 30);
      cout << "h = Time(15,30)" << endl;
      int duration;
      cout << "Entrez une duree en minutes : ";
      cin >> duration;
      h = h + duration;
      cout << "Apres addition (h = h + duration) --> " << h << endl
           << endl;
    }
  }
  catch (TimeException &e)
  {

    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai3()
{
  cout << "----- 3. Test de l'operateur (int + Time) de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {

    {
      Time h(15, 30);
      cout << "h = Time(15,30)" << endl;
      int duration;
      cout << "Entrez une duree en minutes : ";
      cin >> duration;
      h = duration + h;
      cout << "Apres addition (h = duree + h) --> " << h << endl
           << endl;
    }
  }
  catch (TimeException &e)
  {

    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai4()
{
  cout << "----- 4. Test de l'operateur (Time - int) de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {
      Time h(1, 30);
      cout << "h = Time(1,30)" << endl;
      int duration;
      cout << "Entrez une duree en minutes : ";
      cin >> duration;
      h = h - duration;
      cout << "Apres soustraction (h = h - duree) --> " << h << endl
           << endl;
    }
  }
  catch (TimeException &e)
  {

    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai5()
{
  cout << "----- 5. Test de l'operateur (int - Time) de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {
      Time h(1, 30);
      cout << "h = Time(1,30)" << endl;
      int duration;
      cout << "Entrez une duree en minutes : ";
      cin >> duration;
      h = duration - h;
      cout << "Apres soustraction (h = duree - h) --> " << h << endl
           << endl;
    }
  }
  catch (TimeException &e)
  {
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai6()
{
  cout << "----- 6. Test de l'operateur (Time + Time) de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {
      Time h1(22, 30);
      cout << "h1 = Time(22,30)" << endl;
      int duration;
      cout << "Entrez une duree en minutes : ";
      cin >> duration;
      Time d(duration);
      cout << "d = " << d << endl;
      h1 = h1 + d;
      cout << "Apres addtion (h1 = h1 + d) --> " << h1 << endl
           << endl;
    }
  }
  catch (TimeException &e)
  {
    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai7()
{
  cout << "----- 7. Test de l'operateur (Time - Time) de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {
      Time d(120);
      cout << "d = " << d << endl;
      Time h1;
      cout << "Entrez l'heure h1 : ";
      cin >> h1;
      h1 = h1 - d;
      cout << "Apres soustraction (h1 = h1 - d) --> " << h1 << endl
           << endl;
    }
  }
  catch (TimeException &e)
  {

    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai8()
{
  cout << "----- 8. Test de l'operateur ++ de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {
      Time h;
      cout << "Entrez l'heure h = ";
      cin >> h;
      h++;
      ++h;
      cout << "Apres incrementation (h++) --> " << h << endl
           << endl;
    }
  }
  catch (TimeException &e)
  {

    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai9()
{
  cout << "----- 9. Test de l'operateur -- de la classe Time --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {
      Time h;
      cout << "Entrez l'heure h = ";
      cin >> h;
      h--;
      --h;
      cout << "Apres decrementation (h--) --> " << h << endl
           << endl;
    }
  }
  catch (TimeException &e)
  {
    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai10()
{
  cout << "----- 10. Test de la methode setDay() de la classe Timing --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee et le code de l'erreur

  // ...
  try
  {
    {
      Timing t;
      string day;
      cout << "Entrez le jour = ";
      getline(cin, day);
      t.setDay(day);
      t.display();
    }
  }
  catch (TimingException &e)
  {

    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  // ...

  cout << endl;
}

/**********************************************************************************************/
void Essai11()
{
  cout << "----- 11. Gestion de plusieurs exceptions simultanement ---" << endl;
  // A COMPLETER : Traitez TOUTES les exceptions susceptible d'etre lancee par le bloc de code suivant (try...catch)

  // ...
  try
  {
    {
      Timing t;
      string day;
      Time hour;
      int d;
      cout << "Encodez un timing :" << endl;
      cout << "Jour = ";
      getline(cin, day);
      t.setDay(day);
      cout << "Heure = ";
      cin >> hour;
      t.setStart(hour);
      cout << "Duree en minutes = ";
      cin >> d;
      cin.ignore();
      t.setDuration(Time(d));
      cout << endl
           << "Timing encode : ";
      t.display();
      cout << endl;
      Event e(1, "Theorie C++");
      cout << "Voici un Event non planifie : ";
      e.display();
      cout << "Voulez-vous planifier cet Event (o/n) ? ";
      char ch;
      cin >> ch;
      cin.ignore();
      if (ch == 'o')
        e.setTiming(t);
      cout << "Voici le Timing de l'Event planifie : ";
      e.getTiming().display(); // !!!
    }
  }
  catch (TimeException &e)
  {
    cout << "Erreur : " << e.getMessage() << ", Code : " << e.getCode() << endl;
  }
  catch (TimingException &ee)
  {
    cout << "Erreur : " << ee.getMessage() << ", Code : " << ee.getCode() << endl;
  }

  // ...
}
