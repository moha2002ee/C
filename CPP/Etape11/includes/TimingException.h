#ifndef TIMINGEXCEPTION_H
#define TIMINGEXCEPTION_H
#include <iostream>
#include <stdio.h>
#include "Exception.h"

using namespace std;
namespace planning
{

  class TimingException : public Exception
  {
  private:
    int code;

  public:
    static const int INVALID_DAY = 1;
    static const int NO_TIMING = 2;
    static const int NO_PROF = 3;
    static const int NO_LOCAL = 4;
    static const int NO_GROUP = 5;

    TimingException();
    TimingException(const string &message, int code);
    TimingException(const Exception &e, const TimingException &te);
    virtual ~TimingException() = default;
    int getCode() const;
  };
}

#endif