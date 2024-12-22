#ifndef TIME_H
#define TIME_H

#include <iostream> // Pour l'utilisation de istream et ostream

namespace planning
{
    class Time
    {
    private:
        int hour;                  // Heures
        int minute;                // Minutes
        int comptH(const Time &t); // Méthode privée de comparaison

    public:
        // Constructeurs et destructeur
        Time();
        Time(int d);        // Constructeur prenant en paramètre des minutes totales
        Time(int h, int m); // Constructeur avec heures et minutes
        ~Time();

        // Accesseurs et mutateurs
        int getHour() const;   // Obtenir l'heure
        int getMinute() const; // Obtenir les minutes
        void setHour(int h);   // Définir l'heure
        void setMinute(int m); // Définir les minutes

        void display() const; // Méthode d'affichage des informations

        // Surcharge des opérateurs arithmétiques
        Time operator+(Time t); // Addition de deux objets Time
        Time operator++(int);   // Incrémentation post-fixée
        Time operator++();      // Incrémentation pré-fixée
        Time operator--();      // Décrémentation pré-fixée
        Time operator--(int);   // Décrémentation post-fixée

        // Surcharge de l'opérateur d'assignation
        Time &operator=(const Time &t);

        // Surcharge des opérateurs pour la soustraction
        friend Time operator+(int n, const Time &t); // Ajout d'un entier à un objet Time
        Time operator-(int m);                       // Soustraction d'un entier
        friend Time operator-(int m, const Time &t); // Soustraction avec un entier à gauche
        Time operator-(const Time &t2);              // Soustraction de deux objets Time

        // Surcharge des opérateurs de comparaison
        int operator<(const Time &t);
        int operator>(const Time &t);
        int operator==(const Time &t);

        // Sérialisation de l'objet Time dans un flux de sortie (ostream)
        friend std::ostream& operator<<(std::ostream &, const Time &) noexcept;

        // Désérialisation de l'objet Time depuis un flux d'entrée (istream)
        friend std::istream& operator>>(std::istream &, Time &);
    };
}

#endif
