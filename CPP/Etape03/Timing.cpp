#include "Timing.h"
using namespace std;

namespace planning
{
    // Constants for the days of the week
    const string Timing::MONDAY = "Lundi";
    const string Timing::TUESDAY = "Mardi";
    const string Timing::WEDNESDAY = "Mercredi";
    const string Timing::THURSDAY = "Jeudi";
    const string Timing::FRIDAY = "Vendredi";
    const string Timing::SATURDAY = "Samedi";
    const string Timing::SUNDAY = "Dimanche";

    // Getter for the duration of the timing
    Time Timing::getDuration() const
    {
        return duration;
    }

    // Getter for the day of the timing
    string Timing::getDay() const
    {
        return day;
    }

    // Getter for the start time of the timing
    Time Timing::getStart() const
    {
        return start;
    }

    // Setter for the start time of the timing
    void Timing::setStart(const Time &e)
    {
        start = e;
    }

    // Setter for the duration of the timing
    void Timing::setDuration(const Time &e)
    {
        duration = e;
    }

    // Setter for the day of the timing
    void Timing::setDay(const string &d)
    {
        day = d;
    }

    // Constructor that initializes the timing with a given day, start time, and duration
    Timing::Timing(const string &d, const Time &s, const Time &du)
        : day(d), start(s), duration(du)
    {
    }

    // Default constructor that sets the day to "default"
    Timing::Timing()
    {
        setDay("default");
    }

    // Destructor (currently doesn't do anything)
    Timing::~Timing()
    {
    }

    // Method to display the day, start time, and duration of the timing
    void Timing::display() const
    {
        cout << "Jour     => " << day << "\n";  // Prints the day
        start.display();  // Displays the start time
        duration.display();  // Displays the duration
    }

    // Assignment operator to copy values from another Timing object
    Timing &Timing::operator=(const Timing &t)
    {
        setDay(t.getDay());
        setStart(t.getStart());
        setDuration(t.getDuration());
        return (*this);
    }

    // Comparison operator to check if the current Timing is less than another one
    int Timing::operator<(const Timing &t)
    {
        return compT(t) == -1;
    }

    // Comparison operator to check if the current Timing is greater than another one
    int Timing::operator>(const Timing &t)
    {
        return compT(t) == 1;
    }

    // Comparison operator to check if the current Timing is equal to another one
    int Timing::operator==(const Timing &t)
    {
        return compT(t) == 0;
    }

    // Helper function to compare two Timing objects based on the day of the week
    int Timing::compT(const Timing &x)
    {
        // Return an integer based on the comparison of the days
        if(x.day == "Lundi") return 1;
        if(x.day == "Mardi") return 2;
        if(x.day == "Mercredi") return 3;
        if(x.day == "Jeudi") return 4;
        if(x.day == "Vendredi") return 5;
        if(x.day == "Samedi") return 6;
        if(x.day == "Dimanche") return 7;

        return -1; // Return -1 in case of an error
    }
}
