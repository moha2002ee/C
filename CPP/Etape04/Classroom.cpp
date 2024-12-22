#include "Classroom.h"
#include <string>
#include <sstream>
using namespace std;

Classroom::Classroom()
{
    setName("");
    setSeatingCapacity(0);
}

Classroom::Classroom(int i, string n, int s)
{
    Schedulable::setId(i);  
    setName(n);
    setSeatingCapacity(s);
}

void Classroom::setName(string n)
{
    name = n;
}

void Classroom::setSeatingCapacity(int s)
{
    seatingCapacity = s;
}

string Classroom::getName() const
{
    return name;
}

int Classroom::getSeatingCapacity() const  // Ajout de const
{
    return seatingCapacity;
}

string Classroom::toString() const
{
    ostringstream oss;
    oss << name << " " << seatingCapacity;
    return oss.str();
}

string Classroom::tuple() const
{
    ostringstream oss;
    oss << id << ";" << name << ";" << seatingCapacity;
    return oss.str();
}

Classroom &Classroom::operator=(const Classroom &c)
{
    Schedulable::setId(c.id);  
    setName(c.name);
    setSeatingCapacity(c.seatingCapacity);
    return *this;
}
ostream& operator<<(ostream& o, const Classroom& c)
	{
		o << c.toString() << endl;
  		return o;
	}