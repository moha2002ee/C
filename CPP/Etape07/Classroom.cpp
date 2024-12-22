#include "Classroom.h"
namespace planning
{
  // ---constructeur---
  Classroom::Classroom() : Schedulable(){
    cout << "---Classroom: constructeur par defaut" << endl;
    setName("pas de classe");
    setSeatingCapacity(0);
  }
  Classroom::Classroom(int id, const string& name, int seatCap) : Schedulable(id){
    cout << "---Classroom: constructeur d'initialisation" << endl;
    setName(name);
    setSeatingCapacity(seatCap);
  }
  // --- set(xxx) et get(xxx) ---
  void Classroom::setName(const string& name){
    this->name = name;
  }
  void Classroom::setSeatingCapacity(int seatCap){
    seatingCapacity = seatCap;
  }
  string Classroom::getName() const{
    return name;
  }
  int Classroom::getSeatingCapacity() const{
    return seatingCapacity;
  }

  // ---methode override---
  string Classroom::toString() const {
    ostringstream oss;
    oss << name << "("<< seatingCapacity << ")";
    return oss.str();
  }
  string Classroom::tuple() const {
    ostringstream oss;
    oss << id << ";" << name << "("<< seatingCapacity << ")";
    return oss.str();
  }


  //--- operateurs---
  ostream& operator<<(ostream& o, const Classroom& c)
  {
    o << "<Classroom>" << endl;
    o << "<id>" << endl;
    o << c.id << endl;
    o << "</id>" << endl;
    o << "<name>" << endl;
    o << c.name << endl;
    o << "</name>" << endl;
    o << "<seatingCapacity>" << endl;
    o << c.seatingCapacity << endl;
    o << "</seatingCapacity>" << endl;
    o << "</Classroom>";
    
    return o;
  }
  istream& operator>>(istream& i, Classroom& c)
  {
    string sId, sName, sSeatingCapacity, tag;
    getline(i, tag);
    getline(i, tag);
    getline(i, sId);
    getline(i, tag);
    getline(i, tag);
    getline(i, sName);
    getline(i, tag);
    getline(i, tag);
    getline(i, sSeatingCapacity);
    getline(i, tag);
    getline(i, tag);


    c.setId(stoi(sId));
    c.setName(sName);
    c.setSeatingCapacity(stoi(sSeatingCapacity));
    return i;
  }

  Classroom& Classroom::operator=(const Classroom& Classroom){
    setId(Classroom.id);
    setName(Classroom.name);
    setSeatingCapacity(Classroom.seatingCapacity);
    return (*this);
  }
}