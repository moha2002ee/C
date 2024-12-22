#include <stdio.h>      // Inclus pour certaines fonctions de base en C.
using namespace std;    // Permet d'éviter de préfixer avec std::.
#include <string.h>     // Inclus pour les fonctions de manipulation de chaînes comme strlen et strcpy.
#include <iostream>     // Inclus pour les entrées/sorties avec cout, cin, etc.

// Définition de la classe Event
class Event
{
private:
    int code;        // Code unique associé à l'événement.
    char *title;     // Titre de l'événement, stocké dynamiquement.

public:
    // Constructeur par défaut : initialise un événement avec des valeurs par défaut.
    Event();

    // Constructeur paramétré : initialise un événement avec un code et un titre donnés.
    Event(int, const char *);

    // Getter pour le code : retourne la valeur du code.
    int getCode() const;

    // Getter pour le titre : retourne un pointeur constant vers le titre.
    const char *getTitle() const;

    // Setter pour le code : met à jour la valeur du code.
    void setCode(int);

    // Setter pour le titre : met à jour le titre avec une gestion sécurisée de la mémoire.
    void setTitle(const char *);

    // Destructeur : libère la mémoire allouée dynamiquement pour le titre.
    ~Event();

    // Méthode d'affichage : affiche les informations de l'événement (code et titre).
    void display() const;

    // Constructeur de copie : permet de créer un nouvel objet Event en copiant un autre.
    Event(const Event &e);
};
