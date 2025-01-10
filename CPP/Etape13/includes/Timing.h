#ifndef TIMING_H
#define TIMING_H
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
#include "Time.h"
#include "TimingException.h"

namespace planning
{
  class Timing
  {
    friend ostream& operator<<(ostream& o, const Timing& tmg);
    friend istream& operator>>(istream& i, Timing& tmg);

  private:
    string day;
    Time start;
    Time duration;
    int compT(const Timing& t) noexcept;
    

  public:
    const static string MONDAY;
    const static string TUESDAY;
    const static string WEDNESDAY;
    const static string THURSDAY;
    const static string FRIDAY;
    const static string SATURDAY;
    const static string SUNDAY;
    const static string DAYS[7];

    Timing() noexcept;
    Timing(string d, Time s, Time dt);
    Timing(const Timing& t)noexcept;
    ~Timing();

    string getDay() const noexcept;
    Time getStart() const noexcept;
    Time getDuration() const noexcept;

    void setDay(string d);
    void setStart(Time s);
    void setDuration(Time dt);

    void display() const noexcept;
    string toString() const noexcept;
    bool intersect(const Timing& t);
    
    Timing& operator=(const Timing& t) noexcept;

    int operator<(const Timing& t) noexcept;
    int operator>(const Timing& t) noexcept;
    int operator==(const Timing& t) noexcept;
  };
}
#endif