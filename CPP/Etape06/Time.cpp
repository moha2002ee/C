#include "Time.h"
#include "TimeException.h"
#include <iostream>
#include <stdexcept>

namespace planning
{

    // Constructeurs
    Time::Time() : hour(0), minute(0) {}

    Time::Time(int d)
    {
        hour = d / 60;   // Calcul des heures
        minute = d % 60; // Calcul des minutes
    }

    Time::Time(int h, int m) : hour(h), minute(m) {}

    // Destructeur
    Time::~Time() {}

    // Accesseurs et mutateurs
    int Time::getHour() const
    {
        return hour;
    }

    int Time::getMinute() const
    {
        return minute;
    }

    void Time::setHour(int h)
    {
        if (h < 0 || h >= 24)
        {
            throw TimeException("Invalid hour value", h);
        }
        hour = h;
    }

    void Time::setMinute(int m)
    {
        if (m < 0 || m >= 60)
        {
            throw TimeException("Invalid minute value", m);
        }
        minute = m;
    }

    // Méthode d'affichage
    void Time::display() const
    {
        std::cout << "Heure: " << hour << " Minutes: " << minute << std::endl;
    }

    // Surcharge des opérateurs arithmétiques
    Time Time::operator+(Time t)
    {
        int totalMinutes = (hour * 60 + minute) + (t.hour * 60 + t.minute);
        return Time(totalMinutes);
    }

    Time Time::operator++()
    {
        // Incrémentation pré-fixée
        minute++;
        if (minute == 60)
        {
            minute = 0;
            hour++;
            if (hour == 24)
            {
                hour = 0;
            }
        }
        return *this;
    }

    Time Time::operator++(int)
    {
        // Incrémentation post-fixée
        Time temp = *this;
        operator++();
        return temp;
    }

    Time Time::operator--()
    {
        // Décrémentation pré-fixée
        minute--;
        if (minute < 0)
        {
            minute = 59;
            hour--;
            if (hour < 0)
            {
                hour = 23;
            }
        }
        return *this;
    }

    Time Time::operator--(int)
    {
        // Décrémentation post-fixée
        Time temp = *this;
        operator--();
        return temp;
    }

    // Surcharge de l'opérateur d'assignation
    Time &Time::operator=(const Time &t)
    {
        if (this != &t)
        { // Protection contre l'auto-assignation
            hour = t.hour;
            minute = t.minute;
        }
        return *this;
    }

    // Surcharge des opérateurs pour la soustraction
    Time Time::operator-(int m)
    {
        int totalMinutes = (hour * 60 + minute) - m;
        return Time(totalMinutes);
    }

    Time operator+(int n, const Time &t)
    {
        int totalMinutes = (t.hour * 60 + t.minute) + n;
        return Time(totalMinutes);
    }

    Time operator-(int m, const Time &t)
    {
        int totalMinutes = m - (t.hour * 60 + t.minute);
        return Time(totalMinutes);
    }

    Time Time::operator-(const Time &t2)
    {
        int totalMinutes = (hour * 60 + minute) - (t2.hour * 60 + t2.minute);
        return Time(totalMinutes);
    }

    // Surcharge des opérateurs de comparaison
    int Time::operator<(const Time &t)
    {
        return (hour < t.hour) || (hour == t.hour && minute < t.minute);
    }

    int Time::operator>(const Time &t)
    {
        return (hour > t.hour) || (hour == t.hour && minute > t.minute);
    }

    int Time::operator==(const Time &t)
    {
        return (hour == t.hour) && (minute == t.minute);
    }

  ostream& operator<<(ostream& o, const Time& t) noexcept
  {
    o << "<Time>" << endl;
    o << "<hour>" << endl;
    o << t.hour << endl;
    o << "</hour>" << endl;
    o << "<minute>" << endl;
    o << t.minute << endl;
    o << "</minute>" << endl;
    o << "</Time>";
    return o;
  }
  istream& operator>>(istream& i, Time& t)
  {
    string sHour, sMinute, tag;
    getline(i, tag);
    getline(i, tag);
    getline(i, sHour);
    getline(i, tag);
    getline(i, tag);
    getline(i, sMinute);
    getline(i, tag);
    getline(i, tag);

    t.setHour(stoi(sHour));
    t.setMinute(stoi(sMinute));
    return i;
  }

}
