#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <set>
#include <list>

#include "Classroom.h"
#include "Professor.h"
#include "Group.h"
#include "Course.h"
#include "Schedulable.h"
#include "XmlFileSerializer.hpp"
#include <iostream>
#include <fstream> 
#include <iomanip>

using namespace std;
using namespace planning;


class Timetable 
{ 
  private: 
    Timetable()= default;
    set<Classroom> classrooms; 
    set<Professor> professors; 
    set<Group>     groups;
    list<Course>   courses;

    static Timetable instance;
  
  public:
   Timetable(const Timetable& t) = delete;
   ~Timetable() = default; 
 
   int addClassroom(const string& name,int seatingCapacity); 
   void displayClassrooms() const; 
   Classroom findClassroomByIndex(int index) const; 
   Classroom findClassroomById(int id) const; 
   void deleteClassroomByIndex(int index); 
   void deleteClassroomById(int id); 
   bool isClassroomAvailable(int id, const Timing& timing);
 
   int addProfessor(const string& lastName,const string& firstName); 
   void displayProfessors() const; 
   Professor findProfessorByIndex(int index) const; 
   Professor findProfessorById(int id) const; 
   void deleteProfessorByIndex(int index); 
   void deleteProfessorById(int id); 
   bool isProfessorAvailable(int id, const Timing& timing);
 
   int addGroup(const string& name); 
   void displayGroups() const; 
   Group findGroupByIndex(int index) const; 
   Group findGroupById(int id) const; 
   void deleteGroupByIndex(int index); 
   void deleteGroupById(int id); 
   bool isGroupAvailable(int id, const Timing& timing);

   void deleteCourseById(int code);

   set<Classroom> getClassrooms() const;
   set<Professor> getProfessors() const; 
   set<Group>     getGroups()     const; 
   list<Course>     getCourses()  const; 

   static Timetable& getInstance();

   void save(const string& timetableName);
   void load(const string& timetableName);
   void schedule(Course& c, const Timing& t);
   string tuple(const Course& c);
   int importProfessorsFromCsv(const string& filename);
   int importGroupsFromCsv(const string& filename);
   int importClassroomsFromCsv(const string& filename);
   void exportProfessorTimetable(int id);
   void exportLocalTimetable(int id);
   void exportGroupTimetable(int id);

   
   Timetable& operator=(const Timetable& t) = delete;
}; 


#endif
