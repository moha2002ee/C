#include "Time.h"
#include "TimeException.h"
#include <iostream>

using namespace std;

namespace planning
{

    Time::Time(int d)
    {
        int h = d / 60;
        int m = d % 60;
        setHour(h);
        setMinute(m);
    }

    Time::Time(int h, int m)
    {
        setHour(h);
        setMinute(m);
    }

    Time::Time()
    {
        setHour(0);
        setMinute(0);
    }

    Time::~Time() {}

    // Accessors
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
            throw TimeException("l'heure n'est pas bien pas saisie ", TimeException::INVALID_HOUR);
        }
        hour = h;
    }

    void Time::setMinute(int m)
    {
        if (m < 0 || m >= 60)
        {
            throw TimeException("la minute est pas bien saisie", TimeException::INVALID_MINUTE);
        }
        minute = m;
    }

    // Display function
    void Time::display() const
    {
        cout << "\nHour    => " << hour << "h\n";
        cout << "Minute   => " << minute << "m\n";
    }

    // Overloaded operators
    Time Time::operator+(Time t)
    {/*
        Time result;
        result.hour = hour + t.hour;
        result.minute = minute + t.minute;

        // Handle overflow
        if (result.minute >= 60)
        {
            result.minute -= 60;
            result.hour++;
        }

        if (result.hour >= 24)
        {
            throw TimeException("tu depasse les 23h donc non ", TimeException::OVERFLOW);
        }

        return result;
*/
        return Time(hour*60 + t.hour*60 + minute + t.minute);
    }

    Time &Time::operator=(const Time &t)
    {
        if (this != &t)
        {
            hour = t.hour;
            minute = t.minute;
        }
        return *this;
    }

    Time operator+(int n, const Time &t)
    {
        Time result = t;
        result.minute += n;

        if (result.minute >= 60)
        {
            result.minute -= 60;
            result.hour++;
        }

        if (result.hour >= 24)
        {
            throw TimeException("l'heure est plus grande que 23 donc non ", TimeException::OVERFLOW);
        }

        return result;
    }

    Time Time::operator-(int m)
    {
        Time temp(*this);
        temp.minute = (temp.hour * 60) + temp.minute;
        temp.minute -= m;

        if (temp.minute < 0)
        {
            throw TimeException("la minute est plus petite que 0 donc non ", TimeException::OVERFLOW);
        }

        temp.hour = temp.minute / 60;
        temp.minute = temp.minute % 60;

        return temp;
    }

    Time operator-(int m, const Time &t)
    {
        Time temp;
        temp.hour = m / 60;
        temp.minute = m % 60;
        m = (t.hour * 60) + t.minute;
        return temp - m;
    }

    Time Time::operator-(const Time &t2)
    {
        Time temp(*this);
        int m = (t2.hour * 60) + t2.minute;
        return temp - m;
    }

    int Time::operator<(const Time &t)
    {
        return comptH(t) == -1;
    }

    int Time::operator>(const Time &t)
    {
        return comptH(t) == 1;
    }

    int Time::operator==(const Time &t)
    {
        return comptH(t) == 0;
    }

    int Time::comptH(const Time &t)
    {
        if (hour < t.hour)
            return -1;
        if (hour > t.hour)
            return 1;
        if (minute < t.minute)
            return -1;
        if (minute > t.minute)
            return 1;
        return 0;
    }

    // Overloaded >> operator for input
    istream &operator>>(istream &s, Time &t)
    {
        int h, m;
        do
        {
            cout << "Enter hour (0-23): ";
            s >> h;
            try
            {
                t.setHour(h);
                break;
            }
            catch (const TimeException &e)
            {
                cout << e.getMessage() << "\n";
            }
        } while (true);

        do
        {
            cout << "Enter minute (0-59): ";
            s >> m;
            try
            {
                t.setMinute(m);
                break;
            }
            catch (const TimeException &e)
            {
                cout << e.getMessage() << "\n";
            }
        } while (true);

        return s;
    }

    ostream &operator<<(ostream &s, const Time &t)
    {
        s << "Hour => " << t.getHour() << "h "
          << "Minutes => " << t.getMinute() << "m";
        return s;
    }

    // Pre-increment and post-increment operators
    Time Time::operator++()
    {
        (*this) = (*this) + 1;
        if (this->hour > 23 && this->minute > 59)
        {
            throw TimeException("Lheure est plus grande que 23h59", TimeException::OVERFLOW);
        }
        return (*this);
    }

    Time Time::operator++(int)
    {
        Time temp(*this);
        (*this) = (*this) + 1;
        if (this->hour > 23 && this->minute > 59)
        {
            throw TimeException("Lheure est plus grande que 23h59", TimeException::OVERFLOW);
        }
        return temp;
    }

    Time Time::operator--()
    {
        (*this) = (*this) - 1;
        if (this->hour < 0 && this->minute < 0)
        {
            throw TimeException("Lheure est plus petite que 00h00", TimeException::OVERFLOW);
        }
        return (*this);
    }

    Time Time::operator--(int)
    {
        Time temp(*this);
        (*this) = (*this) - 1;
        if (this->hour < 0 && this->minute < 0)
        {
            throw TimeException("Lheure est plus petite que 00h00", TimeException::OVERFLOW);
        }
        return temp;
    }
}
