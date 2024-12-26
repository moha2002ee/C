#include "Classroom.h"
namespace planning {

    // Constructeur par défaut
    Classroom::Classroom() : Schedulable() {
        cout << "---Classroom: constructeur par défaut---" << endl;
        setName("aucune classe");
        setSeatingCapacity(0);
    }

    // Constructeur d'initialisation
    Classroom::Classroom(int id, const string& name, int seatCap) : Schedulable(id) {
        cout << "---Classroom: constructeur d'initialisation---" << endl;
        setName(name);
        setSeatingCapacity(seatCap);
    }

    // Accesseurs
    void Classroom::setName(const string& name) {
        this->name = name;
    }

    void Classroom::setSeatingCapacity(int seatCap) {
        seatingCapacity = seatCap;
    }

    string Classroom::getName() const {
        return name;
    }

    int Classroom::getSeatingCapacity() const {
        return seatingCapacity;
    }

    // Méthodes pour afficher les informations
    string Classroom::toString() const {
        return name + " (" + to_string(seatingCapacity) + ")";
    }

    string Classroom::tuple() const {
        return to_string(id) + ";" + name + " (" + to_string(seatingCapacity) + ")";
    }

    // Surcharge de l'opérateur <<
    ostream& operator<<(ostream& o, const Classroom& c) {
        o << "<Classroom>\n";
        o << "<id>\n" << c.id << "\n</id>\n";
        o << "<name>\n" << c.name << "\n</name>\n";
        o << "<seatingCapacity>\n" << c.seatingCapacity << "\n</seatingCapacity>\n";
        o << "</Classroom>";
        return o;
    }

    // Surcharge de l'opérateur >>
    istream& operator>>(istream& i, Classroom& c) {
        string sId, sName, sSeatingCapacity, tag;
        getline(i, tag);  // <Classroom>
        getline(i, tag);  // <id>
        getline(i, sId);
        getline(i, tag);  // </id>
        getline(i, tag);  // <name>
        getline(i, sName);
        getline(i, tag);  // </name>
        getline(i, tag);  // <seatingCapacity>
        getline(i, sSeatingCapacity);
        getline(i, tag);  // </seatingCapacity>
        getline(i, tag);  // </Classroom>

        c.setId(stoi(sId));
        c.setName(sName);
        c.setSeatingCapacity(stoi(sSeatingCapacity));
        return i;
    }

    // Surcharge de l'opérateur =
    Classroom& Classroom::operator=(const Classroom& c) {
        setId(c.id);
        setName(c.name);
        setSeatingCapacity(c.seatingCapacity);
        return *this;
    }

    // Surcharge de l'opérateur <
    bool Classroom::operator<(const Classroom& c) const {
        return name < c.name;
    }

}
