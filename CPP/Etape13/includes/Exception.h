#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <sstream>
#include <stdio.h>
using namespace std;
namespace planning
{

  class Exception
  {
  protected:
    string message;
  public:
    Exception();
    Exception(const string& message);
    Exception(const Exception& e);
    virtual ~Exception() = default;
    string getMessage() const;
  };
}

#endif