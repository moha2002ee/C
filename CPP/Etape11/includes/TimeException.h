#ifndef TIMEEXCEPTION_H
#define TIMEEXCEPTION_H
#include <iostream>
#include <stdio.h>
#include "Exception.h"

using namespace std;
namespace planning
{

  class TimeException:public Exception
  {
  private:
    int code;
  public:
    static const int INVALID_HOUR = 1;
    static const int INVALID_MINUTE = 2;
    static const int OVERFLOW = 3;

    TimeException();
    TimeException(const string& message, int code);
    TimeException(const Exception& e, const TimeException& te);
    virtual ~TimeException() = default;
    int getCode() const;
  };
}

#endif