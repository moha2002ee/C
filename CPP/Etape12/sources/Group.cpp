#include "Group.h"

namespace planning {

    // --- opérateurs ---
    ostream& operator<<(ostream& o, const Group& g) {
        o << "<Group>" << endl;
        o << "<Id>" << endl;
        o << g.id << endl;
        o << "</Id>" << endl;
        o << "<name>" << endl;
        o << g.name << endl;
        o << "</name>" << endl;
        o << "</Group>";

        return o;
    }

    istream& operator>>(istream& i, Group& g) {
        string sId, sName, tag;
        getline(i, tag); // <Group>
        getline(i, tag); // <Id>
        getline(i, sId);
        getline(i, tag); // </Id>
        getline(i, tag); // <name>
        getline(i, sName);
        getline(i, tag); // </name>
        getline(i, tag); // </Group>

        g.setId(stoi(sId));
        g.setName(sName);
        return i;
    }

    // --- constructeur ---
    Group::Group() : Schedulable() {
        cout << "---Group: constructeur par defaut" << endl;
        setName("pas de groupe");
    }

    Group::Group(int id, const string& name) : Schedulable(id) {
        cout << "---Group: constructeur d'initialisation" << endl;
        setName(name);
    }

    // --- set(xxx) et get(xxx) ---
    void Group::setName(const string& name) {
        this->name = name;
    }

    string Group::getName() const {
        return name;
    }

    // --- méthode override ---
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

    // --- opérateurs ---
    Group& Group::operator=(const Group& group) {
        setId(group.id);
        setName(group.name);
        return (*this);
    }

    bool Group::operator<(const Group& group) const {
        return (getName() < group.getName());
    }

}
