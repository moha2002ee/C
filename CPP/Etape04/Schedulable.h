#ifndef SCHEDULABLE
#define SCHEDULABLE

#include <sstream> 
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

class Schedulable	{

protected:
	int id;  //id du schedulable

public:
	/*CONSTRUCTEUR*/
	Schedulable();
	Schedulable(int i);
	Schedulable(const Schedulable &s) = default;

	/*DESTRUCTEUR*/
	virtual ~Schedulable() = default; 

	/*SETTER*/
	void setId(int i);

	/*GETTER*/
	int getId();

	/*METHODE*/
	virtual string toString() const = 0;  //Méthode virtuelle pure
	virtual string tuple() const = 0;
};


#endif