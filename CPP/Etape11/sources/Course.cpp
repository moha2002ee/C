#include "Course.h"
namespace planning
{
    Course::Course(int c, const char *t, int ProfId, int classroomId, set<int> groupsIds) : Event(c, t)
    {

        setProfessorId(ProfId);
        setClassroomId(classroomId);
        setGroupsIds(groupsIds);
    }
    void Course::setProfessorId(int prid)
    {
        professorId = prid;
    }
    void Course::setClassroomId(int clid)
    {
        classroomId = clid;
    }
    void Course::setGroupsIds(set<int> grId)
    {
        groupsIds = grId;
    }

    int Course::getProfessorId()
    {
        return professorId;
    }
    set<int> Course::getGroupsIds()
    {
        return groupsIds;
    }
    int Course::getClassroomId()
    {
        return classroomId;
    }
    void Course::addGroupId(int i)
    {
        groupsIds.insert(i);
    }

    bool Course::isGroupIdPresent(int i)
    {
        for (auto it = groupsIds.cbegin(); it != groupsIds.cend(); it++)
        {
            if (*it == i)
            {
                return true;
            }
        }
        return false;
    }
    int Course::compT(const Course &c)
    {
        if (!timing || !c.timing)
            throw TimingException("---pas d'envenement---", TimingException::NO_TIMING);

        return timing->compT(*c.timing);
    }
    int Course::operator<(const Course &c)
    {
        return compT(c) == -1;
    }

    int Course::operator>(const Course &c)
    {
        return compT(c) == 1;
    }

    int Course::operator==(const Course &c)
    {
        return compT(c) == 0;
    }
}
