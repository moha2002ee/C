#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string.h>
#include "Event.h"
#include "TimingException.h"
#include <set>

using namespace std;

namespace planning
{
    class Course : public Event
    {
    private:
        int professorId;
        int classroomId;
        set<int> groupsIds;
        int compT(const Course &c);

    public:
        Course() = default;
        Course(int c, const char *t, int ProfId, int ClassroomId, set<int> groupsIds);
        Course(const Course &c) = default;
        ~Course() = default;
        void addGroupId(int id);
        bool isGroupIdPresent(int id);

        void setProfessorId(int professorId);
        void setClassroomId(int classroomId);
        void setGroupsIds(set<int> groupsIds);

        int getProfessorId();
        int getClassroomId();
        set<int> getGroupsIds();

        void addGroupId(int id);
        bool isGroupIdPresent(int id);

        Course &operator=(const Course &c) = default;

        int operator<(const Course &c);
        int operator>(const Course &c);
        int operator==(const Course &c);
    };
}
#endif