#include "Event.h"

namespace planning
{
    // Variable statique qui permet d'attribuer un code unique à chaque événement.
    int Event::currentCode = 1;

    // ***** Constructeurs *****

    // Constructeur par défaut : initialise un événement avec des valeurs par défaut.
    Event::Event()
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur par defaut <<<" << endl;
        #endif
        // Le code commence à 1, et on initialise le titre et le timing à nullptr.
        code = 1;
        title = nullptr;
        timing = nullptr;

        // Initialisation du titre par défaut avec "---".
        setTitle("---");
        // Incrémente le compteur de codes pour le prochain événement.
        currentCode++;
    }

    // Constructeur d'initialisation : permet de créer un événement avec un code et un titre.
    Event::Event(int c, const char* t)
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur d'initialisation <<<" << endl;
        #endif
        // Définit le code et le titre de l'événement.
        setCode(c);
        title = nullptr;
        timing = nullptr;
        setTitle(t);

        // Incrémente le compteur de codes.
        currentCode++;
    }

    // Constructeur de copie : permet de créer un événement en copiant un autre événement.
    Event::Event(const Event& e)
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur de copie <<<" << endl;
        #endif
        // Copie des attributs de l'événement source.
        setCode(e.getCode());
        title = nullptr;
        timing = nullptr;
        setTitle(e.getTitle());
        setTiming(e.getTiming());

        // Incrémente le compteur de codes.
        currentCode++;
    }

    // ***** Destructeur *****
    
    // Destructeur : libère la mémoire allouée pour les attributs title et timing.
    Event::~Event()
    {
        #ifdef DEBUG
        cout << ">>> Event: destructeur <<<" << endl;
        #endif
        // Libère la mémoire pour le titre et le timing si nécessaire.
        if (title) delete[] title;
        if (timing) delete timing;
        
        // Décrémentation du compteur de codes lors de la destruction de l'objet.
        currentCode--;
    }

    // ***** getXXX / setXXX *****

    // Setter pour le code : le code doit être supérieur ou égal à 1.
    void Event::setCode(int c)
    {
        if(c < 1) return; // Si le code est invalide, ne pas modifier.
        code = c;
    }

    // Setter pour le titre : alloue de la mémoire pour le titre et le copie.
    void Event::setTitle(const char* t)
    {
        if (t == nullptr) return; // Si le titre est nul, ne rien faire.
        if (title) delete[] title; // Libère l'ancien titre si nécessaire.
        title = new char[strlen(t) + 1]; // Alloue de la mémoire pour le nouveau titre.
        strcpy(title, t); // Copie le titre.
    }

    // Setter pour le timing : alloue de la mémoire pour un nouvel objet Timing.
    void Event::setTiming(const Timing& tm)
    {
        if(timing) delete timing; // Libère l'ancien timing si nécessaire.
        timing = new Timing(tm); // Alloue de la mémoire pour un nouveau timing.
    }

    // Getter pour le code : retourne le code de l'événement.
    int Event::getCode() const
    {
        return code;
    }

    // Getter pour le titre : retourne le titre de l'événement.
    const char* Event::getTitle() const
    {
        return title;
    }

    // Getter pour le timing : retourne une copie du timing de l'événement.
    const Timing Event::getTiming() const
    {
        return *timing;
    }

    // ***** Autres méthodes de l'interface *****

    // Affiche les informations de l'événement (code, titre et timing).
    void Event::display() const
    {
        cout << "Event (" << code << ") :" << title << endl;
        
        // Si le timing est défini, on l'affiche.
        if (timing)
        {
            timing->display();
        }
        else
        {
            // Si le timing n'est pas défini, on affiche "Timing non planifié".
            cout << "Timing non planifié" << endl;  
        }
    }
}
