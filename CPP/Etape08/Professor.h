#ifndef PROFESSOR
#define PROFESSOR

#include "Schedulable.h"

class Professor : public Schedulable {

friend ostream& operator<<(ostream& o, const Professor& p);


private:
	string lastName;
	string firstName;

public:
	/*CONSTRUCTEUR*/
	Professor();
	Professor(int i, const string &ln, const string &fn);
	Professor(const Professor &p) = default;

	/*DESTRUCTEUR*/
	~Professor() = default;

	/*SETTER*/
	void setLastName(const string &ln);
	void setFirstName(const string &fn);

	/*GETTER*/
	string getLastName();
	string getFirstName();

	/*METHODE*/
	string toString() const override;  //Méthode surchargé
	string tuple() const override;

	/*OPERATEUR*/
	Professor& operator=(const Professor &p);
};
#endif