#ifndef CLASSROOM_H
#define CLASSROOM_H
#include "Schedulable.h"
namespace planning
{

  class Classroom : public Schedulable{

    friend ostream& operator<<(ostream& o, const Classroom& c);
    friend istream& operator>>(istream& i, Classroom& c);

  private:
    string name;
    int seatingCapacity;
  public:
    Classroom();
    Classroom(int, const string&, int);
    Classroom(const Classroom& classroom) = default;
    ~Classroom() = default;

    void setName(const string& name);
    void setSeatingCapacity(int seatCap);

    string getName() const;
    int getSeatingCapacity() const;

    string toString() const override;
    string tuple() const override;

    Classroom& operator=(const Classroom& classroom);
    bool operator<(const Classroom& classroom) const;
  };
}
#endif