#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <set>
#include "Classroom.h"
#include "Professor.h"
#include "Group.h"
#include <iostream>
using namespace std;
using namespace planning;


class Timetable 
{ 
  private: 
    set<Classroom> classrooms; 
    set<Professor> professors; 
    set<Group>     groups; 
 static Timetable instance;
  public:

   Timetable()= default;
   ~Timetable() = default; 
 
   int addClassroom(const string& name,int seatingCapacity); 
   void displayClassrooms() const; 
   Classroom findClassroomByIndex(int index) const; 
   Classroom findClassroomById(int id) const; 
   void deleteClassroomByIndex(int index); 
   void deleteClassroomById(int id); 
 
   int addProfessor(const string& lastName,const string& firstName); 
   void displayProfessors() const; 
   Professor findProfessorByIndex(int index) const; 
   Professor findProfessorById(int id) const; 
   void deleteProfessorByIndex(int index); 
   void deleteProfessorById(int id); 
 
   int addGroup(const string& name); 
   void displayGroups() const; 
   Group findGroupByIndex(int index) const; 
   Group findGroupById(int id) const; 
   void deleteGroupByIndex(int index); 
   void deleteGroupById(int id); 

      static Timetable& getInstance();
}; 


#endif
