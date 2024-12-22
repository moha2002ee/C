#include "Timetable.h"
static int currentId = 1;

int Timetable::addClassroom(const string &name, int seatingCapacity)
{
    cout << "constructeur d'initialisation" << endl;
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
Classroom Timetable::findClassroomByIndex(int i)const {
    int currentIndex=0; 
    for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it ++){
        if (currentIndex == i){
            return *it;
        }
        currentIndex++;
    }
    throw std::out_of_range("tu depasse la limites ");
}
Classroom Timetable::findClassroomById(int i )const{
    int currentId = 1;
    for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it ++){
        if (currentId == i){
            return *it;
        }
        currentId ++; 
    }
    throw std::out_of_range("tu depasse la limites ");
}
void Timetable::deleteClassroomByIndex(int i){
    int currentindex = 0 ; 
    for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it ++){
        if (currentindex== i){
            classrooms.erase(it);
            currentindex--;
            return;
        }
        currentindex++;
    }
}
void Timetable::deleteClassroomById(int i){
    int currentindex = 0 ; 
    for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it ++){
        if (currentindex== i){
            classrooms.erase(it);
            currentindex--;
            return;
        }
        currentindex++;
    }
}


int Timetable::addProfessor(const string& lastName,const string& firstName){

    cout << "constructeur d'initialisation" << endl;
    professors.insert(Professor(currentId, lastName, firstName)); 
    currentId++;
    return professors.size();
}
void Timetable::displayProfessors() const{
     cout << "contenu professors: " << endl;

     for (set<Professor>::const_iterator it = professors.cbegin(); it != professors.cend(); it++){
          cout << it->toString() << endl;
     }
}
Professor Timetable::findProfessorByIndex(int i)const {
    int currentIndex=0; 
    for (set<Professor>::const_iterator it = professors.cbegin(); it != professors.cend(); it ++){
        if (currentIndex == i){
            return *it;
        }
        currentIndex++;
    }
    throw std::out_of_range("tu depasse la limites ");
}
Professor Timetable::findProfessorById(int i )const{
    int currentId = 1;
    for (set<Professor>::const_iterator it = professors.cbegin(); it != professors.cend(); it ++){
        if (currentId == i){
            return *it;
        }
        currentId ++; 
    }
    throw std::out_of_range("tu depasse la limites ");
}
void Timetable::deleteProfessorByIndex(int i){
    int currentindex = 0 ; 
    for (set<Professor>::const_iterator it = professors.cbegin(); it != professors.cend(); it ++){
        if (currentindex== i){
            professors.erase(it);
            currentindex--;
            return;
        }
        currentindex++;
    }
}
void Timetable::deleteProfessorById(int i){
    int currentindex = 0 ; 
    for (set<Professor>::const_iterator it = professors.cbegin(); it != professors.cend(); it ++){
        if (currentindex== i){
            professors.erase(it);
            currentindex--;
            return;
        }
        currentindex++;
    }
}

int Timetable::addGroup(const string&name){

}