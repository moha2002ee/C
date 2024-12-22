#include "Classroom.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// Constructeur par défaut
Classroom::Classroom() {
    setName("");
    setSeatingCapacity(0);
}

// Constructeur avec paramètres
Classroom::Classroom(int i, string n, int s):Schedulable(i) {
    setName(n);
    setSeatingCapacity(s);
}

// Setters
void Classroom::setName(string n) {
    name = n;
}

void Classroom::setSeatingCapacity(int s) {
    seatingCapacity = s;
}

// Getters
string Classroom::getName() const {
    return name;
}

int Classroom::getSeatingCapacity() const {
    return seatingCapacity;
}

// Méthode toString
string Classroom::toString() const {
    ostringstream oss;
    oss << id << name << " " << seatingCapacity;
    return oss.str();
}

// Méthode tuple
string Classroom::tuple() const {
    ostringstream oss;
    oss << id << ";" << name << ";" << seatingCapacity;
    return oss.str();
}

// Opérateur d'assignation
Classroom &Classroom::operator=(const Classroom &c) {
    setId(c.getId());  // Copier l'ID de l'objet source
    setName(c.getName());
    setSeatingCapacity(c.getSeatingCapacity());
    return *this;
}

// Opérateur de flux de sortie (sérialisation)
std::ostream &operator<<(std::ostream &os, const Classroom &c) {
    os << "<Classroom>" << endl;
    os << "<id>" << c.id << "</id>" << endl;  // Utiliser getId()
    os << "<name>" << c.getName() << "</name>" << endl;
    os << "<seatingCapacity>" << c.getSeatingCapacity() << "</seatingCapacity>" << endl;
    os << "</Classroom>" << endl;
    return os;
}

// Opérateur de flux d'entrée (désérialisation)
std::istream &operator>>(std::istream &i, Classroom &c) {
    string id, name, seat, tag;
    getline(i, tag);       // <Classroom>
    getline(i, tag);       // <id>
    getline(i, id);        // ID value
    getline(i, tag);       // </id>
    getline(i, tag);       // <name>
    getline(i, name);      // Name value
    getline(i, tag);       // </name>
    getline(i, tag);       // <seatingCapacity>
    getline(i, seat);      // Seating capacity value
    getline(i, tag);       // </seatingCapacity>
    getline(i, tag);       // </Classroom>
    
    return i;
}
