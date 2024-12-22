#include "Professor.h"
namespace planning
{

  // ---constructeur---
  Professor::Professor() : Schedulable(){
    cout << "---Professor: constructeur par defaut" << endl;
    setLastName("nom");
    setFirstName("prenom");
  }
  Professor::Professor(int id, const string& nom, const string& prenom) : Schedulable(id){
    cout << "---Professor: constructeur d'initialisation" << endl;
    
    setLastName(nom);
    setFirstName(prenom);
  }
  // --- set(xxx) et get(xxx) ---
  void Professor::setLastName(const string& lName){
    lastName = lName;
  }
  void Professor::setFirstName(const string& fName){
    firstName = fName;
  }
  string Professor::getLastName() const{
    return lastName;
  }
  string Professor::getFirstName() const{
    return firstName;
  }


  // ---methode override---
  string Professor::toString() const {
    ostringstream oss;
    oss << lastName << " " << firstName;
    return oss.str();
  }
  string Professor::tuple() const {
    ostringstream oss;
    oss << id << ";" << firstName << ";" << lastName ;
    return oss.str();
  }


  //--- operateurs---
  ostream& operator<<(ostream& o, const Professor& p)
  {
     o << p.toString();
    return o;
  }
  Professor& Professor::operator=(const Professor& prof){
    setId(prof.id);
    setLastName(prof.lastName);
    setFirstName(prof.firstName);
    return (*this);
  }

  bool Professor::operator<(const Professor& prof) const
  {
    return (getLastName() < prof.getLastName());
  } 

}