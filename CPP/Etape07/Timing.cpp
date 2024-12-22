#include "Timing.h"
#include "TimingException.h"
using namespace std;

namespace planning
{
    const string Timing::MONDAY = "Lundi";
    const string Timing::TUESDAY = "Mardi";
    const string Timing::WEDNESDAY = "Mercredi";
    const string Timing::THURSDAY = "Jeudi";
    const string Timing::FRIDAY = "Vendredi";
    const string Timing::SATURDAY = "Samedi";
    const string Timing::SUNDAY = "Dimanche";

    Time Timing::getDuration() const
    {
        return duration;
    }

    string Timing::getDay() const
    {
        return day;
    }

    Time Timing::getStart() const
    {
        return start;
    }

    void Timing::setStart(const Time &e)
    {
        start = e;
    }

    void Timing::setDuration(const Time &e)
    {
        duration = e;
    }

    void Timing::setDay(const string &d)
    {
        // Vérifie si le jour passé en paramètre est valide
        if (d != MONDAY && d != TUESDAY && d != WEDNESDAY && d != THURSDAY &&
            d != FRIDAY && d != SATURDAY && d != SUNDAY)
        {
            // Lance une exception si le jour n'est pas valide
            throw TimingException("jour erreone", TimingException::INVALID_DAY);
        }
        day = d; // Si le jour est valide, on l'assigne à l'objet
    }

    // Constructeur prenant un jour, une heure de début et une durée
    Timing::Timing(const string &d, const Time &s, const Time &du)
        : day(d), start(s), duration(du)
    {
        setDay(d); // Appelle setDay pour valider le jour
    }

    // Constructeur par défaut (on ne l'initialise plus à "default")
    Timing::Timing()
        : day(MONDAY), start(Time()), duration(Time()) // Initialise avec un jour valide
    {
    }

    Timing::~Timing()
    {
    }

    void Timing::display() const
    {
        cout << "Jour     => " << day << "\n";
        start.display();
        duration.display();
    }

    Timing &Timing::operator=(const Timing &t)
    {
        setDay(t.getDay());
        setStart(t.getStart());
        setDuration(t.getDuration());
        return (*this);
    }

    int Timing::operator<(const Timing &t)
    {
        return compT(t) == -1;
    }

    int Timing::operator>(const Timing &t)
    {
        return compT(t) == 1;
    }

    int Timing::operator==(const Timing &t)
    {
        return compT(t) == 0;
    }

    int Timing::compT(const Timing &t)
    {
        // Créer un tableau avec l'ordre des jours de la semaine
        static const string daysOfWeek[] = {
            MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};

        // Trouver l'indice du jour dans le tableau daysOfWeek
        int dayIndex = -1, tDayIndex = -1;
        for (int i = 0; i < 7; ++i)
        {
            if (day == daysOfWeek[i])
                dayIndex = i;
            if (t.day == daysOfWeek[i])
                tDayIndex = i;
        }

        // Comparer les jours de la semaine
        if (dayIndex < tDayIndex)
            return -1;
        if (dayIndex > tDayIndex)
            return 1;

        // Si les jours sont égaux, comparer l'heure de début
        if (start < t.start)
            return -1;
        if (start > t.start)
            return 1;

        // Si les heures de début sont égales, comparer la durée
        if (duration < t.duration)
            return -1;
        if (duration > t.duration)
            return 1;

        // Si tout est égal
        return 0;
    }
    ostream &operator<<(ostream &o, const Timing &tmg)
    {
        o << "<Timing>" << endl;
        o << "<day>" << endl;
        o << tmg.day << endl;
        o << "</day>" << endl;
        o << "<start>" << endl;
        o << tmg.start << endl;
        o << "</start>" << endl;
        o << "<duration>" << endl;
        o << tmg.duration << endl;
        o << "</duration>" << endl;
        o << "</Timing>";
        return o;
    }
    istream &operator>>(istream &i, Timing &tmg)
    {
        string sDay, tag;
        Time tempStart, tempDuration;
        getline(i, tag);
        getline(i, tag);
        getline(i, sDay);
        getline(i, tag);
        getline(i, tag);
        i >> tempStart;
        getline(i, tag);
        getline(i, tag);
        i >> tempDuration;
        getline(i, tag);
        getline(i, tag);

        tmg.setDay(sDay);
        tmg.setStart(tempStart);
        tmg.setDuration(tempDuration);
        return i;
    }
    string Timing::toString() const noexcept
    {
        ostringstream oss;
        oss << day << ";" << start.toString() << ";" << duration.toString();

        return oss.str();
    }

}
