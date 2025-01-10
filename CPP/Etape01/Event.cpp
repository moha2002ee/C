#include "Event.h"
#include <cstring>
#include <iostream>

using namespace std;

// Constructeur par défaut : initialise un événement avec des valeurs par défaut.
// Le code est initialisé à 0 et le titre à "default".
Event::Event()
{
    code = 0;

    // Allocation dynamique pour le titre avec une copie de "default".
    title = new char[strlen("default") + 1]; 
    strcpy(title, "default");
}

// Constructeur paramétré : initialise un événement avec un code donné et un titre.
// Utilise la méthode setTitle pour gérer la mémoire en toute sécurité.
Event::Event(int c, const char *t)
{
    code = c;         // Initialisation du code.
    title = nullptr;  // Initialise le titre à nullptr pour éviter les erreurs.
    setTitle(t);      // Définit le titre avec gestion sécurisée de la mémoire.
}

// Constructeur de copie : crée une copie d'un objet Event existant.
// Effectue une copie profonde du titre pour éviter les conflits de mémoire.
Event::Event(const Event &e)
{
    code = e.code;  // Copie du code.

    if (e.title) // Si le titre de l'objet à copier n'est pas nul.
    {
        // Allocation dynamique et copie du titre.
        title = new char[strlen(e.title) + 1];
        strcpy(title, e.title);
    }
    else
    {
        title = nullptr; // Si le titre source est nul, titre reste nul.
    }
}

// Destructeur : libère la mémoire allouée dynamiquement pour le titre.
Event::~Event()
{
    delete[] title; // Libère le tableau de caractères alloué pour le titre.
}

// Méthode getter : retourne le code de l'événement.
int Event::getCode() const
{
    return code;
}

// Méthode getter : retourne le titre de l'événement.
const char *Event::getTitle() const
{
    return title; // Retourne un pointeur constant vers le titre.
}

// Méthode setter : met à jour le code de l'événement.
void Event::setCode(int c)
{
    code = c; // Met à jour le code.
}

// Méthode setter : met à jour le titre de l'événement.
// Libère l'ancien titre (si nécessaire) et alloue de la mémoire pour le nouveau.
void Event::setTitle(const char *t)
{
    if (title != nullptr) // Si un titre existait déjà.
    {
        delete[] title; // Libère la mémoire associée à l'ancien titre.
    }

    if (t) // Si le nouveau titre n'est pas nul.
    {
        // Allocation dynamique et copie du nouveau titre.
        title = new char[strlen(t) + 1];
        strcpy(title, t);
    }
    else
    {
        title = nullptr; // Si le nouveau titre est nul, aucun titre n'est défini.
    }
}

// Méthode d'affichage : affiche les informations de l'événement.
void Event::display() const
{
    cout << "Code = " << code << endl;

    // Affiche le titre, ou "(null)" s'il n'existe pas.
    cout << "Title = " << (title ? title : "(null)") << endl;
}
