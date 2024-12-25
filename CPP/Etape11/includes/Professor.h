#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "Schedulable.h"
namespace planning
{
  class Professor : public Schedulable{
    friend istream& operator>>(istream& i, Professor& p);
    friend ostream& operator<<(ostream& o, const Professor& p);

  private:
    string lastName;
    string firstName;

  public:
    Professor();
    Professor(int, const string&, const string&);
    Professor(const Professor& prof) = default;
    ~Professor() = default;

    void setLastName(const string& lName);
    void setFirstName(const string& fName);
    string getLastName() const;
    string getFirstName() const;

    string toString() const override;
    string tuple() const override;

    Professor& operator=(const Professor& prof);
    bool operator<(const Professor& prof) const; 

  };
}

#endif