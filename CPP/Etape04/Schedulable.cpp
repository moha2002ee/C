#include "Schedulable.h"

/*CONSTRUCTEUR*/
Schedulable::Schedulable()
{
	setId(0);

	#ifdef DEBUG
	cout << "appel du constructeur par defaut Schedulable" << endl;
	#endif
}

Schedulable::Schedulable(int i)
{
	setId(i);

	#ifdef DEBUG
	cout << "appel du constructeur par initialisation Schedulable" << endl;
	#endif
}

/*SETTER*/
void Schedulable::setId(int i)
{
	id = i;
}

/*GETTER*/
int Schedulable::getId()
{
	return id;
}