#ifndef SCHEDULABLE_H
#define SCHEDULABLE_H
#include <iostream>
#include <sstream>
#include <stdio.h>
using namespace std;
namespace planning
{
  class Schedulable
  {
  protected:
    int id;
  public:
    static int currentId;

    Schedulable();
    Schedulable(int id);
    Schedulable(const Schedulable& schedule) = default;
    virtual ~Schedulable() = default;
    void setId(int id);
    int getId() const;
    virtual string toString() const = 0;
    virtual string tuple() const = 0;
  };

}
#endif