#include "Time.h"    // Inclut le fichier d'en-tête "Time.h" qui contient la déclaration de la classe Time.

namespace planning   // Espace de noms "planning" pour organiser le code et éviter les conflits.
{
    // Constructeur : Initialise un objet Time à partir d'un entier représentant le nombre total de minutes.
    Time::Time(int d)
    {
        // Calcule les heures (h) et les minutes (m) à partir du nombre total de minutes (d).
        int h = d / 60;     // Divise par 60 pour obtenir les heures.
        int m = d % 60;     // Utilise le modulo pour obtenir le reste (les minutes).

        // Appelle les méthodes setHour et setMinute pour initialiser les valeurs.
        setHour(h);
        setMinute(m);
    }

    // Constructeur : Initialise un objet Time avec des heures et des minutes spécifiées.
    Time::Time(int h, int m)
    {
        // Appelle les méthodes setMinute et setHour pour initialiser les valeurs.
        setMinute(m);
        setHour(h);
    }

    // Getter pour l'heure : retourne l'heure de l'objet Time.
    int Time::getHour() const
    {
        return hour;
    }

    // Getter pour les minutes : retourne les minutes de l'objet Time.
    int Time::getMinute() const
    {
        return minute;
    }

    // Constructeur par défaut : Initialise un objet Time à 0 heure et 0 minute.
    Time::Time(/* args */)
    {
        setHour(0);   // Définit l'heure à 0.
        setMinute(0); // Définit les minutes à 0.
    }

    // Destructeur : Le destructeur ne fait rien ici, mais peut être utilisé pour libérer de la mémoire si nécessaire.
    Time::~Time()
    {
    }

    // Setter pour l'heure : Définit l'heure à la valeur spécifiée.
    void Time::setHour(int h)
    {
        hour = h;   // Attribue la valeur de h à l'attribut hour.
    }

    // Setter pour les minutes : Définit les minutes à la valeur spécifiée.
    void Time::setMinute(int m)
    {
        minute = m; // Attribue la valeur de m à l'attribut minute.
    }

    // Méthode d'affichage : Affiche l'heure et les minutes de l'objet Time.
    void Time::display() const
    {
        // Affiche l'heure et les minutes avec un format lisible.
        cout << "Heure    => " << hour << "h\n";
        cout << "Minute   => " << minute << "m\n";
    }
}
