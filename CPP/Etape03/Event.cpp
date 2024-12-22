#include "Event.h"

namespace planning
{
    // Variable statique pour suivre le nombre d'objets créés
    int Event::currentCode = 1;

    // ***** Constructeurs *****

    // Constructeur par défaut
    // Initialise un événement avec un code par défaut (1) et un titre par défaut ("---")
    // Incrémente également le compteur currentCode
    Event::Event()
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur par defaut <<<" << endl;
        #endif
        code = 1;                  // Code par défaut
        title = nullptr;           // Titre non défini
        timing = nullptr;          // Timing non défini
        setTitle("---");           // Initialise le titre par défaut
        currentCode++;             // Incrémente le compteur des événements créés
    }

    // Constructeur avec initialisation
    // Initialise un événement avec un code et un titre spécifiques
    // Incrémente également le compteur currentCode
    Event::Event(int c, const char* t)
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur d'initialisation <<<" << endl;
        #endif
        setCode(c);                // Initialise le code
        title = nullptr;           // Titre non défini
        timing = nullptr;          // Timing non défini
        setTitle(t);               // Initialise le titre avec la chaîne fournie
        currentCode++;             // Incrémente le compteur des événements créés
    }

    // Constructeur de copie
    // Crée un nouvel événement en copiant le code, le titre et le timing de l'événement passé en paramètre
    Event::Event(const Event& e)
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur de copie <<<" << endl;
        #endif
        setCode(e.getCode());      // Copie le code de l'événement
        title = nullptr;           // Titre non défini
        timing = nullptr;          // Timing non défini
        setTitle(e.getTitle());    // Copie le titre de l'événement
        setTiming(e.getTiming());  // Copie le timing de l'événement
        currentCode++;             // Incrémente le compteur des événements créés
    }

    // ***** Destructeur *****
    // Libère la mémoire allouée pour le titre et le timing, et décrémente le compteur currentCode
    Event::~Event()
    {
        #ifdef DEBUG
        cout << ">>> Event: destructeur <<<" << endl;
        #endif
        if (title) delete[] title;   // Libère la mémoire allouée pour le titre
        if (timing) delete timing;    // Libère la mémoire allouée pour le timing
        currentCode--;               // Décrémente le compteur des événements créés
    }

    // ***** getXXX / setXXX *****

    // Modifie le code de l'événement, mais seulement si le code est supérieur ou égal à 1
    void Event::setCode(int c)
    {
        if(c < 1) return;  // Si le code est inférieur à 1, il n'est pas modifié
        code = c;
    }

    // Modifie le titre de l'événement
    // Alloue dynamiquement de la mémoire pour stocker la chaîne de caractères
    void Event::setTitle(const char* t)
    {
        if (t == nullptr) return;  // Si le titre est nul, il n'est pas modifié
        if (title) delete[] title;  // Libère la mémoire précédemment allouée pour le titre
        title = new char[strlen(t) + 1]; // Alloue de la mémoire pour le nouveau titre
        strcpy(title, t);           // Copie le titre dans la mémoire allouée
    }

    // Modifie le timing de l'événement en copiant un objet `Timing` existant
    void Event::setTiming(const Timing& tm)
    {
        if(timing) delete timing;  // Libère la mémoire précédemment allouée pour le timing
        timing = new Timing(tm);   // Alloue de la mémoire pour un nouvel objet `Timing`
    }

    // Renvoie le code de l'événement
    int Event::getCode() const
    {
        return code;
    }

    // Renvoie le titre de l'événement
    const char* Event::getTitle() const
    {
        return title;
    }

    // Renvoie une copie de l'objet `Timing` associé à l'événement
    const Timing Event::getTiming() const
    {
        return *timing;
    }

    // ***** Autres méthodes de l'interface *****

    // Affiche les informations de l'événement (code, titre et timing)
    void Event::display() const
    {
        cout << "Event (" << code << ") :" << title << endl;  // Affiche le code et le titre
        if (timing)  // Si un timing est défini, affiche ses détails
        {
            timing->display();  // Appelle la méthode display de l'objet `Timing`
        }
        else  // Si aucun timing n'est défini, affiche un message
        {
            cout << "Timing non planifié" << endl;  
        }
    }
}
