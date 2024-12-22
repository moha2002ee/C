#include <string>
#include <iostream>
#include <cstdlib>
#include "Time.h"

#ifndef TIMING_H // Check if TIMING_H is not already defined
#define TIMING_H // Define TIMING_H to prevent multiple inclusions of this header

using namespace std;

namespace planning
{
    // Timing class definition
    class Timing
    {
    private:
        string day;       // The day of the week
        Time start;       // Start time
        Time duration;    // Duration of the event

    public:
        // Static constants for the days of the week
        static const string MONDAY;
        static const string TUESDAY;
        static const string WEDNESDAY;
        static const string THURSDAY;
        static const string FRIDAY;
        static const string SATURDAY;
        static const string SUNDAY;

        // Assignment operator to copy the values of another Timing object
        Timing &operator=(const Timing &t);

        // Comparison operators to compare two Timing objects
        int operator<(const Timing &t);
        int operator>(const Timing &t);
        int operator==(const Timing &t);

        // Helper function to compare two Timing objects based on the day of the week
        int compT(const Timing &t);
        
        // Default constructor (sets default values for the Timing object)
        Timing();

        // Destructor (doesn't do anything here, but could be used for future cleanup)
        ~Timing();

        // Method to display the timing information
        void display() const;

        // Setter methods to set day, start time, and duration
        void setDay(const string &d);
        void setStart(const Time &e);  // Set start time with Time object
        void setStart(int h, int m);   // Set start time using hour and minute integers
        void setDuration(const Time &e); // Set the duration using a Time object

        // Getter methods to retrieve day, start time, and duration
        string getDay() const;
        Time getStart() const;
        Time getDuration() const;

        // Parameterized constructor to initialize day, start time, and duration
        Timing(const string &d, const Time &s, const Time &du);
    };
}

#endif // End of the TIMING_H definition guard
