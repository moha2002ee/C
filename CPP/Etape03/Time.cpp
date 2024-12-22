#include "Time.h"

using namespace std;

namespace planning
{
    // ***** Constructeurs et destructeur *****

    // Constructeur avec un nombre total de minutes
    Time::Time(int d)
    {
        int h = d / 60;      // Calcul des heures
        int m = d % 60;      // Calcul des minutes restantes
        setHour(h);          // Définit l'heure
        setMinute(m);        // Définit les minutes
    }

    // Constructeur avec heure et minute spécifiées
    Time::Time(int h, int m)
    {
        setHour(h);          // Définit l'heure
        setMinute(m);        // Définit les minutes
    }

    // Constructeur par défaut initialisant à 00h00
    Time::Time()
    {
        setHour(0);          // Heure par défaut à 0
        setMinute(0);        // Minute par défaut à 0
    }

    // Destructeur (vide car aucune ressource dynamique n'est allouée)
    Time::~Time() {}

    // ***** Accesseurs (Getters et Setters) *****

    // Retourne l'heure
    int Time::getHour() const
    {
        return hour;
    }

    // Retourne les minutes
    int Time::getMinute() const
    {
        return minute;
    }

    // Définit l'heure
    void Time::setHour(int h)
    {
        hour = h;
    }

    // Définit les minutes
    void Time::setMinute(int m)
    {
        minute = m;
    }

    // ***** Affichage *****

    // Affiche l'heure et les minutes
    void Time::display() const
    {
        cout << "\nHeure    => " << hour << "h\n";
        cout << "\nMinute   => " << minute << "m\n";
    }

    // ***** Surcharge des opérateurs *****

    // Opérateur d'addition : additionne deux objets Time
    Time Time::operator+(Time t)
    {
        Time resultat;
        resultat.hour = hour + t.hour;
        resultat.minute = minute + t.minute;

        // Si les minutes dépassent 60, on ajuste l'heure et les minutes
        if (resultat.minute >= 60)
        {
            resultat.minute -= 60;
            resultat.hour++;
        }

        return resultat;
    }

    // Opérateur d'assignation : copie les valeurs d'un autre objet Time
    Time &Time::operator=(const Time &t)
    {
        if (this != &t)  // Evite l'auto-assignation
        {
            hour = t.hour;
            minute = t.minute;
        }
        return *this;
    }

    // Opérateur d'addition avec un entier (ajoute un nombre de minutes à l'heure)
    Time operator+(int n, const Time &t)
    {
        Time resultat = t;
        resultat.minute += n;

        // Ajuste l'heure et les minutes si nécessaire
        if (resultat.minute >= 60)
        {
            resultat.minute -= 60;
            resultat.hour++;
        }

        return resultat;
    }

    // Opérateur de soustraction : soustrait un nombre de minutes à l'heure
    Time Time::operator-(int m)
    {
        Time temp(*this);
        temp.minute = (temp.hour * 60) + temp.minute;  // Convertit l'heure en minutes
        temp.minute = temp.minute - m;  // Soustrait les minutes
        temp.hour = temp.minute / 60;  // Recalcule l'heure
        temp.minute = temp.minute % 60;  // Reste des minutes

        return temp;
    }

    // Soustraction d'un nombre de minutes depuis un objet Time (fonction globale)
    Time operator-(int m, const Time &t)
    {
        Time temp;
        temp.hour = m / 60;
        temp.minute = m % 60;
        m = (t.hour * 60) + t.minute;  // Convertit l'heure en minutes
        return temp - m;  // Soustrait les minutes
    }

    // Opérateur de soustraction entre deux objets Time
    Time Time::operator-(const Time &t2)
    {
        Time temp(*this);
        int m = (t2.hour * 60) + t2.minute;  // Convertit l'autre heure en minutes
        return temp - m;  // Soustrait les minutes
    }

    // Comparaison : vérifie si l'heure de l'objet est inférieure à l'autre
    int Time::operator<(const Time &t)
    {
        return comptH(t) == -1;
    }

    // Comparaison : vérifie si l'heure de l'objet est supérieure à l'autre
    int Time::operator>(const Time &t)
    {
        return comptH(t) == 1;
    }

    // Comparaison : vérifie si les deux heures sont égales
    int Time::operator==(const Time &t)
    {
        return comptH(t) == 0;
    }

    // Méthode interne pour comparer l'heure et les minutes entre deux objets Time
    int Time::comptH(const Time &t)
    {
        if (hour < t.hour)  // Si l'heure de l'objet est inférieure
            return -1;
        if (hour > t.hour)  // Si l'heure de l'objet est supérieure
            return 1;
        if (minute < t.minute)  // Si les minutes sont inférieures
            return -1;
        if (minute > t.minute)  // Si les minutes sont supérieures
            return 1;
        return 0;  // Si les heures et les minutes sont égales
    }

    // ***** Surcharge des opérateurs de flux d'entrée/sortie *****

    // Surcharge de l'opérateur >> pour saisir l'heure et les minutes depuis l'entrée standard
    istream &operator>>(istream &s, Time &t)
    {
        int h, m;
        do
        {
            cout << "Saisie l'heure (0-23): ";
            s >> h;
            if (h < 0 || h >= 24)
            {
                cout << "Heure invalide. Veuillez entrer une heure entre 0 et 23.\n";
            }
        } while (h < 0 || h >= 24);
        t.setHour(h);

        do
        {
            cout << "Saisie la minute (0-59): ";
            s >> m;
            if (m < 0 || m >= 60)
            {
                cout << "Minute invalide. Veuillez entrer une minute entre 0 et 59.\n";
            }
        } while (m < 0 || m >= 60);
        t.setMinute(m);

        return s;
    }

    // Surcharge de l'opérateur << pour afficher l'heure et les minutes dans la sortie standard
    ostream &operator<<(ostream &s, const Time &t)
    {
        s << "Heure => " << t.getHour() << "h "
          << "Minutes => " << t.getMinute() << "m";
        return s;
    }

    // ***** Opérateurs d'incrémentation et de décrémentation *****

    // Pré-incrémentation : ajoute 1 minute à l'heure
    Time Time::operator++()
    {
        (*this) = (*this) + 1;
        return (*this);
    }

    // Post-incrémentation : ajoute 1 minute à l'heure mais retourne une copie avant
    Time Time::operator++(int)
    {
        Time temp(*this);
        (*this) = (*this) + 1;
        return temp;
    }

    // Pré-décrémentation : soustrait 1 minute de l'heure
    Time Time::operator--()
    {
        (*this) = (*this) - 1;
        return (*this);
    }

    // Post-décrémentation : soustrait 1 minute de l'heure mais retourne une copie avant
    Time Time::operator--(int)
    {
        Time temp(*this);
        (*this) = (*this) - 1;
        return temp;
    }
}
