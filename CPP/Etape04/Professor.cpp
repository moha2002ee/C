#include "Professor.h"

ostream &operator<<(ostream &o, const Professor &p)
{
	o << p.toString() << endl;
	return o;
}

Professor::Professor() : Schedulable()
{
	lastName = "---";
	firstName = "---";

#ifdef DEBUG
	cout << "appel du constructeur par defaut Professor" << endl;
#endif
}

Professor::Professor(int i, const string &ln, const string &fn) : Schedulable(i)
{
	setLastName(ln);
	setFirstName(fn);

#ifdef DEBUG
	cout << "appel du constructeur par initialisation Professor" << endl;
#endif
}

/*SETTER*/
void Professor::setLastName(const string &ln)
{
	lastName = ln;
}

void Professor::setFirstName(const string &fn)
{
	firstName = fn;
}

/*GETTER*/
string Professor::getLastName()
{
	return lastName;
}

string Professor::getFirstName()
{
	return firstName;
}

/*METHODE*/
string Professor::toString() const
{
	ostringstream oss;
	oss << firstName << " " << lastName;
	return oss.str();
}

string Professor::tuple() const
{
	ostringstream oss;
	oss << id << ";" << firstName << ";" << lastName;
	return oss.str();
}

Professor &Professor::operator=(const Professor &p)
{
	setId(p.id);
	setLastName(p.lastName);
	setFirstName(p.firstName);
	return (*this);
}