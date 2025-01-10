#ifndef GROUP_H
#define GROUP_H
#include "Schedulable.h"
namespace planning
{
  class Group : public Schedulable{

    friend ostream& operator<<(ostream& o, const Group& g);
    friend istream& operator>>(istream& i, Group& g);

  private:
    string name;

  public:
    Group();
    Group(int, const string&);
    Group(const Group& group) = default;
    ~Group() = default;

    void setName(const string& name);
    string getName() const;

    string toString() const override;
    string tuple() const override;

    Group& operator=(const Group& group);
    bool operator<(const Group& group) const;

  };
}
#endif