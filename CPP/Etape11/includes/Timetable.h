#ifndef TIMETABLE_H
#define TIMETABLE_H
#include <set>
#include "Classroom.h"
#include "Professor.h"
#include "Group.h"
#include "Schedulable.h"
#include "Timing.h"
#include "XmlFileSerializer.hpp"
#include <iostream>
#include <fstream>
#include "Course.h"
using namespace std;
using namespace planning;
class Timetable
{
private:
  Timetable() = default;
  set<Classroom> classrooms;
  set<Professor> professors;
  set<Group> groups;
  static Timetable instance;
  set<Course> courses;
  Timing *timing;

public:
  Timetable(const Timetable &t) = delete;
  ~Timetable() = default;

  int addClassroom(const string &name, int seatingCapacity);
  void displayClassrooms() const;
  Classroom findClassroomByIndex(int index) const;
  Classroom findClassroomById(int id) const;
  void deleteClassroomByIndex(int index);
  void deleteClassroomById(int id);

  int addProfessor(const string &lastName, const string &firstName);
  void displayProfessors() const;
  Professor findProfessorByIndex(int index) const;
  Professor findProfessorById(int id) const;
  void deleteProfessorByIndex(int index);
  void deleteProfessorById(int id);

  int addGroup(const string &name);
  void displayGroups() const;
  Group findGroupByIndex(int index) const;
  Group findGroupById(int id) const;
  void deleteGroupByIndex(int index);
  void deleteGroupById(int id);

  set<Classroom> getClassrooms() const;
  set<Professor> getProfessors() const;
  set<Group> getGroups() const;
  set<Course> getCourse() const;

  static Timetable &getInstance();

  void save(const string &timetableName);
  void load(const string &timetableName);

  Timetable &operator=(const Timetable &t) = delete;
  bool isClassroomAvailable(int id, const Timing &timing);
  void schedule(Course &c, const Timing &t);
  bool isGroupAvailable(int id, const Timing &timing);
  bool isProfessorAvailable(int id, const Timing &timing);
  void addCourse(Course &c);
};
#endif
