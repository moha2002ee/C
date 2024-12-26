#include "Professor.h"

namespace planning {

    // --- opérateurs ---
    ostream& operator<<(ostream& o, const Professor& p) {
        o << "<Professor>" << endl;
        o << "<id>" << endl;
        o << p.getId() << endl;
        o << "</id>" << endl;
        o << "<lastName>" << endl;
        o << p.getLastName() << endl;
        o << "</lastName>" << endl;
        o << "<firstName>" << endl;
        o << p.getFirstName() << endl;
        o << "</firstName>" << endl;
        o << "</Professor>";
        return o;
    }

    istream& operator>>(istream& i, Professor& p) {
        string sId, sFirstName, sLastName, tag;

        getline(i, tag); // <Professor>
        getline(i, tag); // <id>
        getline(i, sId);
        getline(i, tag); // </id>
        getline(i, tag); // <lastName>
        getline(i, sLastName);
        getline(i, tag); // </lastName>
        getline(i, tag); // <firstName>
        getline(i, sFirstName);
        getline(i, tag); // </firstName>
        getline(i, tag); // </Professor>

        p.setLastName(sLastName);
        p.setId(stoi(sId));
        p.setFirstName(sFirstName);
        return i;
    }

    // --- constructeur ---
    Professor::Professor() : Schedulable() {
        cout << "---Professor: constructeur par defaut" << endl;
        setLastName("nom");
        setFirstName("prenom");
    }

    Professor::Professor(int id, const string& nom, const string& prenom) : Schedulable(id) {
        cout << "---Professor: constructeur d'initialisation" << endl;
        setLastName(nom);
        setFirstName(prenom);
    }

    // --- set(xxx) et get(xxx) ---
    void Professor::setLastName(const string& lName) {
        lastName = lName;
    }

    void Professor::setFirstName(const string& fName) {
        firstName = fName;
    }

    string Professor::getLastName() const {
        return lastName;
    }

    string Professor::getFirstName() const {
        return firstName;
    }

    // --- méthode override ---
    string Professor::toString() const {
        ostringstream oss;
        oss << lastName << " " << firstName;
        return oss.str();
    }

    string Professor::tuple() const {
        ostringstream oss;
        oss << id << ";" << lastName << ";" << firstName;
        return oss.str();
    }

    // --- opérateurs ---
    Professor& Professor::operator=(const Professor& prof) {
        setId(prof.id);
        setLastName(prof.lastName);
        setFirstName(prof.firstName);
        return (*this);
    }

    bool Professor::operator<(const Professor& prof) const {
        return (getLastName() < prof.getLastName());
    }

}
