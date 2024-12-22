#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>
#include "Timing.h"  // Inclut la classe Timing pour utiliser les objets Timing dans la classe Event
using namespace std;
#include <string.h>  // Inclut la bibliothèque pour la gestion des chaînes de caractères C
#include <iostream>  // Inclut la bibliothèque pour l'affichage en console

namespace planning
{
    class Event
    {
    private:
        int code;          // Code unique pour chaque événement
        char *title;       // Titre de l'événement (chaîne de caractères allouée dynamiquement)
        Timing *timing;    // Objet Timing associé à l'événement, qui représente son horaire

    public:
        static int currentCode;  // Variable statique pour suivre le nombre d'événements créés

        // Constructeur par défaut
        Event();

        // Constructeur avec paramètres pour initialiser un événement avec un code et un titre
        Event(int, const char *);

        // Getter pour récupérer le code de l'événement
        int getCode() const;

        // Getter pour récupérer le titre de l'événement
        const char *getTitle() const;

        // Setter pour définir le code de l'événement
        void setCode(int);

        // Setter pour définir le titre de l'événement
        void setTitle(const char *);

        // Destructeur pour libérer la mémoire allouée dynamiquement
        ~Event();

        // Méthode pour afficher les informations de l'événement
        void display() const;

        // Constructeur de copie pour créer un événement à partir d'un autre événement
        Event(const Event &);

        // Setter pour définir le timing (horaire) de l'événement
        void setTiming(const Timing &);

        // Getter pour récupérer le timing de l'événement
        const Timing getTiming() const;
    };
}

#endif
