
#include "Timetable.h"
Timetable Timetable::instance;
static int currentId = 1;
// Timetable::Timetable(){
//      classrooms.insert(Classroom(0, "---", 0));

// } 
int Timetable::addClassroom(const string& name,int seatingCapacity){
     cout << "---Classroom: constructeur d'initialisation" << endl; 

     classrooms.insert(Classroom(currentId, name, seatingCapacity));
     currentId++;
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
     int currentIndex = 1;
     for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it++){
          if(currentIndex == id) return *it;

          currentIndex++;
     }
     throw std::out_of_range("Index hors limites");
}

void Timetable::deleteClassroomByIndex(int index)
{
     int currentIndex = 0;
     for (auto it = classrooms.begin(); it != classrooms.end(); ++it)
     {
          if(currentIndex == index)
          {
               classrooms.erase(it);
               --currentId;
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
               --currentId;
               return;
          }
     }
     throw std::out_of_range("Identifiant non trouvé");
}

int Timetable::addProfessor(const string& lastName,const string& firstName)
{
     cout << "---Professor: constructeur d'initialisation" << endl; 

     professors.insert(Professor(currentId, lastName, firstName));

     ++currentId;
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
               --currentId;
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
               --currentId;
               return;
          }
     }
     throw std::out_of_range("Identificant non trouvé");
}

int Timetable::addGroup(const string& name)
{
     cout << "---Group: constructeur d'initialisation" << endl; 

     groups.insert(Group(currentId, name));

     ++currentId;
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
               --currentId;
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
               --currentId;
               return;
          }
     }
     throw std::out_of_range("Identificant non trouvé");
}
Timetable& Timetable::getInstance()
{
     return instance;
}