#include "Course.h"
namespace planning {

    // Surcharge de l'opérateur <<
    ostream& operator<<(ostream& o, const Course& c) {
        o << "<Course>" << endl;
        o << "<event>" << endl;
        o << static_cast<const Event&>(c) << endl;
        o << "</event>" << endl;
        o << "<professorId>" << endl << c.professorId << endl << "</professorId>" << endl;
        o << "<classroomId>" << endl << c.classroomId << endl << "</classroomId>" << endl;
        o << "<groupsIds>" << endl;
        for (auto it = c.groupsIds.begin(); it != c.groupsIds.end(); ++it) {
            o << "<groupId>" << endl << *it << endl << "</groupId>" << endl;
        }
        o << "</groupsIds>" << endl;
        o << "</Course>";
        return o;
    }

    // Surcharge de l'opérateur >>
    istream& operator>>(istream& i, Course& c) {
        string tag, sProfessorId, sClassroomId, sGroupId;
        getline(i, tag); // <Course>
        getline(i, tag); // <event>
        i >> static_cast<Event&>(c); // Chargement des informations d'Event
        getline(i, tag); // </event>
        getline(i, tag); // <professorId>
        getline(i, sProfessorId);
        getline(i, tag); // </professorId>
        getline(i, tag); // <classroomId>
        getline(i, sClassroomId);
        getline(i, tag); // </classroomId>
        getline(i, tag); // <groupsIds>
        c.groupsIds.clear();
        while (true) {
            getline(i, tag); // Soit <groupId> soit </groupsIds>
            if (tag == "</groupsIds>") break;
            if (tag == "<groupId>") {
                getline(i, sGroupId);
                c.groupsIds.insert(stoi(sGroupId));
                getline(i, tag);
            }
        }
        c.professorId = stoi(sProfessorId);
        c.classroomId = stoi(sClassroomId);
        return i;
    }

    // Constructeur d'initialisation
    Course::Course(int c, const char* t, int ProfId, int classroomId, set<int> groupsIds) : Event(c, t) {
        #ifdef DEBUG
        cout << "Constructeur d'initialisation de la classe Course" << endl;
        #endif
        setProfessorId(ProfId);
        setClassroomId(classroomId);
        setGroupsIds(groupsIds);
    }

    // Accesseurs et mutateurs
    void Course::setProfessorId(int professorId) {
        this->professorId = professorId;
    }

    void Course::setClassroomId(int classroomId) {
        this->classroomId = classroomId;
    }

    void Course::setGroupsIds(set<int> groupsIds) {
        this->groupsIds = groupsIds;
    }

    int Course::getProfessorId() const {
        return professorId;
    }

    int Course::getClassroomId() const {
        return classroomId;
    }

    set<int> Course::getGroupsIds() const {
        return groupsIds;
    }

    // Ajout d'un groupe
    void Course::addGroupId(int id) {
        #ifdef DEBUG
        cout << "Passage par addGroupId" << endl;
        #endif
        groupsIds.insert(id);
    }

    // Vérification de la présence d'un groupe
    bool Course::isGroupIdPresent(int id) const {
        return groupsIds.find(id) != groupsIds.end();
    }

    // Comparaison des événements
    int Course::operator<(const Course& c) const {
        if (this->timing == nullptr || c.timing == nullptr) {
            throw TimingException("---Evenement non planifié---", TimingException::NO_TIMING);
        }
        return *(this->timing) < *(c.timing);
    }

    int Course::operator>(const Course& c) {
        if (this->timing == nullptr || c.timing == nullptr) {
            throw TimingException("---Evenement non planifié---", TimingException::NO_TIMING);
        }
        return *(this->timing) > *(c.timing);
    }

    int Course::operator==(const Course& c) {
        if (this->timing == nullptr || c.timing == nullptr) {
            throw TimingException("---Evenement non planifié---", TimingException::NO_TIMING);
        }
        return *(this->timing) == *(c.timing);
    }

}
