#include "Timing.h"
using namespace std;

namespace planning
{
    // Constantes statiques représentant les jours de la semaine.
    // Ces constantes seront utilisées pour éviter les erreurs de chaîne de caractères
    // lors de l'assignation du jour dans l'objet Timing.
    const string Timing::MONDAY = "Lundi";
    const string Timing::TUESDAY = "Mardi";
    const string Timing::WEDNESDAY = "Mercredi";
    const string Timing::THURSDAY = "Jeudi";
    const string Timing::FRIDAY = "Vendredi";
    const string Timing::SATURDAY = "Samedi";
    const string Timing::SUNDAY = "Dimanche";

    // **Méthodes Getters**
    Time Timing::getDuration() const
    {
        return duration;  // Renvoie la durée de l'événement sous forme d'objet Time
    }

    string Timing::getDay() const     // Cette méthode est const car elle ne modifie pas l'objet.
    {
        return day;   // Renvoie le jour de la semaine sous forme de chaîne de caractères
    }

    Time Timing::getStart() const
    {
        return start;  // Renvoie l'heure de début de l'événement sous forme d'objet Time
    }

    // **Méthodes Setters**
    void Timing::setStart(const Time &e)
    {
        start = e;  // Définit l'heure de début de l'événement
    }

    void Timing::setDuration(const Time &e)
    {
        duration = e;  // Définit la durée de l'événement
    }

    void Timing::setDay(const string& d)  // Le jour est passé par référence constante pour éviter la copie inutile
    {
        day = d;  // Définit le jour de la semaine
    }   

    // **Constructeur avec paramètres**
    // Ce constructeur permet d'initialiser un objet Timing avec un jour, une heure de début et une durée.
    Timing::Timing(const string& d, const Time &s, const Time &du)
    {
        day = d;      // Initialise le jour de la semaine
        start = s;    // Initialise l'heure de début
        duration = du; // Initialise la durée
    }

    // **Constructeur par défaut**
    // Ce constructeur initialise le jour à une valeur par défaut "default"
    Timing::Timing()
    {
        setDay("default");  // Définit le jour à "default"
    }

    // **Destructeur**
    Timing::~Timing()
    {
        // Aucune ressource dynamique n'est allouée, donc le destructeur est vide.
        // Mais s'il y avait des objets alloués dynamiquement, c'est ici qu'on les libérerait.
    }

    // **Méthode d'affichage**
    // Cette méthode affiche le jour, l'heure de début et la durée de l'événement.
    void Timing::display() const
    {
        cout << "Jour     => " << day << "\n";  // Affiche le jour de la semaine
        start.display();     // Appelle la méthode display de la classe Time pour afficher l'heure de début
        duration.display();  // Appelle la méthode display de la classe Time pour afficher la durée
    }
}
