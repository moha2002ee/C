#ifndef TIME_H      // Préprocesseur pour éviter l'inclusion multiple du fichier d'en-tête.
#define TIME_H

#include <stdlib.h>   // Inclut la bibliothèque standard C, souvent utilisée pour des fonctions comme `malloc`, `free`, etc.
#include <iostream>    // Pour utiliser les flux d'entrée/sortie (cout, cin, etc.).
#include <string>      // Permet d'utiliser la classe `std::string`, même si elle n'est pas nécessaire ici (car nous utilisons des `int`).
using namespace std;  // Utilise l'espace de noms standard (std) pour éviter de préfixer chaque élément avec `std::`.

namespace planning   // Définition de l'espace de noms `planning` pour organiser les classes liées à la gestion de planification.
{
    // Classe Time : gère l'heure et les minutes.
    class Time
    {
    private:
        int hour;     // Attribut privé pour stocker l'heure.
        int minute;   // Attribut privé pour stocker les minutes.

    public:
        // Constructeurs
        Time();                 // Constructeur par défaut : initialise l'heure et les minutes à 0.
        Time(int d);            // Constructeur qui prend un entier représentant un nombre total de minutes.
        Time(int h, int m);     // Constructeur qui prend directement l'heure et les minutes.

        // Destructeur
        ~Time();                // Destructeur : vide la mémoire ou effectue des actions de nettoyage si nécessaire.

        // Méthodes Setters
        void setHour(int h);    // Définit l'heure.
        void setMinute(int m);  // Définit les minutes.

        // Méthodes Getters
        int getHour() const;    // Retourne l'heure.
        int getMinute() const;  // Retourne les minutes.

        // Méthode pour afficher l'heure et les minutes.
        void display() const;   // Affiche l'heure et les minutes de manière lisible.
    };
}

#endif // TIME_H   // Fin de la protection contre l'inclusion multiple.
