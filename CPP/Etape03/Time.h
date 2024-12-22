#ifndef TIME_H
#define TIME_H

#include <iostream> // For using istream and ostream

namespace planning
{
    class Time
    {
    private:
        int hour;   // The hour part of time (0 to 23)
        int minute; // The minute part of time (0 to 59)
        
        // Private helper method for comparing two Time objects
        int comptH(const Time &t); 

    public:
        // Constructors and Destructor
        Time();          // Default constructor (00:00)
        Time(int d);     // Constructor that takes total minutes
        Time(int h, int m); // Constructor that takes hours and minutes
        ~Time();         // Destructor

        // Accessor (getter) and mutator (setter) methods
        int getHour() const;    // Get the hour
        int getMinute() const;  // Get the minute
        void setHour(int h);    // Set the hour
        void setMinute(int m);  // Set the minute

        // Method to display time
        void display() const; 

        // Operator overloads
        Time operator+(Time t);   // Addition of two Time objects
        Time operator++(int);     // Postfix increment operator
        Time operator++();        // Prefix increment operator
        Time operator--();        // Prefix decrement operator
        Time operator--(int);     // Postfix decrement operator

        // Assignment operator
        Time &operator=(const Time &t);

        // Subtraction operators
        friend Time operator+(int n, const Time &t); // Adding an integer to a Time object (in minutes)
        Time operator-(int m);                       // Subtracting an integer from Time (in minutes)
        friend Time operator-(int m, const Time &t); // Subtracting Time from an integer (in minutes)
        Time operator-(const Time &t2);              // Subtracting two Time objects

        // Comparison operators
        int operator<(const Time &t);   // Less than operator
        int operator>(const Time &t);   // Greater than operator
        int operator==(const Time &t);  // Equality operator

        // Input/output stream overloads for reading and printing Time
        friend std::istream &operator>>(std::istream &s, Time &t);  // Input stream
        friend std::ostream &operator<<(std::ostream &s, const Time &t); // Output stream
    };
}

#endif
