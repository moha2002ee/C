#include "Timetable.h"

Timetable Timetable::instance;

int Timetable::addClassroom(const string& name,int seatingCapacity){
     cout << "---Classroom: constructeur d'initialisation" << endl; 

     classrooms.insert(Classroom(Schedulable::currentId, name, seatingCapacity));
     Schedulable::currentId++;
     return classrooms.size();
} 
void Timetable::displayClassrooms() const{
     cout << "contenu classrooms: " << endl;

     for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it++){
          cout << it->toString() << endl;
     }
}
Classroom Timetable::findClassroomByIndex(int index) const{
     int currentIndex = 0;
     for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it++){
          if(currentIndex == index) return *it;

          currentIndex++;
     }
     throw std::out_of_range("Index hors limites");

}
Classroom Timetable::findClassroomById(int id) const
{
     
     for (auto it = classrooms.cbegin(); it != classrooms.cend(); ++it)
     {
          if(it->getId() == id)
          {
               return *it;
          }
     }
     throw std::out_of_range("Identifiant non trouvé");
}

void Timetable::deleteClassroomByIndex(int index)
{
     int currentIndex = 0;
     for (auto it = classrooms.begin(); it != classrooms.end(); ++it)
     {
          if(currentIndex == index)
          {
               classrooms.erase(it);
               return;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limites");
}

void Timetable::deleteClassroomById(int id)
{
     for (auto it = classrooms.begin(); it != classrooms.end(); ++it)
     {
          if(it->getId() == id)
          {
               classrooms.erase(it);
               return;
          }
     }
     throw std::out_of_range("Identifiant non trouvé");
}



int Timetable::addProfessor(const string& lastName,const string& firstName)
{
     cout << "---Professor: constructeur d'initialisation" << endl; 

     professors.insert(Professor(Schedulable::currentId, lastName, firstName));

     ++Schedulable::currentId;
     return professors.size();

}

void Timetable::displayProfessors() const
{
     cout << "contenu professors: " << endl;

     for (auto it = professors.cbegin(); it != professors.cend(); ++it)
     {
          cout << it->toString() << endl;
     } 
}

Professor Timetable::findProfessorByIndex(int index) const
{
     int currentIndex = 0;
     for (auto it = professors.cbegin(); it != professors.cend(); ++it)
     {
          if(currentIndex == index)
          {
               return *it;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limites");
}

Professor Timetable::findProfessorById(int id) const
{
     for (auto it = professors.cbegin(); it != professors.cend(); ++it)
     {
          if(it->getId() == id)
          {
               return *it;
          }
     }
     throw std::out_of_range("Identifiant non trouvé");
}

void Timetable::deleteProfessorByIndex(int index)
{
     int currentIndex = 0;
     for (auto it = professors.begin(); it != professors.end(); ++it)
     {
          if (currentIndex == index)
          {
               professors.erase(it);
               return;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limite");
}

void Timetable::deleteProfessorById(int id)
{
     for (auto it = professors.begin(); it != professors.end(); ++it)
     {
          if (it->getId() == id)
          {
               professors.erase(it);
               return;
          }
     }
     throw std::out_of_range("Identificant non trouvé");
}



int Timetable::addGroup(const string& name)
{
     cout << "---Group: constructeur d'initialisation" << endl; 

     groups.insert(Group(Schedulable::currentId, name));

     ++Schedulable::currentId;
     return groups.size();
}

void Timetable::displayGroups() const
{
    cout << "contenu groups: " << endl;

     for (auto it = groups.cbegin(); it != groups.cend(); ++it)
     {
          cout << it->toString() << endl;
     }  
}

Group Timetable::findGroupByIndex(int index) const
{
     int currentIndex = 0;

     for (auto it = groups.cbegin() ; it != groups.cend(); ++it)
     {
          if (currentIndex == index)
          {
               return *it;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limites");
}

Group Timetable::findGroupById(int id) const
{
     for (auto it = groups.cbegin() ; it != groups.cend(); ++it)
     {
          if (it->getId() == id)
          {
               return *it;
          }
     }
     throw std::out_of_range("Index hors limites");
}

void Timetable::deleteGroupByIndex(int index)
{
     int currentIndex = 0;

     for (auto it = groups.begin(); it != groups.end(); ++it)
     {
          if (currentIndex == index)
          {
               groups.erase(it);
               return;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limite");
}

void Timetable::deleteGroupById(int id)
{
     for (auto it = groups.begin(); it != groups.end(); ++it)
     {
          if (it->getId() == id)
          {
               groups.erase(it);
               return;
          }
     }
     throw std::out_of_range("Identificant non trouvé");
}



Timetable& Timetable::getInstance()
{
     return instance;
}


set<Classroom> Timetable::getClassrooms() const
{
     return classrooms;
}

set<Professor> Timetable::getProfessors() const
{
     return professors;
}

set<Group> Timetable::getGroups() const
{
     return groups;
} 


