#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string.h>
#include "Event.h"
#include "Timing.h"
#include "TimingException.h"
#include <set>

using namespace std;

namespace planning
{
    class Course : public Event 
    {

        friend ostream& operator<<(ostream& o, const Course& c);
        friend istream& operator>>(istream& i, Course& c);

    private:
        int professorId;
        int classroomId;
        set<int>groupsIds;
      
    public:
        Course() = default;
        Course(int c, const char* t, int ProfId, int ClassroomId, set<int >groupsIds);
        Course(const Course& c) = default;
        ~Course() = default;

        void setProfessorId(int professorId);
        void setClassroomId(int classroomId);
        void setGroupsIds(set<int >groupsIds);

        int getProfessorId() const;
        int getClassroomId() const;
        set<int> getGroupsIds() const;

        void addGroupId(int id);
        bool isGroupIdPresent(int id) const;

        Course& operator=(const Course& c) = default;

        int operator<(const Course& c) const;
        int operator>(const Course& c);
        int operator==(const Course& c); 
    };
}
#endif