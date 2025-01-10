#ifndef TIME_H
#define TIME_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include "TimeException.h"
using namespace std;

namespace planning
{
  class Time
  {
    friend Time operator+(int m, const Time& t);
    friend Time operator-(int m, const Time& t);
    friend ostream& operator<<(ostream& o, const Time& t) noexcept;
    friend istream& operator>>(istream& i, Time& t);

  private:
    int hour;
    int minute;
    int compT(const Time& t) noexcept;

  public:
    Time() noexcept;
    Time(int h, int m);
    Time(int m);
    Time(const Time& e) noexcept;
    ~Time();
    
    int getHour() const noexcept;
    int getMinute() const noexcept;
    void setHour(int h);
    void setMinute(int m);
    
    void display() const noexcept;
    string toString() const noexcept;
    Time& operator=(const Time& t) noexcept;
    Time operator+(int m);
    Time operator+(const Time& t2);
    Time operator-(int m);
    Time operator-(const Time& t2);

    int operator<(const Time& t) noexcept;
    int operator>(const Time& t) noexcept;
    int operator==(const Time& t) noexcept;
    Time operator++();
    Time operator++(int);
    Time operator--();
    Time operator--(int);



  };
}

#endif