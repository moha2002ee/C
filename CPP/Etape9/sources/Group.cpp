#include "Group.h"
namespace planning
{
  // ---constructeur---
  Group::Group() : Schedulable(){
    cout << "---Group: constructeur par defaut" << endl;
    setName("pas de groupe");
  }
  Group::Group(int id, const string& name) : Schedulable(id){
    cout << "---Group: constructeur d'initialisation" << endl;
    setName(name);
  }
  // --- set(xxx) et get(xxx) ---
  void Group::setName(const string& name){
    this->name = name;
  }
  string Group::getName() const{
    return name;
  }


  // ---methode override---
  string Group::toString() const {
    ostringstream oss;
    oss << name;
    return oss.str();
  }
  string Group::tuple() const {
    ostringstream oss;
    oss << id << ";" << name;
    return oss.str();
  }


  //--- operateurs---
  ostream& operator<<(ostream& o, const Group& g)
  {
     o << g.toString();
    return o;
  }
  Group& Group::operator=(const Group& group){
    setId(group.id);
    setName(group.name);
    return (*this);
  }

  bool Group::operator<(const Group& group) const
  {
    return (getName() < group.getName());
  }

}