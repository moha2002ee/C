#include <string>      
#include <iostream>
#include <cstdlib>     
#include "Time.h"  // Inclut la classe Time pour l'utilisation de l'heure et de la durée
#ifndef TIMING_H 
#define TIMING_H 
using namespace std;   

namespace planning
{
    class Timing
    {
    private:
        string day;          // Jour de la semaine (par exemple, "Lundi")
        Time start;          // Heure de début de l'événement (objet Time)
        Time duration;       // Durée de l'événement (objet Time)

    public:
        // Définition des constantes statiques pour les jours de la semaine.
        // Ces constantes sont utilisées pour faciliter l'assignation du jour
        // sans avoir à se souvenir des chaînes de caractères exactes.
        static const string MONDAY;
        static const string TUESDAY;
        static const string WEDNESDAY;
        static const string THURSDAY;
        static const string FRIDAY;
        static const string SATURDAY;
        static const string SUNDAY;

        // Constructeur par défaut, constructeur avec paramètres et destructeur
        Timing(); // Constructeur par défaut
        ~Timing(); // Destructeur

        // Méthode d'affichage qui montre les informations de l'événement (jour, début, durée)
        void display() const;

        // Méthodes de définition des attributs (setters)
        void setDay(const string& d);   // Définit le jour de la semaine
        void setStart(const Time &e);   // Définit l'heure de début de l'événement
        void setStart(int h, int m);    // Définit l'heure de début en heures et minutes
        void setDuration(const Time &e); // Définit la durée de l'événement

        // Méthodes pour obtenir les valeurs des attributs (getters)
        string getDay() const;          // Renvoie le jour de la semaine
        Time getStart() const;          // Renvoie l'heure de début
        Time getDuration() const;       // Renvoie la durée de l'événement

        // Constructeur avec paramètres pour initialiser l'objet avec un jour, une heure de début et une durée
        Timing(const string& d, const Time &s, const Time &du);
    };
}
#endif
