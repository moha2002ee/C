#include "Group.h"
#include <string>
#include <sstream>

Group::Group(){
    setName("");
}

Group::Group(int i, string n){
    Schedulable::setId(i);
    setName(n);
}

void Group::setName(string n) {
    name = n;
}

string Group::getName() const {
    return name;
}

string Group::toString() const
{
	ostringstream oss;
	oss << name;
	return oss.str();
}

string Group::tuple() const
{
	ostringstream oss;
	oss << id << ";" << name ;
	return oss.str();
}
Group &Group::operator=(const Group &g) {
    setId(g.id);
	setName(g.name);
	return (*this);
}
ostream &operator<<(ostream &o, const Group &g)
{
	o << g.toString() << endl;
	return o;
}