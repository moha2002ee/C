#ifndef EVENT_H    // Directive de préprocesseur pour éviter les inclusions multiples du fichier d'en-tête.
#define EVENT_H

#include <stdio.h>    // Inclus pour certaines fonctions de base en C.
#include "Timing.h"    // Inclut la définition de la classe Timing, qui est utilisée dans cette classe.
using namespace std;   // Permet d'éviter de préfixer avec std:: dans ce fichier.
#include <string.h>    // Inclus pour les fonctions de manipulation de chaînes de caractères, comme strlen et strcpy.
#include <iostream>    // Inclus pour les entrées/sorties avec cout, cin, etc.

namespace planning   // Définition de l'espace de noms "planning" pour organiser les classes et éviter les conflits.
{
    // Définition de la classe Event, qui représente un événement avec un code, un titre et un timing.
    class Event
    {
    private:
        int code;         // Code unique associé à l'événement.
        char *title;      // Titre de l'événement, stocké dynamiquement.
        Timing *timing;   // Pointeur vers un objet Timing associé à l'événement.

    public:
        // Variable statique permettant de suivre le code actuel de l'événement.
        static int currentCode;

        // Constructeur par défaut : initialise un événement avec des valeurs par défaut.
        Event();

        // Constructeur paramétré : permet d'initialiser un événement avec un code et un titre donnés.
        Event(int, const char *);

        // Getter pour le code : retourne le code de l'événement.
        int getCode() const;

        // Getter pour le titre : retourne un pointeur constant vers le titre de l'événement.
        const char *getTitle() const;

        // Setter pour le code : met à jour le code de l'événement.
        void setCode(int);

        // Setter pour le titre : met à jour le titre de l'événement, avec gestion de la mémoire.
        void setTitle(const char *);

        // Destructeur : libère la mémoire allouée dynamiquement pour le titre et le timing.
        ~Event();

        // Méthode d'affichage : affiche les informations de l'événement (code, titre et timing).
        void display() const;

        // Constructeur de copie : permet de créer un nouvel objet Event en copiant un autre.
        Event(const Event &);

        // Setter pour le timing : alloue de la mémoire pour un objet Timing et le copie.
        void setTiming(const Timing &);

        // Getter pour le timing : retourne une copie de l'objet Timing associé à l'événement.
        const Timing getTiming() const;
    };
}

#endif // Fin de la directive de préprocesseur pour éviter les inclusions multiples.
